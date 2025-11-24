//
// Created by janle on 31/10/2025.
//

#ifndef VIEWER_VIEWER_H
#define VIEWER_VIEWER_H
#include <adwaita.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/label.h>
#include <memory>

#include "state.h"

class Viewer : public Gtk::ApplicationWindow {
public:
  Viewer();
  void init();

private:
  void create_date_selector();
  void set_week_label();
  std::shared_ptr<::State> m_state;
  Gtk::Label m_week_label;
};

#endif // VIEWER_VIEWER_H
