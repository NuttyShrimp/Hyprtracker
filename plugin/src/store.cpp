#include "store.hpp"
#include "globals.hpp"
#include <cstdlib>
#include <format>

Store::Store()
    : db(std::format("{}{}/storage.db", std::getenv("HOME"),
                     STORAGE_LOCATION)) {}
