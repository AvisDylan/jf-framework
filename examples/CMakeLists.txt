set(SOURCES 
    src/main.c
)

add_executable(jf-example ${SOURCES})

# Add resources to output
add_custom_command(TARGET jf-example POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:jf-example>/resources
)


target_link_libraries(jf-example PRIVATE jf-framework)

