cmake_minimum_required(VERSION 3.23)
project(type_erasure)

set(CMAKE_CXX_STANDARD 23)

add_executable(old_poly old_poly.cpp)
add_executable(upgrade upgrade.cpp)
add_executable(final final.cpp)
