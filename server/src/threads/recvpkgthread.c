#include <stdio.h>
#include <stdlib.h>

#include "globalvar.h"

void* recvpkg_worker(void* arg) {

    while(*running) {

    }
    printf("\nRecvpkg_worker's loop has ended.");

    return NULL;
}