#include "widgetManager.hpp"

WidgetManager::WidgetManager() : m_current_widget(nullptr) {}

void WidgetManager::set_current_widget(Gtk::Widget *widget) {
  m_current_widget = widget;
  m_current_widget_changed();
};

Gtk::Widget &WidgetManager::get_current_widget() { return *m_current_widget; }

sigslot::signal<> &WidgetManager::signal_widget_changed() {
  return m_current_widget_changed;
}
