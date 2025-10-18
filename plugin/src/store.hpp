#pragma once
#include "SQLiteCpp/SQLiteCpp.h"

class Store {
public:
  Store();
  ~Store() = default;

  void init();
  void storeWindowChange(std::string window, int duration);

private:
  SQLite::Database db;
};
