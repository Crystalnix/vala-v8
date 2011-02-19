cmake_minimum_required (VERSION 2.6)
project (vala-v8)

set(V8_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../v8")

link_directories(${V8_PATH})

add_subdirectory (v8-bindings)
add_subdirectory (test)
