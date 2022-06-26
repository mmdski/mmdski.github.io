add_executable(mmdski
    sine.c)

target_link_options(mmdski PRIVATE
    "-sEXPORTED_FUNCTIONS=[\"_calloc\", \"_malloc\", \"_free\" ]")

# "-sINITIAL_MEMORY=33554432")
install(FILES
    "$<TARGET_FILE_DIR:mmdski>/mmdski.js"
    "$<TARGET_FILE_DIR:mmdski>/mmdski.wasm"
    DESTINATION ${CMAKE_SOURCE_DIR}/assets/js)
