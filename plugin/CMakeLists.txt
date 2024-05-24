cmake_minimum_required(VERSION 3.15)
set(CMAKE_PROJECT_TOP_LEVEL_INCLUDES conan_provider.cmake)

project("hyprtracker" LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compile flags
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC "src/*.cpp")

add_library(hyprtracker SHARED ${SRC})

find_package(PkgConfig REQUIRED)
pkg_check_modules(DEPS REQUIRED hyprland pixman-1 libdrm)

find_package(SQLiteCpp REQUIRED)

add_compile_definitions(WLR_USE_UNSTABLE)

target_link_libraries(hyprtracker SQLiteCpp)
target_include_directories(hyprtracker PRIVATE ${DEPS_INCLUDE_DIRS})

install(TARGETS hyprtracker)
