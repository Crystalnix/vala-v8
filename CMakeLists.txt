cmake_minimum_required (VERSION 2.6)
project (vala-v8)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/vala-cmake
)

find_package(Vala REQUIRED)

set(V8_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../v8")

link_directories(${V8_PATH})
include_directories("${CMAKE_SOURCE_DIR}/v8-bindings")

find_package(PkgConfig)
pkg_check_modules(GO REQUIRED gobject-2.0)
add_definitions(${GO_CFLAGS} ${GO_CFLAGS_OTHER})
link_libraries(${GO_LIBRARIES})
link_directories(${GO_LIBRARY_DIRS})

add_subdirectory (v8-bindings)
add_subdirectory (test)
add_subdirectory (vala-test)
