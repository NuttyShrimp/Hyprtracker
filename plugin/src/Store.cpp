//
// Created by janle on 18/05/24.
//

#include "Store.hpp"
#include <SQLiteCpp/SQLiteCpp.h>
#include <chrono>
#include <cstddef>
#include <iostream>

void Store::init() {
  auto db =
      SQLite::Database(std::format("{}/.local/share/hyprtracker/durations.db",
                                   std::getenv("HOME")),
                       SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  db.exec("CREATE TABLE IF NOT EXISTS durations (window TEXT, duration "
          "INTEGER, date INTEGER default (unixepoch()));");
  // Should be stored in ~/.local/share/hyprtracker/durations
  // if (!exists(m_storePath)) {
  //     create_directories(m_storePath.parent_path());
  // };

  // m_endpoint = std::any_cast<Hyprlang::STRING>(HyprlandAPI::getConfigValue(
  //         PHANDLE, "plugin:hyprtracker:endpoint")->
  //     getValue());
}

void Store::saveDuration(const std::string &windowName,
                         std::chrono::seconds duration) {
  if (duration.count() == 0) {
    return;
  }

  std::lock_guard lock(m_mutex);
  auto db =
      SQLite::Database(std::format("{}/.local/share/hyprtracker/durations.db",
                                   std::getenv("HOME")),
                       SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

  try {
    SQLite::Transaction transaction(db);
    SQLite::Statement query(
        db, "INSERT INTO durations (window, duration) VALUES (?, ?);");
    query.bind(1, windowName);
    query.bind(2, duration.count());
    query.exec();

    transaction.commit();
  } catch (std::exception &e) {
    std::cerr << "Failed to save duration to the database: " << e.what()
              << std::endl;
  }
  // std::ofstream file(m_storePath, std::ios::app);
  // if (!file.is_open()) {
  //     std::cerr << "Failed to open store file while saving durations" <<
  //     std::endl; m_missed_durations.insert(std::pair{windowName,
  //     duration.count()}); return;
  // }
  //
  // file << windowName << " " << duration.count() << std::endl;
  //
  // if (!m_missed_durations.empty()) {
  //     save_missing_durations(file);
  // }
  //
  // file.close();
}

void Store::save_missing_durations(std::ofstream &file) {
  for (auto &duration : m_missed_durations) {
    file << duration.first << " " << duration.second << std::endl;
  }
  m_missed_durations.clear();
}

// void Store::push_to_server() {
//     auto durations = get_merged_durations();
// }
//
// std::map<std::string, size_t> Store::get_merged_durations() {
//     std::lock_guard lock(m_mutex);
//
//     std::ifstream inStream(m_storePath);
//     if (!inStream.is_open()) {
//         std::cerr << "Failed to open store file while merging" << std::endl;
//     }
//
//     std::map<std::string, size_t> durations;
//
//     std::string line;
//     while(getline(inStream, line)) {
//         // Split at last space
//         auto pos = line.find_last_of(' ');
//         auto windowName = line.substr(0, pos);
//         std::stringstream durationStream(line.substr(pos + 1));
//         size_t duration;
//         durationStream >> duration;
//
//         if (durations.contains(windowName)) {
//             durations[windowName] += duration;
//         } else {
//             durations.insert({windowName, duration});
//         }
//     }
//
//     inStream.close();
//
//     std::fstream truncStream(m_storePath, std::ios::trunc);
//
//     if (!truncStream.is_open()) {
//         std::cerr << "Failed to truncate store file" << std::endl;
//     }
//     truncStream.close();
//
//     return durations;
// }
