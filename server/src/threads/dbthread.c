#include <stdio.h>
#include <stdlib.h>

#include <mysql/mysql.h>

#include "globalvar.h"
#include "dbfuncs.h"

void* db_worker(void* arg) {
    MYSQL* conn = mysql_init(NULL);

    if(!connToDB(conn)) {
        mysql_close(conn);
        fprintf(stderr, "\n[DB_W] ERROR:Could't connect to the database");
        *running = 0;
        return NULL;
    }

    while(*running) {
    
    }
    printf("\n[DB_W] LOG:Loop ended");
    

    mysql_close(conn);

    return NULL;
}

