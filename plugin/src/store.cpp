#include "store.hpp"
#include "globals.hpp"
#include <exception>

Store::Store()
    : db(std::format("{}{}/storage.db", std::getenv("HOME"), STORAGE_LOCATION),
         SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {}

void Store::init() {
  SQLite::Transaction tx(db);
  try {
    db.exec("CREATE TABLE IF NOT EXISTS durations(window TEXT, duration "
            "INTEGER, date INTEGER default (unixepoch()))");

    tx.commit();
  } catch (std::exception e) {
    tx.rollback();
    std::cout << "exception creating: " << e.what() << std::endl;
  }
}

void Store::storeWindowChange(std::string window, int duration) {
  if (window.empty())
    return;
  SQLite::Transaction tx(db);
  try {
    std::cout << "Window switched from: " << window
              << " was active for: " << duration << "s" << std::endl;
    SQLite::Statement query(
        db, "INSERT INTO durations(window, duration) VALUES (?, ?)");
    query.bind(1, window);
    query.bind(2, duration);

    query.exec();

    tx.commit();
  } catch (std::exception e) {
    tx.rollback();
    std::cout << "exception saving: " << e.what() << std::endl;
  }
}
