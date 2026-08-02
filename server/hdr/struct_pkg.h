#ifndef STRUCT_PKG_H
#define STRCTS_PKG_H

typedef struct _message {
    char text[128];
    int fd;
} message;

typedef struct _package {
    int type;
    message msg;
    struct _package* next_pkg;
} package;

#endif 