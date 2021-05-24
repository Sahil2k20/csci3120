//
// Created by sahil on 2021-05-07.
//

#include "mempool.h"
#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "siggen.h"

// Reference: Thursday May 6 Lecture
extern trans_encoding * new_list() {
    trans_encoding *list = calloc(1, sizeof(trans_encoding));
    return list;
}

extern void walk_list(trans_encoding *list, unsigned long total_bytes, unsigned int signature) {
    node_t *node = list->head;
    while (total_bytes <= 256 && node != NULL) {
        // Print transaction
        printf("%u %s %s %u %u \n", node->TID, node->payer, node->payee, node->amount, node->fee);

        // Calculate total bytes
        total_bytes = total_bytes + 4 + (strlen(node->payee) + 1) + (strlen(node->payer) + 1) + 4 + 4;

        // Generate signature
        signature = siggen_int(signature, node->TID);
        signature = siggen_string(signature, node->payer);
        signature = siggen_string(signature, node->payee);
        signature = siggen_int(signature, node->amount);
        signature = siggen_int(signature, node->fee);


        // Move to next transaction in list
        node = node->next;
    }
}

extern void remove_transactions(trans_encoding *list, unsigned long total_bytes) {
    node_t *node = list->head;
    while (total_bytes <= 256 && node != NULL) {
        total_bytes = total_bytes + 4 + (strlen(node->payee) + 1) + (strlen(node->payer) + 1) + 4 + 4;

        list_remove(list, node->TID);

        // Move to next transaction in list
        node = node->next;
    }
}

extern int transactions_count(trans_encoding *list, unsigned long total_bytes) {
    node_t *node = list->head;
    int i = 0;
    while (total_bytes <= 256 && node != NULL) {
        // Calculate total bytes
        total_bytes = total_bytes + 4 + (strlen(node->payee) + 1) + (strlen(node->payer) + 1) + 4 + 4;

        // Move to next transaction in list
        node = node->next;

        i +=1;
    }
    return i;
}

extern void list_remove(trans_encoding *list, unsigned int TID) {
    node_t *node = list->head, *prev;
    // Delete head node
    if (node != NULL && node->TID == TID) {
        list->head = node->next; // Changed head
        free(node); // free old head
        return;
    }
    while (node != NULL && node->TID != TID) {
        prev = node;
        node = node->next;
    }

    if (node == NULL) {
        return;
    }

    prev->next = node->next;

    free(node);
}

extern void list_insert(trans_encoding *list, unsigned int TID, char *payer, char *payee, unsigned int amount, unsigned int fee) {
    node_t *node = calloc(1, sizeof(node_t));
    node->TID = TID;
    strcpy(node->payer, payer);
    strcpy(node->payee, payee);
    node->amount = amount;
    node->fee = fee;


    if (list->head == NULL) {
        list->head = node;
        list->tail = node;
    }
    else {
        list->tail->next = node;
        list->tail = node;
    }
}