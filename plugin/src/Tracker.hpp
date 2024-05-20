#pragma once

#include "globals.hpp"
#include "Store.hpp"
#include <chrono>

class Tracker {
public:
    Tracker(std::shared_ptr<Store> store);

    virtual ~Tracker() = default;

    void onWindowChange(PHLWINDOW window);

private:
    std::shared_ptr<Store> m_store;
    PHLWINDOW m_currentWindow = nullptr;
    std::chrono::time_point<std::chrono::system_clock> m_startTime;
};

