//
// Created by janle on 31/10/2025.
//

#include "viewer.h"

#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/label.h>

Viewer::Viewer() : m_state(std::make_shared<::State>())
{
    set_title("Hyprtracker Viewer");
    set_default_size(200, 200);
}

void Viewer::init()
{
    auto header = Gtk::HeaderBar();
    set_titlebar(header);

    auto child = Gtk::Box(Gtk::Orientation::VERTICAL);

    set_child(child);
    create_date_selector();
}

void Viewer::create_date_selector()
{
    auto box = Gtk::Box(Gtk::Orientation::HORIZONTAL);
    box.set_halign(Gtk::Align::END);
    box.set_spacing(8);
    box.set_margin(12);

    m_week_label = Gtk::Label();
    m_state->signal_change().connect(sigc::mem_fun(*this, &Viewer::set_week_label));
    set_week_label();
    box.append(m_week_label);

    auto prev_btn = Gtk::Button();
    prev_btn.set_icon_name("go-previous");
    prev_btn.signal_clicked().connect([this]
    {
        m_state->move_a_week(-1);
    });
    box.append(prev_btn);

    auto today_btn = Gtk::Button();
    today_btn.set_label("This week");
    today_btn.signal_clicked().connect([this]
    {
        m_state->reset_time();
    });
    box.append(today_btn);

    auto next_btn = Gtk::Button();
    next_btn.set_icon_name("go-next");
    next_btn.signal_clicked().connect([this]
    {
        m_state->move_a_week(1);
    });
    box.append(next_btn);

    auto ct = dynamic_cast<Gtk::Box*>(get_child());
    ct->append(box);
}

void Viewer::set_week_label()
{
    m_week_label.set_text(std::format("{:%Y/%m/%d}", m_state->selected_time));
}
