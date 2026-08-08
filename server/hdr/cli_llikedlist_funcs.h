#ifndef CLI_LINKEDLIST_FUNCS_H
#define CLI_LINKEDLIST_FUNCS_H

#include "struct_client.h"

client* newNode(int fd, char username[16]);
int rmvCli(client **head, int fd);
int insonTail(client **head, int fd, char username[16]);
void freeCli(client* head);

#endif