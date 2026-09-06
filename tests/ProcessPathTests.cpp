#include <catch2/catch_test_macros.hpp>

#include "holocron/common/ProcessPath.h"

TEST_CASE("Executable path is unknown so no sibling path in return")
{
    const char* executable = NULL;
    const char* sibling = "node";
    char buffer[256];
    size_t bufferSize = sizeof(buffer);

    REQUIRE(sibling_path(executable, sibling, buffer, bufferSize) < 0);
}

TEST_CASE("Sibling name is unknown so no sibling path in return")
{
    const char* executable = "dev/null/exec";
    const char* sibling = NULL;
    char buffer[256];
    size_t bufferSize = sizeof(buffer);

    REQUIRE(sibling_path(executable, sibling, buffer, bufferSize) < 0);
}

TEST_CASE("Buffer is not provided so no sibling path in return")
{
    const char* executable = "dev/null/exec";
    const char* sibling = "node";
    char* buffer = NULL;
    size_t bufferSize = 10;

    REQUIRE(sibling_path(executable, sibling, buffer, bufferSize) < 0);
}

TEST_CASE("Buffer is ok, but size is set to zero, so no sibling path in return")
{
    const char* executable = "dev/null/exec";
    const char* sibling = "node";
    char buffer[256];
    size_t bufferSize = 0;

    REQUIRE(sibling_path(executable, sibling, buffer, bufferSize) < 0);
}