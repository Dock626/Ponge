cmake_minimum_required(VERSION 3.15)
project(
        Ponge
        VERSION 0.0.1
        DESCRIPTION "chujh wi "
        HOMEPAGE_URL "none"
        LANGUAGES C CXX
)   

add_executable(example Ponge/Ponge.cpp Ponge/Player.cpp Ponge/Enemy_AI_1.cpp Ponge/Enemy.cpp Ponge/Ball.cpp)

target_compile_features(example PUBLIC cxx_std_23)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)
target_link_libraries(example PRIVATE raylib)