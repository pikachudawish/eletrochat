#ifndef CLI_LINKEDLIST_FUNCS_H
#define CLI_LINKEDLIST_FUNCS_H

#include "../../common_hdrs/struct_client.h"

client* newNode(int id, char username[16]);
int rmvCli(client **head, int id);
int insonTail(client **head, int id, char username[16]);
void freeCli(client* head);

#endif