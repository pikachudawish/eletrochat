#include <stdio.h>
#include <stdlib.h>

#include <mysql/mysql.h>

#include "globalvar.h"
#include "auxfuncs.h"


void* dbworker(void* arg) {
    MYSQL* conn = mysql_init(NULL);

    if(!connToDB(conn)) {
        mysql_close(conn);
        *server = 0;
        return NULL;
    }

    while(*server) {

    }

    mysql_close(conn);

    return NULL;
}