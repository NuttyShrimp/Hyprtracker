#include "chooser.hpp"
#include "../managers/alertManager.hpp"
#include "../managers/dbManager.hpp"
#include "../managers/singleton.hpp"
#include "../managers/widgetManager.hpp"
#include "../windows/daily.hpp"
#include <filesystem>
#include <gtkmm/button.h>
#include <gtkmm/flowbox.h>
#include <iostream>

using namespace std::filesystem;

Chooser::Chooser()
    : m_centeredButtonBox(), m_buttonBox(),
      m_openDefaultButton("Open from default location"),
      m_chooseLocButton("Choose DB file") {
  m_buttonBox.set_orientation(Gtk::Orientation::VERTICAL);
  m_buttonBox.set_column_spacing(10);

  m_buttonBox.insert(m_openDefaultButton, -1);
  m_buttonBox.insert(m_chooseLocButton, -1);

  m_centeredButtonBox.set_orientation(Gtk::Orientation::HORIZONTAL);
  m_centeredButtonBox.set_center_widget(m_buttonBox);

  set_orientation(Gtk::Orientation::VERTICAL);
  set_center_widget(m_centeredButtonBox);

  m_openDefaultButton.signal_clicked().connect(
      sigc::mem_fun(*this, &Chooser::onOpenDefaultButtonClicked));
  m_chooseLocButton.signal_clicked().connect(
      sigc::mem_fun(*this, &Chooser::onSelectFileButtonClicked));
}

Chooser::~Chooser() {}

void Chooser::onOpenDefaultButtonClicked() {
  auto defaultPath =
      path(std::getenv("HOME")) / ".local/share/hyprtracker/durations.db";
  if (!exists(defaultPath)) {
    AlertBoxManager::instance().show_message("Default database not found",
                                             "No file found at " +
                                                 defaultPath.string());
    return;
  }
  DbManager::instance().set_db_path(defaultPath);
  auto dailyScreen = new Daily();
  WidgetManager::instance().set_current_widget(dailyScreen);
  std::cout << "Opened default database at " << defaultPath << std::endl;
}

void Chooser::onSelectFileButtonClicked() {}
