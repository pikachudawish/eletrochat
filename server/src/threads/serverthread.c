#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

#include "globalvar.h"

#include "serverfuncs.h"

void* server(void* arg) {
    int server_socket = server_init();


    while (*running) {

    }

    printf("\n[SERVER]Loop Ended");

    close(server_socket);

    return NULL;
}