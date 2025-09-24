cmake_minimum_required(VERSION 3.15)
project(pacman VERSION 0.1.0 LANGUAGES CXX) 

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")

find_package(Curses REQUIRED)

set(SOURCES
    src/main.cpp
    src/engine/ncurses.cpp
    src/engine/stateManager.cpp
    src/engine/window.cpp
    src/engine/menu.cpp
    src/engine/direction.cpp
    src/game/states/mainMenuState.cpp
    src/game/states/gameState.cpp
    src/game/states/pauseState.cpp
    src/game/board.cpp
    src/game/boardUtils.cpp
    src/game/player.cpp
    src/game/ghost.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES}) 

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${CURSES_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ${CURSES_LIBRARIES}
)
