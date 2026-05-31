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
        perror("[Supervisor][ERROR] Too few arguments to start node! Nodes numbers needed! \n");
        exit(EXIT_FAILURE);
    }

    int nodesCount = atoi(argv[1]);
    if (nodesCount > MAX_NODES)
    {
        nodesCount = MAX_NODES;
        printf("[Supervisor][WARNING] Too many nodes. Only %d nodes will be created\n", MAX_NODES);
    }
    printf("[Supervisor] %d nodes will be created\n", nodesCount);

    int nodesHandles[MAX_NODES] = {0};

    for (int id = 1; id <= nodesCount; ++id)
    {
        int pid = fork();
        if (isNewProcess(pid))
        {
            printf("[Supervisor] Trying to create new node with ID %d \n", id);

            char textId[20];
            snprintf(textId, sizeof(textId), "%d", id);

            char* const nodeArgv[] = {"node", textId, NULL};
            nodesHandles[id - 1] = execv("node", nodeArgv);

            perror("[Supervisor][ERROR] execv");
            exit(EXIT_FAILURE);
        }
    }

    for (int id = 1; id <= nodesCount; ++id)
    {
        waitpid(nodesHandles[id], NULL, 0);
    }
    printf("[Supervisor] Supervisor ended. \n");

    return 0;
}