#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#include "globalvar.h"
#include "enums.h"
#include "struct_pkg.h"

#include "serverfuncs.h"

#define EVENTSIZE 50

void* server(void* arg) {
    int server_socket = server_init();
    if(!server_socket) {
        fprintf(stderr, "\n[SERVER] ERROR:Couldn't create the server's socket");
        *running = 0;
        return NULL;
    }

    int epoll_fd = epoll_create1(0);
    if(epoll_fd == -1) {
        close(server_socket);
        fprintf(stderr, "\n[SERVER] ERROR:epoll_create1() failed");
        *running = 0;
        return NULL;
    }

    struct epoll_event ev_server = {.events = EPOLLIN, .data.fd = server_socket};

    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &ev_server) == -1) {
        close(server_socket);
        fprintf(stderr, "\n[SERVER] ERROR:epoll_ctl() failed");
        *running = 0;
        return NULL;
    }


    int evsize = EVENTSIZE;
    struct epoll_event* ev_array = (struct epoll_event*)malloc(EVENTSIZE*sizeof(struct epoll_event));

    int n_cli = 0;
    while (*running) {
        int nfds = epoll_wait(epoll_fd, ev_array, evsize, -1);
        if(nfds == -1) continue;

        for(int s = 0; s < nfds; s++) {
            if(ev_array[s].data.fd == server_socket) { 
                int cli_fd = accept(server_socket, NULL, NULL);
                if(cli_fd == -1) {
                    fprintf(stderr, "\n[SERVER] WARNING:Couldn't accept a client");
                    continue;
                }
                n_cli++;

                if(n_cli > evsize) {
                    evsize = evsize + EVENTSIZE;
                    ev_array = (struct epoll_event*)realloc(ev_array, evsize*sizeof(struct epoll_event));
                }

                struct epoll_event new_ev_cli = {.events = EPOLLIN, .data.fd = cli_fd};

                if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cli_fd, &new_ev_cli) == -1) {
                    fprintf(stderr, "\n[SERVER] WARNING:epoll_ctl() failed to add a new cli(fd=%d)", cli_fd);
                    close(cli_fd);
                    continue;
                }

                fprintf(stdout, "\n[SERVER] LOG:New client connected!(fd=%d)", cli_fd);
            } else {
                package* pkg = (package*)malloc(sizeof(package));

                ssize_t bytes_recv = recv(ev_array[s].data.fd, pkg, sizeof(*pkg), 0);
                if(bytes_recv <= 0) {
                    if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ev_array[s].data.fd, NULL) == -1) {
                        fprintf(stderr, "\n[SERVER] WARNING:epoll_ctl() failed to remove a cli(fd=%d)", ev_array[s].data.fd);
                    }
                    close(ev_array[s].data.fd);
                    free(pkg);
                    continue;
                }   

                switch(pkg->type) {
                    case HB:

                        break;

                    case LOGIN:

                        break;

                    case SIGNUP:

                        break;

                    case MSG:

                        break;

                    default:

                        break;
                }
                free(pkg);

            }
        }
    }
    free(ev_array);

    printf("\n[SERVER]Loop Ended");

    close(server_socket);

    return NULL;
}