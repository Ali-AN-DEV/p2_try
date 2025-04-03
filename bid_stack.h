#ifndef BID_STACK_H
#define BID_STACK_H

#include "types.h"
#include <stdbool.h>
#include <stdlib.h>

#define SNULL NULL
#define MAX_STACK 25

// Definición de un elemento de la pila (una puja)
typedef struct {
    tUserId bidder;
    tConsolePrice consolePrice;
} tItemS;

// Definición del nodo de la pila
typedef struct tNodeS* tPosS;
typedef struct tNodeS {
    tItemS data;
    tPosS next;
} tNodeS;

typedef tPosS tStack;

// Prototipos de las operaciones del TAD BidStack
void createEmptyStack(tStack* stack);
bool push(tItemS item, tStack* stack);
void pop(tStack* stack);
tItemS peek(tStack stack);
bool isEmptyStack(tStack stack);

#endif // BID_STACK_H
