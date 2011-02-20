include(ValaPrecompile)

vala_precompile(VALA_C
    vala_getting_started.vala
PACKAGES
    gobject-2.0
CUSTOM_VAPIS
    ${CMAKE_SOURCE_DIR}/vala-api/v8c.vapi
)

add_executable(vala_getting_started ${VALA_C})
target_link_libraries (vala_getting_started v8-bindings)
