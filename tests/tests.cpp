#include <catch2/catch_test_macros.hpp>

#include "Foo.h"

TEST_CASE("Simple test")
{
    REQUIRE(returnTrue());
    REQUIRE(returnFalse());
}