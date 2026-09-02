cmake_minimum_required(VERSION 4.3)

project(jf-framework LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SOURCES 
    src/server.c
    src/router.c
    src/http.c
)

set(HEADERS
    include/server.h
    include/router.h
    include/http.h
)

add_library(jf-framework SHARED ${SOURCES} ${HEADERS})

target_include_directories(jf-framework PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
