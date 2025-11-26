#pragma once
#include "state.h"
#include <peel/Adw/Adw.h>
#include <peel/Gio/Gio.h>
#include <peel/Gtk/Gtk.h>
#include <peel/RefPtr.h>
#include <peel/class.h>

using namespace peel;

namespace Hyprtracker {
class Window final : public Adw::ApplicationWindow {
  PEEL_SIMPLE_CLASS(Window, Adw::ApplicationWindow)

  RefPtr<Gtk::Label> m_week_label;
  RefPtr<State> m_state;

  inline void init(Class *);

public:
  static Window *create(Gtk::Application *app) {
    Window *window = Object::create<Window>(prop_application(), app);
    return window;
  }

private:
  void create_date_selector(FloatPtr<Gtk::Box> panel);
  void update_week_label();
};
} // namespace Hyprtracker
