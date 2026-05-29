cmake_minimum_required(VERSION 3.23)

project(traveler LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_library(holocron_lib)
target_sources(holocron_lib PRIVATE src/Foo.c)
target_include_directories(holocron_lib PUBLIC include)

add_executable(holocron)
target_sources(holocron PRIVATE src/main.c)
target_link_libraries(holocron PRIVATE holocron_lib)
target_compile_options(holocron PRIVATE -fsanitize=address -g)
target_link_options(holocron PRIVATE -fsanitize=address)

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