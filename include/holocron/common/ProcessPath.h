#ifndef PROCESS_PATH_H
#define PROCESS_PATH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

inline static int sibling_path(const char* executable, char* buffer, size_t buffer_size)
{
    if (executable == NULL)
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
    
    int slash = '/';
    char* lastSlash = strrchr(buffer, slash);

    if (lastSlash == NULL)
    {
        perror("[ProcessPath] strrchr() error");
    }

    size_t pathLength = (size_t)(lastSlash - buffer);
    buffer[pathLength] = '\0';

    return 0;
}

#ifdef __cplusplus
}
#endif

#endif