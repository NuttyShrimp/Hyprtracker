#include "Tracker.hpp"

#include "globals.hpp"

std::shared_ptr<Store> store = std::make_shared<Store>();
std::unique_ptr<Tracker> tracker = std::make_unique<Tracker>(store);

static void onActiveWindowChange(void *self, SCallbackInfo &info, std::any data) {
    try {
        auto window = std::any_cast<PHLWINDOW>(data);
        tracker->onWindowChange(window);
    } catch (const std::bad_any_cast &e) {}
}

APICALL EXPORT std::string PLUGIN_API_VERSION() {
    return HYPRLAND_API_VERSION;
}

APICALL EXPORT PLUGIN_DESCRIPTION_INFO PLUGIN_INIT(HANDLE handle) {
    PHANDLE = handle;

    const std::string HASH = __hyprland_api_get_hash();

    // ALWAYS add this to your plugins. It will prevent random crashes coming from
    // mismatched header versions.

    if (HASH != GIT_COMMIT_HASH) {
        HyprlandAPI::addNotification(PHANDLE, "[HyprTracker] Mismatched headers! Can't proceed.",
                                     CColor{1.0, 0.2, 0.2, 1.0}, 5000);
        throw std::runtime_error("[HyprTracker] Version mismatch");
    }

    // TODO: If the server is running locally, get the port from the env variable
    HyprlandAPI::addConfigValue(PHANDLE, "plugin:hyprtracker:endpoint", Hyprlang::STRING{"http://localhost:21435"});

    store->init();

    static auto P = HyprlandAPI::registerCallbackDynamic(PHANDLE, "activeWindow",
                                                         [&](void *self, SCallbackInfo &info, std::any data) {
                                                             onActiveWindowChange(self, info, data);
                                                         });

    return {"HyprTracker", "Track the time spent in a window", "NuttyShrimp", "0.1"};
}

APICALL EXPORT void PLUGIN_EXIT() {
}
