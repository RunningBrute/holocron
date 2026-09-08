#ifndef SOCKET_PATH_H
#define SOCKET_PATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

typedef struct SocketPath
{
    const char* path;
    size_t length;
} SocketPath;

#ifdef __cplusplus
}
#endif

#endif