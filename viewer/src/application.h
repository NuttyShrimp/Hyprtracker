#pragma once
#include <peel/Adw/Adw.h>
#include <peel/GLib/functions.h>
#include <peel/Gio/Gio.h>
#include <peel/Gtk/Gtk.h>
#include <peel/class.h>

using namespace peel;

namespace Hyprtracker {
class Application final : public Adw::Application {
  PEEL_SIMPLE_CLASS(Application, Adw::Application)
  friend class Gio::Application;

  inline void init(Class *);

  inline void vfunc_activate();

  void action_quit(Gio::SimpleAction *, GLib::Variant *);

  void action_about(Gio::SimpleAction *, GLib::Variant *);

public:
  static RefPtr<Application> create() {
    return Object::create<Application>(
        prop_application_id(), "org.nuttyshrimp.hyprtracker.viewer",
        prop_flags(), Gio::Application::Flags::DEFAULT_FLAGS);
  }
};
} // namespace Hyprtracker
