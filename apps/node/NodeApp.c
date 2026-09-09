#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include "holocron/node/Node.h"
#include "SocketPath.h"

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

    int serverFd = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr = {0};

    addr.sun_family = AF_UNIX;
    if (socketPath.length >= sizeof(addr.sun_path))
    {
        errno = ENAMETOOLONG;
        return -1;
    }

    memcpy(addr.sun_path, socketPath.path, socketPath.length + 1);

    if (connect(serverFd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("[Node] connect");
        return -1;
    }

    printf("[Node] Id: %d, PID: %d conected to the server! \n", id, pid);
    
    char message[64];

    int length = snprintf(message, sizeof(message), "Hello from node [ID: %d, PID: %d]", id, pid);

    if (length < 0 || (size_t) length >= sizeof(message))
    {
        fprintf(stderr, "[Node] Failed to create hello message\n");
        return EXIT_FAILURE;
    }

    if (send(serverFd, message, (size_t)length, 0) < 0)
    {
        perror("[Node] send");
        return EXIT_FAILURE;
    }

    while (1)
    {
        printf("[Node] Alive! Id: %d, PID: %d \n", id, pid);
        sleep(10);
    }

    destroyNode(node);
    printf("[Node] Node with ID %d and PID %d destroyed \n", id, pid);

    return 0;
}