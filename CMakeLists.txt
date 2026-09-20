cmake_minimum_required(VERSION 4.3)

project(jf-framework VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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

find_package(OpenSSL CONFIG REQUIRED)

add_library(jf-framework SHARED ${SOURCES} ${HEADERS})

target_include_directories(jf-framework PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(jf-framework PRIVATE
    OpenSSL::SSL
    OpenSSL::Crypto
)

target_compile_definitions(jf-framework PUBLIC
    FRAMEWORK_VERSION="${PROJECT_VERSION}"
)

target_compile_options(jf-framework PRIVATE
    -O2
    -g3
    -fno-omit-frame-pointer
    -frecord-gcc-switches
    -DNDEBUG
    -D_FORTIFY_SOURCE=2
    -fstack-protector-all
    -fstack-clash-protection
    -fcf-protection=full
    -fno-delete-null-pointer-checks
    -fwrapv
    -fno-common
    -flto
    -Wall -Wextra -Wpedantic
    -Wshadow -Wconversion -Wformat=2 -Wformat-security
    -Wmissing-prototypes -Wstrict-prototypes -Wredundant-decls
    -Wundef -Wpointer-arith -Wcast-align -Wcast-function-type
    -Wnull-dereference -Wimplicit-fallthrough=4
    -Wvla
)

target_link_options(jf-framework PRIVATE
    -flto
    -Wl,-z,relro
    -Wl,-z,now
    -Wl,-z,noexecstack
    -Wl,-z,defs
    -Wl,-O1
)

add_subdirectory(examples)
