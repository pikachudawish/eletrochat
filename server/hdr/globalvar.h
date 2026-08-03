#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <pthread.h>

#include "struct_pkg.h"
#include "struct_db.h"

extern int* running;

extern packagelist* head_pkg;
extern packagelist* tail_pkg; 

extern dbinfolist* head_db;
extern dbinfolist* tail_db;

extern pthread_cond_t* cond_db;
extern pthread_cond_t* cond_sendpkg;

extern pthread_mutex_t* lock_db;
extern pthread_mutex_t* lock_sendpkg;

#endif