//
// Created by janle on 01/11/2025.
//

#ifndef VIEWER_STATE_H
#define VIEWER_STATE_H
#include <chrono>
#include <ctime>
#include <sigc++/signal.h>
#include <sigc++/adaptors/adaptor_trait.h>


class State
{
public:
    State();
    std::chrono::time_point<std::chrono::system_clock> selected_time;
    void move_a_week(int modifier);
    void reset_time();

    using type_signal_change = sigc::signal<void()>;
    type_signal_change signal_change();

protected:
    type_signal_change m_signal_change;
};


#endif //VIEWER_STATE_H
