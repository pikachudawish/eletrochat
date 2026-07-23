#include <stdio.h>
#include <stdlib.h>

#include <mysql/mysql.h>

int main() {
    int library_init = mysql_library_init(0, NULL, NULL);
    if(library_init) {
        fprintf(stderr, "Couldn't initialize MySQL client library\n");
        exit(EXIT_FAILURE);
    }


    return 0;
}