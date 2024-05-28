#pragma once

#include "windows/chooser.hpp"
#include <gtkmm/window.h>

class Viewer : public Gtk::Window {

public:
  Viewer();
  ~Viewer() override;

  void onWidgetChanged();

protected:
  Chooser m_chooser;
};
