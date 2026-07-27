#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "globalvar.h"

#define N_THREADS 1

int main() {
    server = (int*)malloc(sizeof(int));
    if(!server) return 1;

    *server = 1;

    pthread_t* threads = (pthread_t*)malloc(N_THREADS * sizeof(pthread_t));
    if(!threads) {
        free(server);
        return 1;
    }


    free(server);
    free(threads);

    return 0;
}