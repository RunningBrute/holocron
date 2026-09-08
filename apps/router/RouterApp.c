#include <stdio.h>
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
    socketPath.path = argv[2];
    socketPath.length = strlen(argv[2]);

    printf("[Router] socket adress: %s \n", socketPath.path);

    return 0;
}