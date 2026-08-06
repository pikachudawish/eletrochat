#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct_client.h"

client* newNode(int fd, char username[16]) {
    client* new = (client*)malloc(sizeof(client));
    if(!new) {
        fprintf(stderr, "[SERVER] ERROR:Failed malloc newNode");
        return NULL;
    }
    new->fd = fd;
    strcpy(new->username, username);
    new->next = NULL;

    return new;
}

int insonTail(client **head, int fd, char username[16]) {
    client* new = newNode(fd, username);
    if(!new) {
        return 0;
    }

    if(!*head) {
        *head = new;
        return 1;
    }

    client* now = *head;
    while(now->next != NULL) {
        now = now->next;
    }
    now->next = new;

    return 1;
}

int rmvCli(client** head, int fd) {
    client* now = *head;
    client* before = NULL;

    while(now != NULL && now->fd != fd) {
        before = now;
        now = now->next;
    }

    if(!now) {
        fprintf(stderr, "[SERVER] WARNING:Couldn't remove the cli(fd=%d) that disconnected\n", fd);
        return 0;
    }

    if (!before) {
        *head = now->next;
    } else {
        before->next = now->next;
    }

    free(now);
    
    return 1;
}

void freeCli(client* head) {
    client* now = head;

    while(now->next != NULL) {
        client* freeNode = now;
        now = now->next;
        free(freeNode);
    }

    return;
}