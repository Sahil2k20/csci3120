#include <stdio.h>
#include <string.h>

#include "siggen.h"
#include "mempool.h"

#define BITS (sizeof(int) * 8)

int main() {
    trans_encoding *list = new_list();
    char input[4], payer[31], payee[31];
    unsigned int TID, amount, fee;
    unsigned int ID=0, prevID=0, prevSig, T, signature, full_signature=0, nonce;
    int total_bytes;

    while (strcmp(input, "END") != 0) {
        scanf("%s", input);

        if (strcmp(input, "TRX") == 0) {
            scanf("%u %s %s %u %u", &TID, payer, payee, &amount, &fee);
            list_insert(list, TID, payer, payee, amount, fee);
            printf("Adding transaction: %u %s %s %u %u\n", TID, payer, payee, amount, fee);
            //print_list(list);
        }

        if (strcmp(input, "MINE") == 0) {
            int i = 0, t=0;
            unsigned  int msb = 0xff000000;

            nonce = 0;
            signature = siggen_new();              // start a new signature

            ID += 1;
            if (ID != 1) {
                prevID += 1;
            }
            prevSig = signature;
            // id, prevID, prevSig
            total_bytes = 4 + 4 + 4;
            // nonce, signature
            total_bytes = total_bytes + 4 + 4;

            i = transactions_count(list, total_bytes);

            signature = siggen_int(signature, ID);
            signature = siggen_int(signature, prevID);
            signature = siggen_int(signature, prevSig);
            signature = siggen_int(signature, i);

            printf("Block mined: %d %d 0x%.8x %d\n", ID, prevID, prevSig, i);

            walk_list(list, total_bytes, signature);

            // remove transactions in block from the list
            while (t <= i) {
                list_remove(list, TID);
                t += 1;
            }

            full_signature = siggen_int(signature, nonce);
            // while msb of signature is 1
            while (msb & full_signature) {
                nonce += 1;
                full_signature = siggen_int(signature, nonce);
            }

            total_bytes = 0;
            printf("0x%.8x 0x%.8x\n", nonce, full_signature);
        }

        if (strcmp(input, "BLK") == 0) {
            int i = 0;
            scanf("%d %d %i %d", &ID, &prevID, &prevSig, &T);

            while (i < T) {
                scanf("%u %s %s %u %u", &TID, payer, payee, &amount, &fee);
                list_remove(list, TID);
                printf("Removing transaction: %u %s %s %u %u\n", TID, payer, payee, amount, fee);
                i += 1;
            }

            //print_list(list);
            scanf("%i %i", &nonce, &signature);
        }
    }
    return 0;
}

