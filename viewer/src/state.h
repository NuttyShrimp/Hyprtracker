#pragma once
#include <chrono>
#include <peel/GObject/Object.h>
#include <peel/GObject/ParamSpec.h>
#include <peel/class.h>
#include <peel/signal.h>

namespace Hyprtracker {
using tpsystem = std::chrono::time_point<
    std::chrono::system_clock,
    std::common_type<std::chrono::duration<long, std::ratio<1, 1000000000>>,
                     std::chrono::duration<long, std::ratio<86400, 1>>>::type>;

class State : public peel::Object {
  PEEL_SIMPLE_CLASS(State, peel::Object)
  tpsystem selected_time;

public:
  tpsystem get_selected_time() const;
  void move_a_week(int modifier);
  void reset_time();

  PEEL_PROPERTY(tpsystem, selected_time, "selected_time")

  PEEL_SIGNAL_CONNECT_METHOD(changed, sig_changed)

private:
  template <typename F> static void define_properties(F &f);
  static peel::Signal<State, void(void)> sig_changed;
};
} // namespace Hyprtracker
