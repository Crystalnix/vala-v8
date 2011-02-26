include_directories(${V8_PATH}/include)

add_library(test-bindings SHARED v8c.cc v8c.h v8c-private.h)
target_link_libraries (test-bindings v8)

add_executable(test test.c)
target_link_libraries (test test-bindings)
