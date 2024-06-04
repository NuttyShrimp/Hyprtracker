#include "barChart.hpp"
#include <format>
#include <glibmm/value.h>
#include <gtkmm/box.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/grid.h>
#include <gtkmm/textview.h>

BarChart::BarChart(std::map<std::string, double> data) : m_data(data) {
  // Generate the grid BG
  create_grid_bg();
}

void BarChart::create_grid_bg() {
  // Grid should be 5 * data.size() as row x col
  Gtk::Grid *grid = new Gtk::Grid();
  // grid->set_row_homogeneous(true);
  // grid->set_column_homogeneous(true);

  for (int i = 0; i < 5; i++) {
    grid->insert_row(i);
  }
  for (int i = 0; i < m_data.size(); i++) {
    grid->insert_column(i);
  }

  // #4b5563
  Glib::ustring data = ".cell {border: 2px solid green background-image: none; "
                       "background-color: red;}";
  auto provider = Gtk::CssProvider::create();
  provider->load_from_data(data);

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < m_data.size(); j++) {
      Gtk::Box *widget = new Gtk::Box();
      widget->set_size_request(200, 100);
      widget->get_style_context()->add_class("cell");
      widget->get_style_context()->add_provider(
          provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

      auto border = widget->get_style_context()->get_border();
      border.set_top(1);
      border.set_left(1);
      border.set_right(1);
      border.set_bottom(1);
      Gtk::TextView *label = new Gtk::TextView();
      label->get_buffer()->set_text(std::format("{} {}", i, j));
      widget->get_children().push_back(label);
      grid->attach(*widget, j, i, 1, 1);
    }
  }

  set_child(*grid);
  // Gtk::TextView *label = new Gtk::TextView();
  // label->get_buffer()->set_text("Test label");
  // add_overlay(*label);
}
