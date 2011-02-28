include(ValaPrecompile)

#vala_precompile(VALA_C
#    vala_getting_started.vala
#PACKAGES
#    gobject-2.0
#CUSTOM_VAPIS
#    ${CMAKE_SOURCE_DIR}/vala-api/v8c.vapi
#)

vala_precompile(GITEST_C
    gitest.vala
PACKAGES
    gobject-2.0
CUSTOM_VAPIS
    ${CMAKE_BINARY_DIR}/vala-api/jslib.vapi
    ${CMAKE_SOURCE_DIR}/vala-api/v8c.vapi
)

#add_executable(vala_getting_started ${VALA_C})
#target_link_libraries (vala_getting_started v8-bindings)

include_directories(${CMAKE_BINARY_DIR}/vala-api)
link_directories(${CMAKE_BINARY_DIR}/vala-api)

add_executable(gitest ${GITEST_C})
target_link_libraries (gitest jslib)
