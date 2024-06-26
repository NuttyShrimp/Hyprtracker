#include "Tracker.hpp"

#include <hyprland/src/desktop/Window.hpp>

Tracker::Tracker(std::shared_ptr<Store> store): m_store(store) {}

Tracker::~Tracker() {
    store_duration(nullptr);
}

void Tracker::onWindowChange(PHLWINDOW window) {
    if (window == m_currentWindow) {
        return;
    }
    store_duration(window);
}

void Tracker::store_duration(PHLWINDOW window) {
    if (m_currentWindow != nullptr) {
        // Calculate the time spent in the window
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - m_startTime);
        auto title = m_currentWindow->m_szInitialTitle;
        if (title.empty()) {
            title = m_currentWindow->m_szInitialClass;
        }
        m_store->saveDuration(title, duration);
    }

    if (window != nullptr) {
        m_currentWindow = window;
        m_startTime = std::chrono::system_clock::now();
    }
}
