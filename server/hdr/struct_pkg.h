#ifndef STRUCT_PKG_H
#define STRUCT_PKG_H

#include "struct_user.h"
#include "struct_client.h"

typedef struct _message {
    char message[128];
    char sender[16];
} message;

typedef struct _package {
    int type;
    int recipient_fd;
    union {
        void* null;
        userinfo ui;
        message msg;
    } data;
} package;

typedef struct _packagelist {
    int fd_recipient;
    client sender;
    package pkg;
    struct _packagelist* next;
} packagelist;

#endif 