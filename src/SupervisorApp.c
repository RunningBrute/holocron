#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NODES 10

static inline bool isNewProcess(const int pid)
{
    return pid == 0;
}

int main(int argc, char* argv[])
{
    printf("[Supervisor] Supervisor started. \n");

    if (argc < 2)
    {
        printf("[Supervisor] Too few arguments to start node! Nodes numbers needed! \n");
        return -1;
    }

    int nodesNum = atoi(argv[1]);
    int pid = fork();

    int nodesHandles[MAX_NODES] = {0};

    if (isNewProcess(pid))
    {
        printf("[Supervisor] Place for Node app \n");
        char* const nodeArgv[] = {"node", "2", NULL};
        nodesHandles[0] = execv("node", nodeArgv);

        perror("[ERROR] execv");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("[Supervisor] Old process \n");
    }

    waitpid(nodesHandles[0], NULL, 0);
    printf("[Supervisor] Supervisor ended. \n");

    return 0;
}