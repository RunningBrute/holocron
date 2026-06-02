#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_NODES 10

typedef struct NodesContext
{
    pid_t pids[MAX_NODES];
    int ids[MAX_NODES];
    int size;
} NodesContext;

static inline bool isNewProcess(const pid_t pid)
{
    return pid == 0;
}

static inline void waitForNodes(const NodesContext ctx)
{
    for (int id = 0; id < ctx.size; ++id)
    {
        waitpid(ctx.pids[id], NULL, 0);
    }
}

static inline void createNode(NodesContext* ctx, const int id)
{
    ctx->ids[id] = id;
    ctx->pids[id] = fork();
    if (isNewProcess(ctx->pids[id]))
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

static inline void createNodes(NodesContext* ctx)
{
    for (int id = 0; id < ctx->size; ++id)
    {
        createNode(ctx, id);
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

    NodesContext nodesCtx;
    nodesCtx.size = nodesCount;

    createNodes(&nodesCtx);
    waitForNodes(nodesCtx);

    printf("[Supervisor] Supervisor ended. \n");

    return 0;
}