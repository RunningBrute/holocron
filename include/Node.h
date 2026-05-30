#ifndef NODE_H
#define NODE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct Node Node;

Node* createNode(int id);
void destroyNode(Node* node);

#ifdef __cplusplus
}
#endif

#endif