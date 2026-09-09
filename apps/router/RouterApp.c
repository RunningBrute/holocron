#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>

#include "SocketPath.h"

int main(int argc, const char* argv[])
{
    printf("[Router] Router started. \n");

    if (argc < 2)
    {
        printf("[Router] Too few arguments to start router! Socket path needed! \n");
        return -1;
    }

    SocketPath socketPath;
    socketPath.path = argv[1];
    socketPath.length = strlen(argv[1]);

    printf("[Router] socket adress: %s \n", socketPath.path);

    int serverFd = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;

    if (socketPath.length >= sizeof(addr.sun_path))
    {
        errno = ENAMETOOLONG;
        return -1;
    }

    memcpy(addr.sun_path, socketPath.path, socketPath.length + 1);

    unlink(socketPath.path);

    bind(serverFd, (struct sockaddr*)&addr, sizeof(addr));
    listen(serverFd, SOMAXCONN);

    for (;;)
    {
        int nodeFd = accept(serverFd, NULL, NULL);

        if (nodeFd < 0)
        {
            perror("[Router] accept");
            return -1;
        }

        char buffer[256];

        ssize_t received = recv(nodeFd, buffer, sizeof(buffer) - 1, 0);

        if (received < 0)
        {
            perror("[Router] recv");
            close(nodeFd);
            return -1;
        }

        if (received == 0)
        {
            printf("[Router] Client disconnected\n");
            close(nodeFd);
        }

        buffer[received] = '\0';

        printf("[Router] Received: %s\n", buffer);
    }

    return 0;
}