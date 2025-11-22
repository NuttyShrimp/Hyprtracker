#include "globals.hpp"
#include "store.hpp"
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <fstream>
#include <hyprland/src/desktop/Window.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>
#include <memory>
#include <stdexcept>

std::unique_ptr<std::ofstream> log_file;
std::shared_ptr<Store> store_ptr;
std::string active_window = "";
std::chrono::time_point<std::chrono::system_clock> switch_time =
    std::chrono::system_clock::now();
static SP<HOOK_CALLBACK_FN> activeWindowHookCallback;

APICALL EXPORT std::string PLUGIN_API_VERSION() { return HYPRLAND_API_VERSION; }

static void failNotif(const std::string &reason) {
  std::cerr << "Failure: " << reason << std::endl;
  HyprlandAPI::addNotification(PHANDLE, "[hyprtracker] Failure: " + reason,
                               CHyprColor{1.0, 0.2, 0.2, 1.0}, 5000);
}

bool make_storage_available() {
  auto homePath = std::getenv("HOME");
  if (homePath == nullptr) {
    return false;
  }
  const auto p = homePath + STORAGE_LOCATION;
  if (auto fp = p + "/storage.db"; std::filesystem::exists(fp)) {
    return true;
  }
  if (!std::filesystem::exists(p) && !std::filesystem::create_directories(p)) {
    return false;
  }
  return true;
}

void redirect_outputs() {
  log_file = std::make_unique<std::ofstream>("/tmp/hyprtracker.log");

  if (!(*log_file).is_open()) {
    std::cerr << "Failed to open log file" << std::endl;
    throw std::runtime_error("Failed to open log file");
  }

  // Redirect cout to the file by setting cout's buffer to the file's buffer
  std::cout.rdbuf((*log_file).rdbuf());
  std::cerr.rdbuf((*log_file).rdbuf());
  std::cout << "Hyprtracker logging initiated" << std::endl;
}

void handle_window_change(const std::string &window_title) {
  if (window_title == active_window)
    return;

  auto duration = std::chrono::duration_cast<std::chrono::seconds>(
                      std::chrono::system_clock::now() - switch_time)
                      .count();
  switch_time = std::chrono::system_clock::now();
  store_ptr->storeWindowChange(active_window, duration);
  active_window = window_title;
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
  PHANDLE = handle;

  const std::string HASH = __hyprland_api_get_hash();

  if (HASH != GIT_COMMIT_HASH) {
    failNotif(
        "Version mismatch (headers ver is not equal to running hyprland ver)");
    throw std::runtime_error("[ht] Version mismatch");
  }

  redirect_outputs();

  if (!make_storage_available()) {
    failNotif("Unable to create/check storage directory, make sure the HOME "
              "variable is set");
    throw std::runtime_error("[ht] storage initialization error");
  }

  store_ptr = std::make_shared<Store>();
  store_ptr->init();
  std::cout << "Sqlite DB initiated" << std::endl;

  activeWindowHookCallback = HyprlandAPI::registerCallbackDynamic(
      PHANDLE, "activeWindow", [&](void *, SCallbackInfo &, std::any data) {
        std::cout << "window changed " << std::endl;
        try {
          auto window = std::any_cast<PHLWINDOW>(data);
          auto title = window->m_class;
          if (title.empty()) {
            title = window->m_title;
          }
          // auto title = window->m_initialTitle;
          // if (title.empty())
          // {
          //     title = window->m_initialClass;
          // }
          std::cout << "window changed to: " << title << std::endl;

          handle_window_change(title);
        } catch (const std::bad_any_cast &e) {
          std::cerr << "casting exception: " << e.what() << std::endl;
          throw std::runtime_error(
              "[ht] failed to parse data from window change event");
        }
      });
  if (activeWindowHookCallback == nullptr) {
    failNotif("Unable to register hyprland callbacks");
    throw std::runtime_error("[ht] callback initialization error");
  }

  // printf("Callback pointer: %p\n", (void *)activeWindowHookCallback.get());
  std::cout << "Plugin setup!" << std::endl;

  return {"hyprtracker", "A time tracking plugin", "NuttyShrimp", "1.0"};
}

APICALL EXPORT void PLUGIN_EXIT() {
  handle_window_change("");
  if (log_file) {
    log_file->close();
  }
}
