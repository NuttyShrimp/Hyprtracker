#pragma once

#include "singleton.hpp"
#include <gtkmm/window.h>

class AlertBoxManager final : public Singleton<AlertBoxManager> {
  friend class Singleton;

public:
  void init(Gtk::Window *window);

  void show_message(const std::string &title, const std::string &message);

protected:
private:
  AlertBoxManager();

  Gtk::Window *m_window = nullptr;
};
