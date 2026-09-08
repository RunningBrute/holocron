#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "holocron/node/Node.h"

typedef struct SocketPath
{
    const char* path;
    size_t length;
} SocketPath;

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printf("[Node] Too few arguments to start node! Node ID and socket path needed! \n");
        return -1;
    }

    SocketPath socketPath;
    socketPath.path = argv[2];
    socketPath.length = strlen(argv[2]);

    int id = atoi(argv[1]);
    int pid = getpid();

    Node* node = createNode(id);
    printf("[Node] Node with ID %d and PID %d created \n", id, pid);
    printf("[Node] socket adress: %s \n", socketPath.path);

    while (1)
    {
        printf("[NODE] Alive! Id: %d, PID: %d \n", id, pid);
        sleep(10);
    }

    destroyNode(node);
    printf("[Node] Node with ID %d and PID %d destroyed \n", id, pid);

    return 0;
}