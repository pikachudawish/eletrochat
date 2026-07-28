#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "globalvar.h"
#include "serverfuncs.h"
#include "threadfuncs.h"

#define N_THREADS 3

int main() {
    running = (int*)malloc(sizeof(int));
    if(!running) return 1;

    *running = 1;

    pthread_t* threads = (pthread_t*)malloc(N_THREADS * sizeof(pthread_t));
    if(!threads) {
        free(running);
        return 1;
    }

    pthread_create(&threads[0], NULL, server, NULL);
    pthread_create(&threads[1], NULL, db_worker, NULL);
    pthread_create(&threads[2], NULL, sendpkg_worker, NULL);

    for(int s = 0; s < N_THREADS; s++) pthread_join(threads[s], NULL);

    free(running);
    free(threads);

    return 0;
}