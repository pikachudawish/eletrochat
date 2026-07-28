#include <stdio.h>
#include <stdlib.h>

#include "globalvar.h"

void* recvpkg_worker(void* arg) {

    while(*running) {

    }
    printf("\n[RECV_W]Loop ended");

    return NULL;
}