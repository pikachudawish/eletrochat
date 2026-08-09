#define _POSIX_C_SOURCE 199309L     

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include <pthread.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>

#include "globalvar.h"
#include "../../common_hdrs/struct_client.h"
#include "../../common_hdrs/enum_pkgtype.h"
#include "../../common_hdrs/struct_pkg.h"

#include "serverfuncs.h"
#include "cli_llikedlist_funcs.h"

#define EVENTSIZE 64

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
        fprintf(stderr, "\n[SERVER] ERROR:epoll_ctl() 1 failed");
        *running = 0;
        return NULL;
    }

    int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if(timer_fd == -1) {
        close(server_socket);
        fprintf(stderr, "\n[SERVER] ERROR:timerfd_create() failed");
        *running = 0;
        return NULL;
    }

    struct itimerspec new_value = {.it_value.tv_sec = 60, .it_value.tv_nsec = 0, .it_interval.tv_sec = 60, .it_interval.tv_nsec = 0};

    if(timerfd_settime(timer_fd, 0, &new_value, NULL) == -1) {
        close(server_socket);
        close(timer_fd);
        fprintf(stderr, "\n[SERVER] ERROR:timerfd_create() failed");
        *running = 0;
        return NULL;
    }

    struct epoll_event ev_timer = {.events = EPOLLIN, .data.fd = timer_fd};

    if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timer_fd, &ev_timer) == -1) {
        close(server_socket);
        close(timer_fd);
        fprintf(stderr, "\n[SERVER] ERROR:epoll_ctl() 2 failed");
        *running = 0;
        return NULL;
    }

    int evsize = EVENTSIZE;
    struct epoll_event* ev_array = (struct epoll_event*)malloc(EVENTSIZE*sizeof(struct epoll_event));

    client* cli_head = NULL; 

    int n_cli = 0;
    while (*running) {
        int nfds = epoll_wait(epoll_fd, ev_array, evsize, -1);
        if(nfds == -1) continue;

        for(int s = 0; s < nfds; s++) {
            if(ev_array[s].data.fd == server_socket) { //SERVER SOCKET
                int new_cli_fd = accept(server_socket, NULL, NULL);
                if(new_cli_fd == -1) {
                    fprintf(stderr, "\n[SERVER] WARNING:Couldn't accept a client");
                    continue;
                }
                n_cli++;

                char cli_username[16];
                if(recv(new_cli_fd, cli_username, sizeof(cli_username), 0) == -1) {
                    n_cli--;
                    close(new_cli_fd);
                    fprintf(stderr, "\n[SERVER] WARNING:Verifications with new client failed");
                    continue;
                }

                package send_hb  = {.type = HB, .sender_id = server_id, .data.null = NULL};
                if(send(new_cli_fd, &send_hb, sizeof(send_hb), 0) == -1) {
                    n_cli--;
                    close(new_cli_fd);
                    fprintf(stderr, "\n[SERVER] WARNING:Verifications with new client failed");
                    continue;
                }

                if(!insonTail(&cli_head, new_cli_fd, cli_username)) { //failed mem alloc
                    freeCli(cli_head);
                    return NULL;
                }
 
                if(n_cli > evsize) {
                    evsize = evsize + EVENTSIZE;
                    ev_array = (struct epoll_event*)realloc(ev_array, evsize*sizeof(struct epoll_event));
                }

                struct epoll_event new_ev_cli = {.events = EPOLLIN, .data.fd = new_cli_fd};

                if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_cli_fd, &new_ev_cli) == -1) {
                    fprintf(stderr, "\n[SERVER] WARNING:epoll_ctl() failed to add a new cli(fd=%d)", new_cli_fd);
                    close(new_cli_fd);
                    continue;
                }

                fprintf(stdout, "\n[SERVER] LOG:New client connected!(fd=%d)", new_cli_fd);

            } else if(ev_array[s].data.fd == timer_fd) { // TIMER_FD SOCKET
                //FAZER SISTEMA HEARTBEAT


            } else { //CLIENT SOCKETS
                package pkg_recv = {.type = -1, .sender_id = -1,.data.null = NULL};

                ssize_t bytes_recv = recv(ev_array[s].data.fd, &pkg_recv, sizeof(pkg_recv), 0);
                if(bytes_recv <= 0) {
                    if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, ev_array[s].data.fd, NULL) == -1) {
                        fprintf(stderr, "\n[SERVER] WARNING:epoll_ctl() failed to remove a cli(fd=%d)", ev_array[s].data.fd);
                    }
                    close(ev_array[s].data.fd);
                    continue;
                }   

                package pkg_send = {.type = -1, .sender_id = *server_id, .data.null = NULL};
                switch(pkg_recv.type) {
                    case HB:
                        
                        break;

                    case LOGIN:

                        break;

                    case SIGNUP:

                        break;

                    case MSG:
                        pkg_send.type = MSG;
                        strcpy(pkg_send.data.msg.message, pkg_recv.data.msg.message);
                        strcpy(pkg_send.data.msg.sender, pkg_recv.data.msg.sender);

                        

                        break;

                    case END_CONN:
                        close(ev_array[s].data.fd);
                        rmvCli(&cli_head, ev_array[s].data.fd);
                        break;

                    default:

                        break;
                }
            }
        }
    }
    free(ev_array);

    printf("\n[SERVER] LOG:Loop Ended");

    close(server_socket);

    return NULL;
}