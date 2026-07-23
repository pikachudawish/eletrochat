#include <stdio.h>
#include <stdlib.h>

#include <mysql/mysql.h>

int fetchEnvInfo(MYSQL* conn) {
    char* db = getenv("DB_NAME");
    printf("\n%s", db);
    char* username = getenv("DB_USERNAME");
    printf("\n%s", username);
    char* pass = getenv("DB_PASS");
    printf("\n%s", pass);
    char* ip = getenv("DB_IP");
    printf("\n%s", ip);
    int port = atoi(getenv("DB_PORT"));
    printf("\n%d", port);

    if(!mysql_real_connect(conn, ip, username, pass, db, port, NULL, 0)) {
        fprintf(stderr, "\n[ERROR] Couldn establish a connection with the Database");
        return 0;
    }

    return 1; 
}