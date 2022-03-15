cmake_minimum_required(VERSION 3.17)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

file(GLOB CORE
        ${PROJECT_SOURCE_DIR}/src/core/*.cpp
)

file(GLOB SDL
    ${PROJECT_SOURCE_DIR}/src/sdl/*.cpp
)

file(GLOB NCURSES
    ${PROJECT_SOURCE_DIR}/src/ncurses/*.cpp
)

add_library(ncurses SHARED ${NCURSES})

add_library(sdl2 SHARED ${SDL})

set_target_properties(sdl2 PROPERTIES PREFIX "arcade_" SUFFIX ".so" LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
set_target_properties(ncurses PROPERTIES PREFIX "arcade_" SUFFIX ".so" LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib" CMAKE_SHARED_LINKER_FLAGS "-lcurses")

add_executable(arcade ${CORE})

set_target_properties(arcade PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}")
