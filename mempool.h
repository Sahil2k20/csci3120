//
// Created by sahil on 2021-05-07.
//

#ifndef MINER_MEMPOOL_H
#define MINER_MEMPOOL_H

// Reference: Thursday May 6 Lecture
typedef struct node {
    struct node *next;
    unsigned int TID, amount, fee;
    char payer[31], payee[31];
}node_t;

typedef struct transaction_encoding {
    node_t *head;
    node_t *tail;
}trans_encoding;

extern trans_encoding * new_list();
extern void list_insert(trans_encoding *list, unsigned int TID, char *payer, char *payee, unsigned int amount, unsigned int fee);
extern void list_remove(trans_encoding *list, unsigned int TID);
extern void walk_list(trans_encoding *list, unsigned long total_bytes, unsigned int signature);
extern int transactions_count(trans_encoding *list, unsigned long total_bytes);
#endif //MINER_MEMPOOL_H
