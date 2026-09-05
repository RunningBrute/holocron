#ifndef PROCESS_PATH_H
#define PROCESS_PATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

inline static int sibling_path(
    const char* executable,
    const char* sibling,
    char* buffer,
    size_t buffer_size)
{
    if (executable == NULL || sibling == NULL || buffer == NULL || buffer_size == 0)
    {
        perror("[ProcessPath] Wrong executable path");
        return -1;
    }

    ssize_t length = readlink(executable, buffer, buffer_size - 1);
    if (length < 0)
    {
        perror("[ProcessPath] readlink() error");
        return -1;
    }
    buffer[length] = '\0';
    
    char* lastSlash = strrchr(buffer, '/');
    if (lastSlash == NULL)
    {
        perror("[ProcessPath] strrchr() error");
        return -1;
    }

    size_t pathLength = (size_t)(lastSlash - buffer);
    buffer[pathLength] = '\0';

    int written = snprintf(buffer + pathLength, buffer_size - pathLength, "/%s", sibling);
    if (written < 0 || (size_t)written >= buffer_size - pathLength)
    {
        perror("[ProcessPath] snprintf() error");
        return -1;
    }

    return 0;
}

#ifdef __cplusplus
}
#endif

#endif