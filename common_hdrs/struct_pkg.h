#ifndef STRUCT_PKG_H
#define STRUCT_PKG_H

#include "struct_user.h"
#include "struct_client.h"


typedef struct _message {
    char message[128];
    char sender[16];
} message;

typedef struct _package {
    int sender_id;
    int type;
    union {
        void* null;
        userinfo ui;
        message msg;
    } data;
} package;



#endif 