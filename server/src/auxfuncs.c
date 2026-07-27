#include <stdio.h>
#include <stdlib.h>

#include <mysql/mysql.h>

int connToDB(MYSQL* conn) {
    char* ip = getenv("DB_IP");
    char* db = getenv("DB_NAME");
    char* username = getenv("DB_USER");
    char* pass = getenv("DB_PASS");

    if(!mysql_real_connect(conn, ip, username, pass, db, 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    return 1; 
}