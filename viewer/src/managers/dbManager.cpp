#include "dbManager.hpp"

using namespace std::filesystem;

DbManager::DbManager() : m_db_path("") {}

void DbManager::set_db_path(path &path) { m_db_path = path; }
