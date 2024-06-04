#pragma once

#include <gtkmm/drawingarea.h>
#include <gtkmm/overlay.h>
#include <map>
#include <string>
#include <vector>

class Bar : public Gtk::DrawingArea {};

class BarChart : public Gtk::Overlay {
public:
  BarChart(std::map<std::string, double> data);

private:
  std::vector<Bar> m_bars;
  std::map<std::string, double> m_data;

  void create_grid_bg();

  void add_bar(Bar bar);
};
