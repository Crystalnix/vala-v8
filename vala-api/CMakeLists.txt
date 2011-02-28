include(ValaPrecompile)

vala_precompile(VALA_API_C
    importer.vala
PACKAGES
    gobject-2.0
CUSTOM_VAPIS
    ${CMAKE_SOURCE_DIR}/vala-api/v8c.vapi
    ${CMAKE_SOURCE_DIR}/vala-api/girepository.vapi
GENERATE_VAPI
    jslib
GENERATE_HEADER
    jslib
)

add_library(jslib SHARED ${VALA_API_C})
target_link_libraries (jslib v8-bindings)