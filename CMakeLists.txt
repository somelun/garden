cmake_minimum_required(VERSION 3.10)

project(sandbox VERSION 0.1 LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/engine.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/framebuffer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/math/vector3.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/scene/base_scene.h
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/framebuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/scene/base_scene.cpp
)

if(APPLE)
    set(SOURCES ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/osx.mm)
endif(APPLE)

# message(${SRC})

set(TARGET sandbox)

add_executable(${TARGET} ${SOURCES} ${HEADERS})

if(APPLE)
    target_link_libraries(${TARGET} PRIVATE "-framework Cocoa")
endif()
