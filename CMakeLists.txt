cmake_minimum_required(VERSION 3.10)

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

if(APPLE)
    project(garden VERSION 0.1 LANGUAGES CXX OBJCXX)
else()
    project(garden VERSION 0.1 LANGUAGES CXX)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(MSVC)
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -pedantic -g -O3")
endif()

file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/shared/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/shared/*.h"
)

if(APPLE)
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/macos/macos.mm)
endif(APPLE)

if(MSVC)
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/windows/win64.cpp)
endif(MSVC)

if(LINUX)
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/linux/linux.cpp)
endif(LINUX)

set(TARGET garden)

add_executable(${TARGET} ${SOURCES})

if(APPLE)
    target_link_libraries(${TARGET} PRIVATE "-framework Cocoa")
elseif(LINUX)
    target_link_libraries(${TARGET} PRIVATE "-lX11")
endif()
