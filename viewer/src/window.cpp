#include "window.h"
#include "peel/Gtk/Box.h"
#include "peel/RefPtr.h"
#include <format>

using namespace peel;

namespace Hyprtracker {
PEEL_CLASS_IMPL(Window, "MainWindow", Adw::ApplicationWindow)

inline void Window::Class::init() {
  add_binding_action(GDK_KEY_T, Gdk::ModifierType::CONTROL_MASK, "win.new-tab",
                     nullptr);
  add_binding_action(GDK_KEY_W, Gdk::ModifierType::CONTROL_MASK,
                     "win.close-tab", nullptr);
}

inline void Window::init(Class *) {
  set_title("Hyprtracker Viewer");
  set_default_size(700, 500);
  m_state = Object::create<State>();

  FloatPtr<Adw::HeaderBar> header_bar = Adw::HeaderBar::create();
  FloatPtr<Adw::WindowTitle> window_title =
      Adw::WindowTitle::create("Hyprtracker Viewer", "");
  header_bar->set_title_widget(std::move(window_title));

  RefPtr<Gio::Menu> menu = Gio::Menu::create();
  menu->append("New Window", "app.new-window");
  menu->append("About", "app.about");
  menu->append("Quit", "app.quit");
  FloatPtr<Gtk::PopoverMenu> popover_menu =
      Gtk::PopoverMenu::create_from_model(menu);

  // Menu button
  FloatPtr<Gtk::MenuButton> menu_button = Gtk::MenuButton::create();
  menu_button->set_popover(std::move(popover_menu));
  menu_button->set_icon_name("open-menu-symbolic");
  menu_button->set_tooltip_text("Menu");
  menu_button->set_focus_on_click(false);
  header_bar->pack_end(std::move(menu_button));

  FloatPtr<Gtk::Box> main_panel =
      Gtk::Box::create(Gtk::Orientation::VERTICAL, 0);
  RefPtr<Gtk::Box> main_panel_ref = main_panel;
  create_date_selector(main_panel_ref);

  FloatPtr<Adw::ToolbarView> toolbar_view = Adw::ToolbarView::create();
  toolbar_view->set_top_bar_style(Adw::ToolbarStyle::RAISED);
  toolbar_view->add_top_bar(std::move(header_bar));
  toolbar_view->set_content(std::move(main_panel));

  set_content(std::move(toolbar_view));
}

void Window::create_date_selector(FloatPtr<Gtk::Box> panel) {
  auto box = Gtk::Box::create(Gtk::Orientation::HORIZONTAL, 8);
  box->set_halign(Gtk::Align::END);
  box->set_margin_bottom(12);
  box->set_margin_end(12);
  box->set_margin_start(12);
  box->set_margin_top(12);

  m_week_label = Gtk::Label::create("Today").ref_sink();
  // Connect the State's 'changed' signal to a lambda that updates the label.
  // The signal will pass the State* instance; ignore it and call the member.
  m_state->connect_changed([this](State *) { update_week_label(); });
  // Update label initially.
  update_week_label();
  box->append(m_week_label);

  auto prev_btn = Gtk::Button::create_from_icon_name("go-previous");
  prev_btn->connect_clicked(
      [state = m_state](Gtk::Button *) { state->move_a_week(-1); });
  box->append(std::move(prev_btn));

  auto today_btn = Gtk::Button::create_with_label("This week");
  today_btn->connect_clicked(
      [state = m_state](Gtk::Button *) { state->reset_time(); });
  box->append(std::move(today_btn));

  auto next_btn = Gtk::Button::create_from_icon_name("go-next");
  next_btn->connect_clicked(
      [state = m_state](Gtk::Button *) { state->move_a_week(1); });
  box->append(std::move(next_btn));

  panel->append(std::move(box));
}

void Window::update_week_label() {
  m_week_label->set_text(
      std::format("{:%Y/%m/%d}", m_state->get_selected_time()).c_str());
}

} // namespace Hyprtracker
