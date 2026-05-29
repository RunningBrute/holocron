#include <stdint.h>
#include <stdbool.h>

#ifndef NODE_H
#define NODE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Node Node;

Node* createNode(int id);
void destroyNode(Node* node);

#ifdef __cplusplus
}
#endif

#endif