#include "viewer.hpp"

Viewer::Viewer() : m_chooser() {
  set_title("Hyperland Usage Statistics");

  set_child(m_chooser);
}

Viewer::~Viewer() {}
