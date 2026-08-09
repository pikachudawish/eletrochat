#ifndef STRUCT_PKGLIST_H
#define STRUCT_PKGLIST_H

#include "../../common_hdrs/struct_pkg.h"

typedef struct _packagelist {
    int fd_recipient;
    client sender;
    package pkg;
    struct _packagelist* next;
} packagelist;

#endif