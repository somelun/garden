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

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/math/vec.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/math/mat.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/engine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/object.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/framebuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/scenes/test_scene.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/renderer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/loader.h
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/math/mat.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/object.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/scenes/test_scene.cpp
)

if(APPLE)
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/platforms/macos.mm)
endif(APPLE)

if(MSVC)
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/platforms/win64.cpp)
endif(MSVC)

if(LINUX)
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/platforms/linux.cpp)
endif(LINUX)

set(TARGET garden)

add_executable(${TARGET} ${SOURCES} ${HEADERS})

if(APPLE)
    target_link_libraries(${TARGET} PRIVATE "-framework Cocoa")
elseif(LINUX)
    target_link_libraries(${TARGET} PRIVATE "-lX11")
endif()
