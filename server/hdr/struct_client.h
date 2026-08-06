#ifndef STRUCT_CLIENT_H
#define STRUCT_CLIENT_H

typedef struct _client {
    int fd;
    char username[16];
    struct _client* next;
} client;


#endif