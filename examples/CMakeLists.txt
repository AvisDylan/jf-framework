set(SOURCES 
    src/main.c
)

add_executable(jf-example ${SOURCES})

target_include_directories(jf-example PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(jf-example PRIVATE jf-framework)

