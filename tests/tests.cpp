#include <catch2/catch_test_macros.hpp>

#include "Node.h"
#include "Message.h"

TEST_CASE("Create node")
{
    int id = 1;
    Node* node = createNode(id);

    Message* message = createMessage(0, 1, "Hello World!", 13);
    destroyMessage(message);

    destroyNode(node);
}