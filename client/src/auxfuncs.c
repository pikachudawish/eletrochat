#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

int genId() {
    char id_char[16];

    int fd = open("/dev/urandom", O_RDONLY);
    if(fd == -1) return 1;

    for(int i = 0; i < 16; i++) {
        unsigned char byte;

        if(read(fd, &byte, 1) != 1) return 1;

        id_char[i] = '0' + (byte % 10);
    }
    close(fd);

    int id = atoi(id_char);

    return;
}