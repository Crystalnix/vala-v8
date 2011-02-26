cmake_minimum_required (VERSION 2.6)
project (vala-v8)

list(APPEND CMAKE_MODULE_PATH
    ${CMAKE_SOURCE_DIR}/vala-cmake
)

find_package(Vala REQUIRED)

set(V8_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../v8")

find_package(PkgConfig)
pkg_check_modules(GO REQUIRED gobject-2.0 glib-2.0 gobject-introspection-1.0)

include_directories("${CMAKE_SOURCE_DIR}/test-bindings" ${GO_INCLUDE_DIRS})
link_directories(${V8_PATH} ${GO_LIBRARY_DIRS})

link_libraries(${GO_LIBRARIES})

add_subdirectory (test-bindings)
