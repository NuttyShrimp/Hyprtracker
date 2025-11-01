//
// Created by janle on 01/11/2025.
//

#include "state.h"

#include <chrono>

std::chrono::time_point<std::chrono::system_clock> get_start_of_week_time()
{
    auto now = std::chrono::system_clock::now();
    std::chrono::year_month_weekday ymw{std::chrono::floor<std::chrono::days>(now)};
    auto start_of_week = now - std::chrono::days{ymw.weekday().iso_encoding() - 1};
    return start_of_week;
}

State::State() : selected_time(get_start_of_week_time())
{
}

void State::move_a_week(int modifier)
{
    std::chrono::days d{7 * modifier};
    selected_time = selected_time + d;
    m_signal_change.emit();
}

void State::reset_time()
{
    selected_time = get_start_of_week_time();
    m_signal_change.emit();
}

State::type_signal_change State::signal_change()
{
    return m_signal_change;
}
