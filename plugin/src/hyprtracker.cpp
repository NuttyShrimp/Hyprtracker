#include "globals.hpp"
#include "store.hpp"
#include <cstddef>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <hyprland/src/plugins/PluginAPI.hpp>
#include <memory>
#include <wayland-util.h>

std::unique_ptr<std::ofstream> log_file;

APICALL EXPORT std::string PLUGIN_API_VERSION() { return HYPRLAND_API_VERSION; }

static void failNotif(const std::string &reason) {
  HyprlandAPI::addNotification(
      PHANDLE, "[hyprtracker] Failure in initialization: " + reason,
      CHyprColor{1.0, 0.2, 0.2, 1.0}, 5000);
}

bool make_storage_available() {
  auto homePath = std::getenv("HOME");
  if (homePath == NULL) {
    return false;
  }
  auto p = std::format("{}{}", homePath, STORAGE_LOCATION);
  auto fp = p + "/storage.db";
  if (std::filesystem::exists(fp)) {
    return true;
  }
  if (!std::filesystem::exists(p)) {
    if (!std::filesystem::create_directories(p)) {
      return false;
    }
  }
  std::ofstream stream;
  stream.open(fp, std::ios::binary);
  stream.close();
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
  std::cout << "Hyprtracker logging initiated" << std::endl;
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

  auto store_ptr = std::make_shared<Store>();

  return {"hyprtracker", "A time tracking plugin", "NuttyShrimp", "1.0"};
}

APICALL EXPORT void PLUGIN_EXIT() {
  if (log_file) {
    (*log_file).close();
  }
}
