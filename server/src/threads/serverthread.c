#include <stdio.h>

#include <pthread.h>

#include "globalvar.h"

void* server(void* arg) {

    while (*running) {

    }
    printf("\nServer's loop has ended.");

    return NULL;
}