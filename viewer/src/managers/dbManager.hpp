#include "singleton.hpp"
#include <filesystem>
#include <string>

using namespace std::filesystem;

class DbManager : public Singleton<DbManager> {
  friend class Singleton;

public:
  void set_db_path(path &path);

protected:
  DbManager();

private:
  path m_db_path;
};
