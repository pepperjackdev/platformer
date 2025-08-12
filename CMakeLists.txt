cmake_minimum_required(VERSION 3.15)
project(platformer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)

# TODO: Should be avoided
file(GLOB SRC_FILES
    "src/*.cpp"
    "src/**/*.cpp"
)

add_executable(platformer ${SRC_FILES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET raylib)
target_link_libraries(platformer PRIVATE PkgConfig::deps)

add_custom_target(run
    COMMAND platformer
    DEPENDS platformer
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running project..."
)