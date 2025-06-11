/*
TITLE: PROGRAMMING II LABS                   SUBTITLE: P2

AUTHOR 1: Ali Abu-afash Nayef  LOGIN 1: ali.nayef@udc.es

AUTHOR 2: Pedro Rodríguez Raposo  LOGIN 2: pedro.rodriguez.raposo@udc.es

GROUP: 1.2                                                        DATE: 03/04/2025
*/

#include <stdlib.h>
#include <stddef.h>
#include "bid_stack.h"

#define LNULL -1
#define MAX_LIST 25

typedef int tPosL;

typedef struct tItemL {
    tUserId seller;
    tConsoleId consoleId;
    tConsoleBrand consoleBrand;
    tConsolePrice consolePrice;
    tBidCounter bidCounter;
    tStack bidStack;
} tItemL;

typedef struct {
    tItemL data[MAX_LIST];
    tPosL lastPos;
} tList;

//operaciones del TAD ConsoleList
void createEmptyList(tList* l);
bool isEmptyList(tList l);
tPosL first(tList l);
tPosL last(tList l);
tPosL next(tPosL p, tList l);
tPosL previous(tPosL p, tList l);
bool insertItem(tItemL d, tList* l);
void deleteAtPosition(tPosL p, tList* l);
tItemL getItem(tPosL p, tList l);
void updateItem(tItemL d, tPosL p, tList* l);
tPosL findItem(tConsoleId id, tList l);

#endif // CONSOLE_LIST_H