#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#include "globalvar.h"
#include "enums.h"

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

    lock_db = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    lock_sendpkg = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));

    pthread_mutex_init(&lock_db, NULL);
    pthread_mutex_init(&lock_sendpkg, NULL);

    cond_db = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));
    cond_sendpkg = (pthread_cond_t*)malloc(sizeof(pthread_cond_t));

    pthread_cond_init(cond_db, NULL);
    pthread_cond_init(cond_sendpkg, NULL);

    pthread_create(&threads[0], NULL, server, NULL);
    pthread_create(&threads[1], NULL, db_worker, NULL);
    pthread_create(&threads[2], NULL, sendpkg_worker, NULL);

    //Linha de Comandos
    printf("\n#SERVER COMMAND LINE#");
    while(*running) {
        int cmd = 0;
        char buffer[32];

        printf("\n->> ");
        fgets(buffer, 32, stdin);
        
        if(!strcasecmp(buffer, "quit")) cmd = QUIT;

        switch(cmd){
            case QUIT:
                printf("\n[MAIN]Starting shutdown Procedures...");
                *running = 0;
                break;

            default:
                printf("\n[MAIN]INVALID COMMAND!\n");
                break;
        } 
        
    }
    
    for(int s = 0; s < N_THREADS; s++) pthread_join(threads[s], NULL);
    printf("\n[MAIN]All threads were deleted. Ending Gracefully the Programm.");

    pthread_mutex_destroy(&lock_db);
    pthread_mutex_destroy(&lock_sendpkg);

    free(lock_db);
    free(lock_sendpkg);

    free(running);
    free(threads);

    return 0;
}