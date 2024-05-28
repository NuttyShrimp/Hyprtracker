#include "alertManager.hpp"
#include <gtkmm/alertdialog.h>

AlertBoxManager::AlertBoxManager() {}

void AlertBoxManager::init(Gtk::Window *window) { m_window = window; }

void AlertBoxManager::show_message(const std::string &title,
                                   const std::string &message) {
  auto dialog = Gtk::AlertDialog::create();
  dialog->set_message(title);
  dialog->set_detail(message);
  dialog->show(*m_window);
}
