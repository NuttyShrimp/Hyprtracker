#pragma once

#include "globals.hpp"
#include <chrono>
#include <map>
#include <set>
#include <SQLiteCpp/SQLiteCpp.h>


// A basic store, it will save the durations to a local file
class Store {
public:
    Store() = default;
    virtual ~Store() = default;

    void init();
    void saveDuration(const std::string& windowName, std::chrono::seconds duration);
private:
    std::mutex m_mutex;
    // Stored durations that failed to save to the file
    std::set<std::pair<std::string, size_t>> m_missed_durations;
    // TODO: Is for webserver logic
    // std::filesystem::path m_storePath = std::filesystem::path(std::getenv("HOME")) / ".local/share/hyprtracker/durations";
    // std::string m_endpoint;

    void save_missing_durations(std::ofstream &file);

    // void push_to_server();
    // std::map<std::string, size_t> get_merged_durations();
};