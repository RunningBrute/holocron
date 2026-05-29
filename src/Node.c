#include "Node.h"

#include <stdlib.h>

typedef struct Node
{
    int id;
} Node;

Node* createNode(int id)
{
    Node* node = malloc(sizeof(*node));
    node->id = id;
}

void destroyNode(Node* node)
{
    free(node);
}