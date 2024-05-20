//
// Created by janle on 18/05/24.
//

#include "Store.hpp"
#include <chrono>

void Store::init() {
    // Should be stored in ~/.local/share/hyprtracker/durations
    if (!exists(m_storePath)) {
        create_directories(m_storePath.parent_path());
    };
}

void Store::saveDuration(const std::string &windowName, std::chrono::seconds duration) {
    std::lock_guard lock(m_mutex);

    std::ofstream file(m_storePath, std::ios::app);
    file << windowName << " " << duration.count() << std::endl;
    file.close();
}
