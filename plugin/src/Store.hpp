#pragma once

#include "globals.hpp"
#include <chrono>


// A basic store, it will save the durations to a local file
class Store {
public:
    Store() = default;
    virtual ~Store() = default;

    void init();
    void saveDuration(const std::string& windowName, std::chrono::seconds duration);
private:
    std::mutex m_mutex;
    std::filesystem::path m_storePath = std::filesystem::path(std::getenv("HOME")) / ".local/share/hyprtracker/durations";
};