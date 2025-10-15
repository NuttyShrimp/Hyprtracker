#pragma once
#include "SQLiteCpp/SQLiteCpp.h"

class Store {
public:
  Store();
  ~Store() = default;

private:
  SQLite::Database db;
};
