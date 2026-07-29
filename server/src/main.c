#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#include "globalvar.h"
#include "cmdenum.h"

#include "serverfuncs.h"
#include "threadfuncs.h"

#define N_THREADS 4

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
    pthread_create(&threads[3], NULL, recvpkg_worker, NULL);

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

    free(running);
    free(threads);

    return 0;
}