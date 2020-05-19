cmake_minimum_required(VERSION 3.1..3.15)

project(sandbox VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/platform.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/engine.h
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/engine.cpp
)

if(APPLE)
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/osx.mm)
endif(APPLE)

# message(${SRC})

add_executable(sandbox ${SOURCES} ${HEADERS})
