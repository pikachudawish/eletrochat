#include <stdio.h>
#include <stdlib.h>

#include "client/hdr/auxfuncs.h"
#include "client/hdr/globalvar.h"
#include "../../common_hdrs/struct_client.h"

#include "serverfuncs.h"

int main() {
    printf("\n[⚡] Initiating Eletochat App...");

    cli = (client*)malloc(sizeof(client));
    if(!cli) {
        return 1;
    }

    cli->id = genId();

    connServer();   

    free(cli);

    return 0;
}