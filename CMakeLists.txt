cmake_minimum_required(VERSION 3.23)

project(traveler LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_library(holocron_lib)
target_sources(holocron_lib PRIVATE src/Message.c src/Node.c)
target_include_directories(holocron_lib PUBLIC include)

# Node application
add_executable(node)
target_sources(node PRIVATE src/NodeApp.c)
target_link_libraries(node PRIVATE holocron_lib)
target_compile_options(node PRIVATE -fsanitize=address -g)
target_link_options(node PRIVATE -fsanitize=address)

# Supervisor application
add_executable(supervisor)
target_sources(supervisor PRIVATE src/SupervisorApp.c)
target_compile_options(supervisor PRIVATE -fsanitize=address -g)
target_link_options(supervisor PRIVATE -fsanitize=address)

# Router application
add_executable(router)
target_sources(router PRIVATE src/RouterApp.c)
target_compile_options(router PRIVATE -fsanitize=address -g)
target_link_options(router PRIVATE -fsanitize=address)

# Tests
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.8.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(tests)
target_sources(tests PRIVATE tests/tests.cpp)
target_link_libraries(tests PRIVATE holocron_lib Catch2::Catch2WithMain)
target_compile_options(tests PRIVATE -fsanitize=address -g)
target_link_options(tests PRIVATE -fsanitize=address)

include(CTest)
include(Catch)

catch_discover_tests(tests)