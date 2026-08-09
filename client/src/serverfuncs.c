#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "globalvar.h"
#include "../../common_hdrs/struct_pkg.h"
#include "../../common_hdrs/enum_pkgtype.h"

#include "auxfuncs.h"

#define PORT 6767

#define IP_LOOPBACK "127.0.0.1"

int connServer() {
    int cli_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(cli_socket == -1) {
        fprintf(stderr, "\n[❌] ERROR: Failed to create a socket. Aborting programm");
        return 0;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = IP_LOOPBACK;

    if(connect(cli_socket, (struct sockaddr*)&server_address, sizeof(server_address))) {
        close(cli_socket);
        fprintf(stderr, "\n[❌] ERROR: Failed to connect to the server. Please verify your internet connection. Aborting programm");
        return 0;
    }

    if(send(cli_socket, &cli->id, sizeof(cli->id), 0) == -1) {
        close(cli_socket);
        fprintf(stderr, "\n[❌] ERROR: Failed to send the confirmation message to server. Aborting programm");
        return 0;
    }

    package recv_hb = {.sender_id = 0, .type = -1, .data.null = NULL};
    if(recv(cli_socket, &recv_hb, sizeof(recv_hb), 0) == -1) {
        close(cli_socket);
        fprintf(stderr, "\n[❌] ERROR: Failed to receive the confirmation message to server. Aborting programm");
        return 0;
    }

    if(recv_hb.type != HB) {
        close(cli_socket);
        fprintf(stderr, "\n[❌] ERROR: Confirmation from server arrived corrupted . Aborting programm");
        return 0;
    }

    fprintf(stderr, "\n[✅] SUCESS: Connection to server confirmated");

    return 1;
}