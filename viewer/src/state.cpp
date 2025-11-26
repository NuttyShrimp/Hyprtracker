#include "state.h"

namespace Hyprtracker {
peel::Signal<State, void(void)> State::sig_changed;

PEEL_CLASS_IMPL(State, "State", Object)

void State::Class::init() {
  sig_changed = peel::Signal<State, void(void)>::create("state_changed");
}

tpsystem State::get_selected_time() const { return selected_time; }

static tpsystem get_start_of_week_time() {
  auto now = std::chrono::system_clock::now();
  std::chrono::year_month_weekday ymw{
      std::chrono::floor<std::chrono::days>(now)};
  auto start_of_week =
      now - std::chrono::days{ymw.weekday().iso_encoding() - 1};
  return start_of_week;
}

void State::move_a_week(int modifier) {
  std::chrono::days d{7 * modifier};
  selected_time = selected_time + d;
  sig_changed.emit(this);
}

void State::reset_time() {
  selected_time = get_start_of_week_time();
  sig_changed.emit(this);
}

template <typename F> void State::define_properties(F &f) {
  // Do not register `selected_time` as a GObject property because the
  // property/value marshalling does not provide traits for
  // std::chrono::time_point. If a GObject property is required, expose an
  // integer (e.g. epoch seconds) and convert in getter/setter wrappers. For
  // now, leave empty.
  (void)f;
}
} // namespace Hyprtracker
