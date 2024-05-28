#pragma once

#include "singleton.hpp"
#include <gtkmm/widget.h>
#include <sigslot/signal.hpp>

class WidgetManager : public Singleton<WidgetManager> {
  friend class Singleton;

public:
  void set_current_widget(Gtk::Widget *widget);
  Gtk::Widget &get_current_widget();
  sigslot::signal<> &signal_widget_changed();

protected:
  WidgetManager();

private:
  Gtk::Widget *m_current_widget;
  sigslot::signal<> m_current_widget_changed;
};
