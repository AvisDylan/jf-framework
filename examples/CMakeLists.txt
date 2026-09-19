set(SOURCES 
    src/main.c
)

add_executable(jf-example ${SOURCES})

target_link_libraries(jf-example PRIVATE jf-framework)

