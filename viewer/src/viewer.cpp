#include "viewer.hpp"
#include "managers/alertManager.hpp"
#include "managers/widgetManager.hpp"

Viewer::Viewer() : m_chooser() {
  set_title("Hyperland Usage Statistics");

  set_child(m_chooser);

  auto &alertManager = AlertBoxManager::instance();
  alertManager.init(this);
  WidgetManager::instance().signal_widget_changed().connect(
      &Viewer::onWidgetChanged, this);
}

Viewer::~Viewer() = default;

void Viewer::onWidgetChanged() {
  set_child(WidgetManager::instance().get_current_widget());
}
