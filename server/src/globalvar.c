#include <stdio.h>

#include "globalvar.h"

int pipe_db[2] = {0,0};
int pipe_sendpkg[2] = {0,0}; 

int* running = NULL;

packagelist* head_pkg = NULL;
packagelist* tail_pkg = NULL;

dbinfolist* head_db = NULL;
dbinfolist* tail_db = NULL;

pthread_cond_t* cond_db = NULL;
pthread_cond_t* cond_sendpkg = NULL;

pthread_mutex_t* lock_db = NULL;
pthread_mutex_t* lock_sendpkg = NULL;
