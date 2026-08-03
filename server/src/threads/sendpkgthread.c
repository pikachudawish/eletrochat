#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "globalvar.h"

void* sendpkg_worker(void* arg) {
    
    
    while(*running) {
        pthread_mutex_lock(lock_sendpkg);

        while(!head_pkg) pthread_cond_wait(cond_sendpkg, lock_sendpkg); 

        if(!head_db) {
            pthread_mutex_unlock(lock_sendpkg);
            continue;
        }

        pthread_mutex_unlock(lock_sendpkg);

    }
    printf("\n[SEND_W] LOG:Loop Ended");

    return NULL;
}