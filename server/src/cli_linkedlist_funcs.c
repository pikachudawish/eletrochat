#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../common_hdrs/struct_client.h"

client* newNode(int id, char username[16]) {
    client* new = (client*)malloc(sizeof(client));
    if(!new) {
        fprintf(stderr, "[SERVER] ERROR:Failed malloc newNode");
        return NULL;
    }
    new->id = id;
    strcpy(new->username, username);
    new->next = NULL;

    return new;
}

int insonTail(client **head, int id, char username[16]) {
    client* new = newNode(id, username);
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

int rmvCli(client** head, int id) {
    client* now = *head;
    client* before = NULL;

    while(now != NULL && now->id != id) {
        before = now;
        now = now->next;
    }

    if(!now) {
        fprintf(stderr, "[SERVER] WARNING:Couldn't remove the cli(id=%d) that disconnected\n", id);
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