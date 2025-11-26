#include "application.h"

int main(int argc, char *argv[]) {
  RefPtr<Hyprtracker::Application> app = Hyprtracker::Application::create();
  return app->run(argc, argv);
}
