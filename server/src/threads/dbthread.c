#include <stdio.h>
#include <stdlib.h>

#include <mysql/mysql.h>

#include "globalvar.h"
#include "auxfuncs.h"

void* db_worker(void* arg) {
    MYSQL* conn = mysql_init(NULL);

    if(!connToDB(conn)) {
        mysql_close(conn);
        *running = 0;
        return NULL;
    }

    while(*running) {
    
    }

    mysql_close(conn);

    return NULL;
}

