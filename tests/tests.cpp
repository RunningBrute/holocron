#include <catch2/catch_test_macros.hpp>

#include "Node.h"

TEST_CASE("Create node")
{
    int id = 1;
    Node* node = createNode(id);
    destroyNode(node);
}