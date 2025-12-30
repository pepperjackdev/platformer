cmake_minimum_required(VERSION 3.15)
project(platformer CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# TODO: should be avoided;
#       do not provide multiple `main` functions
file(GLOB GAME_SRC_FILES
    "src/platformer/**/*.cpp"
    "src/platformer/*.cpp"
)

file(GLOB EDITOR_SRC_FILES
    "src/editor/**/*.cpp"
    "src/editor/*.cpp"
)

add_executable(platformer ${GAME_SRC_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(raylib REQUIRED IMPORTED_TARGET raylib)
target_link_libraries(platformer PRIVATE PkgConfig::raylib)
target_include_directories(platformer PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_custom_target(run
    COMMAND platformer
    DEPENDS platformer
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running project..."
)