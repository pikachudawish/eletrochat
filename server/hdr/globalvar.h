#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#include <pthread.h>

#include "struct_pkg.h"

extern int* running;

extern package* pkg_list_head;
extern package* pkg_list_tail; 

extern pthread_cond_t* cond_db;
extern pthread_cond_t* cond_sendpkg;

extern pthread_mutex_t* lock_db;
extern pthread_mutex_t* lock_sendpkg;

#endif