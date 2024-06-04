cmake_minimum_required(VERSION 3.20)
project(hyprtracker-viewer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET gtkmm-4.0 gtk4 glibmm-2.68 cairomm-1.16 pangomm-2.48)
find_package(PalSigslot REQUIRED)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS src/*.cpp)
add_executable(hyprtracker-viewer ${SRC})

target_link_libraries(hyprtracker-viewer PUBLIC PkgConfig::deps Pal::Sigslot)

# add_executable(hyprtracker-viewer src/main.cpp)
install(TARGETS hyprtracker-viewer)
