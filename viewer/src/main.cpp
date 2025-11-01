#include "viewer.h"
#include "gtkmm-4.0/gtkmm.h"


int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.nuttyshrimp.hyprtracker.viewer");
    app->signal_activate().connect([app]()
    {
        auto window = new Viewer();
        window->init();
        app->add_window(*window);
        window->present();
    });
    app->run(argc, argv);
    return 0;
}
