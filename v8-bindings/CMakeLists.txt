include_directories(${V8_PATH}/include)

add_library(v8-bindings SHARED v8c.cc v8c.h v8c-private.h)
target_link_libraries (v8-bindings v8)