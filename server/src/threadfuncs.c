#include <stdio.h>
#include <stdlib.h>

#include <mysql/mysql.h>

void* dbworker(void* arg) {
    MYSQL* conn = mysql_init(NULL);

    


    mysql_close(conn);
}