#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NODES 10

static inline bool isNewProcess(const pid_t pid)
{
    return pid == 0;
}

static inline void waitForNodes(const pid_t* nodesPids, const int nodesCount)
{
    for (int id = 1; id <= nodesCount; ++id)
    {
        waitpid(nodesPids[id - 1], NULL, 0);
    }
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

    pid_t nodesPids[MAX_NODES] = {0};

    for (int id = 1; id <= nodesCount; ++id)
    {
        pid_t pid = fork();
        nodesPids[id - 1] = pid;
        if (isNewProcess(pid))
        {
            printf("[Supervisor] Trying to create new node with ID %d \n", id);

            char textId[20];
            snprintf(textId, sizeof(textId), "%d", id);

            char* const nodeArgv[] = {"node", textId, NULL};
            execv("node", nodeArgv);

            perror("[Supervisor][ERROR] execv");
            _exit(EXIT_FAILURE);
        }
    }

    waitForNodes(nodesPids, nodesCount);

    printf("[Supervisor] Supervisor ended. \n");

    return 0;
}