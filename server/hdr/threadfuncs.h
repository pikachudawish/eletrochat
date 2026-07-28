#ifndef THREADFUNCS_H
#define THREADFUNCS_H

void* server(void* arg);
void* db_worker(void* arg);
void* recvpkg_worker(void* arg);
void* sendpkg_worker(void* arg);

#endif