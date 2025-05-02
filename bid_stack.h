/*
TITLE: PROGRAMMING II LABS                   SUBTITLE: P2

AUTHOR 1: Ali Abu-afash Nayef  LOGIN 1: ali.nayef@udc.es

AUTHOR 2: Pedro Rodríguez Raposo  LOGIN 2: pedro.rodriguez.raposo@udc.es

GROUP: 1.2                                                        DATE: 03/04/2025
*/

#ifndef BID_STACK_H
#define BID_STACK_H

#include "types.h"
#include <stdbool.h>

#define SNULL -1
#define MAX_STACK 25

//definición de un elemento de la pila (una puja)
typedef struct {
    tUserId bidder;
    tConsolePrice consolePrice;
} tItemS;

//definición de posición en la pila
typedef int tPosS;

//definición de la pila estática
typedef struct {
    tItemS data[MAX_STACK];  // Array de elementos
    tPosS top;               // Índice del elemento superior
} tStack;

//operaciones del TAD BidStack
void createEmptyStack(tStack* stack);
bool push(tItemS item, tStack* stack);
void pop(tStack* stack);
tItemS peek(tStack stack);
bool isEmptyStack(tStack stack);

#endif // BID_STACK_H
