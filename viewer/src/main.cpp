#include "adwaita.h"
#include "gio/gio.h"
#include "viewer.h"

int main(int argc, char *argv[]) {
  auto app = adw_application_new("org.nuttyshrimp.hyprtracker.viewer",
                                 G_APPLICATION_DEFAULT_FLAGS);
  app->signal_activate().connect([app]() {
    auto window = new Viewer();
    window->init();
    app->add_window(*window);
    window->present();
  });
  app->run(argc, argv);
  return 0;
}
