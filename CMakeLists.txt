cmake_minimum_required(VERSION 3.15)
project(platformer CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
    tiledpp
    GIT_REPOSITORY  https://github.com/pepperjackdev/tiledpp
    GIT_TAG         main     
)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY  https://github.com/raysan5/raylib
    GIT_TAG         c1ab645ca298a2801097931d1079b10ff7eb9df8
)

FetchContent_MakeAvailable(raylib tiledpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

# TODO: Should be avoided
file(GLOB SRC_FILES
    "src/*.cpp"
    "src/**/*.cpp"
)

add_executable(platformer ${SRC_FILES})

target_link_libraries(platformer PRIVATE raylib tiledpp)

add_custom_target(run
    COMMAND platformer
    DEPENDS platformer
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running project..."
)