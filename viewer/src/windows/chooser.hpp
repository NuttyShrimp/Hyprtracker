#include <gtkmm/button.h>
#include <gtkmm/centerbox.h>
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
};
