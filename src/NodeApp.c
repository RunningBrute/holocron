#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "Node.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("[Node] Too few arguments to start node! Node ID needed! \n");
        return -1;
    }

    int id = atoi(argv[1]);
    int pid = getpid();

    Node* node = createNode(id);
    printf("[Node] Node with ID %d and PID %d created \n", id, pid);

    destroyNode(node);
    printf("[Node] Node with ID %d and PID %d destroyed \n", id, pid);

    return 0;
}