#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "globalvar.h"

void* sendpkg_worker(void* arg) {
    
    
    while(*running) {
        pthread_mutex_lock(lock_sendpkg);

        while(!pkg_list_head) pthread_cond_wait(cond_sendpkg, lock_sendpkg); 


    }
    printf("\n[SEND_W] LOG:Loop Ended");

    return NULL;
}