cmake_minimum_required(VERSION 3.10)

project(garden VERSION 0.1 LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(MSVC)
else()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -pedantic")
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
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/platforms/osx.mm)
endif(APPLE)

if(MSVC)
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/platforms/win64.cpp)
endif(MSVC)

# message(${SRC})

set(TARGET garden)

add_executable(${TARGET} ${SOURCES} ${HEADERS})

if(APPLE)
    target_link_libraries(${TARGET} PRIVATE "-framework Cocoa")
endif()
