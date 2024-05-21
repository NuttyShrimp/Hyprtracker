#pragma once

#include "chooser.hpp"
#include <gtkmm/button.h>
#include <gtkmm/flowbox.h>

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
}

Chooser::~Chooser() {}
