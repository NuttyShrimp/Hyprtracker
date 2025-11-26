#include "application.h"
#include "window.h"

namespace Hyprtracker {
PEEL_CLASS_IMPL(Application, "HyprtrackerApplication", Adw::Application)

inline void Application::init(Class *) {
  RefPtr<Gio::SimpleAction> action = Gio::SimpleAction::create("quit", nullptr);
  action->connect_activate(this, &Application::action_quit);
  cast<Gio::ActionMap>()->add_action(action);
  set_accels_for_action("app.quit", (const char *[]){"<Ctrl>Q", nullptr});

  action = Gio::SimpleAction::create("about", nullptr);
  action->connect_activate(this, &Application::action_about);
  cast<Gio::ActionMap>()->add_action(action);
}

inline void Application::Class::init() {
  override_vfunc_activate<Application>();
}

inline void Application::vfunc_activate() {
  parent_vfunc_activate<Application>();

  Window *window = Window::create(this);
  window->present();
}

void Application::action_quit(Gio::SimpleAction *, GLib::Variant *) { quit(); }

void Application::action_about(Gio::SimpleAction *, GLib::Variant *) {
  Gtk::Window *parent_window = get_active_window();
  // if (parent_window && !parent_window->check_type<Window>())
  //   parent_window = nullptr;

  Adw::show_about_dialog(
      parent_window, Adw::AboutDialog::prop_application_name(),
      "Hyprtracker data visualizer", Adw::AboutDialog::prop_application_icon(),
      "application-x-executable", Adw::AboutDialog::prop_version(), "0.1",
      Adw::AboutDialog::prop_license_type(), Gtk::License::MIT_X11,
      Adw::AboutDialog::prop_comments(),
      "A simple application demonstrating how Adwaita can be used from C++ "
      "with peel.",
      Adw::AboutDialog::prop_issue_url(),
      "https://github.com/nuttyshrimp/hyprtracker/issues",
      Adw::AboutDialog::prop_developers(),
      (const char *[]){"Jan Lecoutere <jan@lecoutere.dev>", nullptr});
}
} // namespace Hyprtracker
