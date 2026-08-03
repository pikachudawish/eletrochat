#ifndef STRUCT_PKG_H
#define STRUCT_PKG_H

#include "struct_user.h"

typedef struct _message {
    char message[128];
    char from_user[16];
} message;

typedef struct _package {
    int type;
    union data {
        userinfo ui;
        message msg;
    };
} package;

typedef struct _packagelist {
    int fd_dest;
    int fd_sender;
    package pkg;
    struct _packagelist* next;
} packagelist;

#endif 