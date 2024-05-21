#include "viewer.hpp"
#include <gtkmm/application.h>

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create("com.nutty.hyprtracker");

  // Shows the window and returns when it is closed.
  return app->make_window_and_run<Viewer>(argc, argv);
}
