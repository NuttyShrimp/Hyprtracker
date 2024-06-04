#pragma once

#include <gtkmm/button.h>
#include <gtkmm/centerbox.h>
#include <gtkmm/filedialog.h>
#include <gtkmm/flowbox.h>

class Chooser : public Gtk::CenterBox {
public:
  Chooser();
  ~Chooser() override;

private:
  Gtk::CenterBox m_centeredButtonBox;
  Gtk::FlowBox m_buttonBox;
  Gtk::Button m_openDefaultButton;
  Gtk::Button m_chooseLocButton;

  void onOpenDefaultButtonClicked();
  void onSelectFileButtonClicked();
  void onFileSelected(const Glib::RefPtr<Gio::AsyncResult> &result,
                      const Glib::RefPtr<Gtk::FileDialog> &dialog);
};
