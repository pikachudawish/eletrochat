#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 6767

int server_init() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) {
        return 0;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if(bind(server_socket, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        close(server_socket);
        return 0;
    }

    if(listen(server_socket, 1024) == -1) {
        close(server_socket);
        return 0;
    }

    return server_socket;
}

