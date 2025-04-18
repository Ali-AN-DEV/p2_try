/*
TITLE: PROGRAMMING II LABS                   SUBTITLE: P2

AUTHOR 1: Ali Abu-afash Nayef  LOGIN 1: ali.nayef@udc.es

AUTHOR 2: Pedro Rodríguez Raposo  LOGIN 2: pedro.rodriguez.raposo@udc.es

GROUP: 1.2                                                        DATE: 03/04/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "types.h"
#include "console_list.h"
#include "bid_stack.h"

#define MAX_BUFFER 255

// Lista estática para almacenar todas las consolas
static tList consoleList;
static int initialized = 0;

/*
 * Objetivo: Procesar el comando [N]ew para añadir una nueva consola
 * Entradas:
 *   - commandNumber: número de comando
 *   - consoleId: identificador de la consola
 *   - userId: identificador del vendedor
 *   - brand: marca de la consola
 *   - price: precio de la consola
 * Salidas: Imprime el resultado del comando
 */
void processNewCommand(char *commandNumber, char *consoleId, char *userId, char *brand, char *price) {
    tItemL newConsole;
    tStack emptyStack;

    printf("%s N: console %s seller %s brand %s price %s\n",
           commandNumber, consoleId, userId, brand, price);

    // Comprobar si la consola ya existe
    if (findItem(consoleId, consoleList) != LNULL) {
        printf("+ Error: New not possible\n");
        return;
    }

    // Inicializar datos de la consola
    strcpy(newConsole.consoleId, consoleId);
    strcpy(newConsole.seller, userId);
    newConsole.consoleBrand = (strcmp(brand, "nintendo") == 0) ? nintendo : sega;
    newConsole.consolePrice = atof(price);
    newConsole.bidCounter = 0;

    // Crear una pila vacía para las pujas
    createEmptyStack(&emptyStack);
    newConsole.bidStack = emptyStack;

    // Insertar la consola en la lista
    if (insertItem(newConsole, &consoleList)) {
        printf("* New: console %s seller %s brand %s price %.2f\n",
               newConsole.consoleId, newConsole.seller,
               (newConsole.consoleBrand == nintendo) ? "nintendo" : "sega",
               newConsole.consolePrice);
    } else {
        printf("+ Error: New not possible\n");
    }
}

/*
 * Objetivo: Procesar el comando [D]elete para eliminar una consola
 * Entradas:
 *   - commandNumber: número de comando
 *   - consoleId: identificador de la consola a eliminar
 * Salidas: Imprime el resultado del comando
 */
void processDeleteCommand(char *commandNumber, char *consoleId) {
    tPosL pos;
    tItemL console;

    printf("%s D: console %s\n", commandNumber, consoleId);

    // Buscar la consola
    pos = findItem(consoleId, consoleList);
    if (pos == LNULL) {
        printf("+ Error: Delete not possible\n");
        return;
    }

    // Obtener datos de la consola
    console = getItem(pos, consoleList);

    // Verificar si la pila de pujas está vacía
    if (!isEmptyStack(console.bidStack)) {
        printf("+ Error: Delete not possible\n");
        return;
    }

    // Imprimir información antes de eliminar
    printf("* Delete: console %s seller %s brand %s price %.2f bids %d\n",
           console.consoleId, console.seller,
           (console.consoleBrand == nintendo) ? "nintendo" : "sega",
           console.consolePrice, console.bidCounter);

    // Eliminar la consola
    deleteAtPosition(pos, &consoleList);
}

/*
 * Objetivo: Procesar el comando [B]id para realizar una puja por una consola
 * Entradas:
 *   - commandNumber: número de comando
 *   - consoleId: identificador de la consola
 *   - userId: identificador del pujador
 *   - price: precio de la puja
 * Salidas: Imprime el resultado del comando
 */
void processBidCommand(char *commandNumber, char *consoleId, char *userId, char *price) {
    tPosL pos;
    tItemL console;
    tItemS newBid;
    float bidPrice;
    float currentPrice;

    printf("%s B: console %s bidder %s price %s\n",
           commandNumber, consoleId, userId, price);

    // Buscar la consola
    pos = findItem(consoleId, consoleList);
    if (pos == LNULL) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    // Obtener datos de la consola
    console = getItem(pos, consoleList);

    // Verificar que el pujador no sea el vendedor
    if (strcmp(console.seller, userId) == 0) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    bidPrice = atof(price);

    // Verificar si la pila está vacía o no
    if (isEmptyStack(console.bidStack)) {
        currentPrice = console.consolePrice;
    } else {
        currentPrice = peek(console.bidStack).consolePrice;
    }

    // Verificar que la puja sea mayor que la actual
    if (bidPrice <= currentPrice) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    // Crear nueva puja
    strcpy(newBid.bidder, userId);
    newBid.consolePrice = bidPrice;

    // Añadir la puja a la pila
    if (!push(newBid, &console.bidStack)) {
        printf("+ Error: Bid not possible\n");
        return;
    }

    // Incrementar contador de pujas
    console.bidCounter++;

    // Actualizar la consola en la lista
    updateItem(console, pos, &consoleList);

    // Imprimir resultado
    printf("* Bid: console %s bidder %s brand %s price %.2f bids %d\n",
           console.consoleId, userId,
           (console.consoleBrand == nintendo) ? "nintendo" : "sega",
           bidPrice, console.bidCounter);
}

/*
 * Objetivo: Procesar el comando [A]ward para asignar el ganador de una subasta
 * Entradas:
 *   - commandNumber: número de comando
 *   - consoleId: identificador de la consola
 * Salidas: Imprime el resultado del comando
 */
void processAwardCommand(char *commandNumber, char *consoleId) {
    tPosL pos;
    tItemL console;
    tItemS winningBid;

    printf("%s A: console %s\n", commandNumber, consoleId);

    // Buscar la consola
    pos = findItem(consoleId, consoleList);
    if (pos == LNULL) {
        printf("+ Error: Award not possible\n");
        return;
    }

    // Obtener datos de la consola
    console = getItem(pos, consoleList);

    // Verificar si hay pujas
    if (isEmptyStack(console.bidStack)) {
        printf("+ Error: Award not possible\n");
        return;
    }

    // Obtener la puja ganadora (la más alta)
    winningBid = peek(console.bidStack);

    // Imprimir resultado
    printf("* Award: console %s bidder %s brand %s price %.2f\n",
           console.consoleId, winningBid.bidder,
           (console.consoleBrand == nintendo) ? "nintendo" : "sega",
           winningBid.consolePrice);

    // Vaciar la pila de pujas (aunque no es necesario porque vamos a eliminar la consola)
    while (!isEmptyStack(console.bidStack)) {
        pop(&console.bidStack);
    }

    // Eliminar la consola de la lista
    deleteAtPosition(pos, &consoleList);
}

/*
 * Objetivo: Procesar el comando [I]nvalidateBids para invalidar pujas de consolas con exceso de pujas
 * Entradas:
 *   - commandNumber: número de comando
 * Salidas: Imprime el resultado del comando
 */
void processInvalidateBidsCommand(char *commandNumber) {
    tPosL pos;
    float averageBids = 0.0;
    int totalBids = 0, totalConsoles = 0;
    bool anyInvalidated = false;

    printf("%s I\n", commandNumber);

    // Si la lista está vacía
    if (isEmptyList(consoleList)) {
        printf("+ Error: InvalidateBids not possible\n");
        return;
    }

    // Calcular la media de pujas
    for (pos = first(consoleList); pos != LNULL; pos = next(pos, consoleList)) {
        tItemL console = getItem(pos, consoleList);
        totalBids += console.bidCounter;
        totalConsoles++;
    }

    if (totalConsoles == 0) {
        printf("+ Error: InvalidateBids not possible\n");
        return;
    }

    averageBids = (float)totalBids / totalConsoles;

    // Invalidar pujas que superan el doble de la media
    for (pos = first(consoleList); pos != LNULL; pos = next(pos, consoleList)) {
        tItemL console = getItem(pos, consoleList);

        if (console.bidCounter > 2 * averageBids) {
            // Mostrar información antes de invalidar
            printf("* InvalidateBids: console %s seller %s brand %s price %.2f bids %d average bids %.2f\n",
                   console.consoleId, console.seller,
                   (console.consoleBrand == nintendo) ? "nintendo" : "sega",
                   console.consolePrice, console.bidCounter, averageBids);

            // Vaciar la pila de pujas
            while (!isEmptyStack(console.bidStack)) {
                pop(&console.bidStack);
            }

            // Actualizar contador de pujas y guardar en la lista
            console.bidCounter = 0;
            updateItem(console, pos, &consoleList);

            anyInvalidated = true;
        }
    }

    if (!anyInvalidated) {
        printf("+ Error: InvalidateBids not possible\n");
    }
}

/*
 * Objetivo: Procesar el comando [R]emove para eliminar consolas sin pujas
 * Entradas:
 *   - commandNumber: número de comando
 * Salidas: Imprime el resultado del comando
 */
void processRemoveCommand(char *commandNumber) {
    tPosL pos, nextPos;
    bool anyRemoved = false;

    printf("%s R\n", commandNumber);

    // Recorrer la lista y eliminar consolas sin pujas
    pos = first(consoleList);
    while (pos != LNULL) {
        tItemL console = getItem(pos, consoleList);

        // Guardar la siguiente posición antes de eliminar
        nextPos = next(pos, consoleList);

        if (console.bidCounter == 0) {
            // Mostrar información antes de eliminar
            printf("Removing console %s seller %s brand %s price %.2f bids %d\n",
                   console.consoleId, console.seller,
                   (console.consoleBrand == nintendo) ? "nintendo" : "sega",
                   console.consolePrice, console.bidCounter);

            // Eliminar la consola
            deleteAtPosition(pos, &consoleList);
            anyRemoved = true;
        }

        pos = nextPos;
    }

    if (!anyRemoved) {
        printf("+ Error: Remove not possible\n");
    }
}

/*
 * Objetivo: Procesar el comando [S]tats para mostrar estadísticas
 * Entradas:
 *   - commandNumber: número de comando
 * Salidas: Imprime el resultado del comando
 */
void processStatsCommand(char *commandNumber) {
    tPosL pos;
    int nintendoCount = 0, segaCount = 0;
    float nintendoSum = 0.0, segaSum = 0.0;
    float maxIncrease = -1.0;
    tItemL topBidConsole;
    tItemS topBid;
    bool foundTopBid = false;

    printf("%s S\n", commandNumber);

    // Si la lista está vacía
    if (isEmptyList(consoleList)) {
        printf("+ Error: Stats not possible\n");
        return;
    }

    // Recorrer la lista y mostrar cada consola
    for (pos = first(consoleList); pos != LNULL; pos = next(pos, consoleList)) {
        tItemL console = getItem(pos, consoleList);

        // Mostrar información de la consola
        printf("Console %s seller %s brand %s price %.2f",
               console.consoleId, console.seller,
               (console.consoleBrand == nintendo) ? "nintendo" : "sega",
               console.consolePrice);

        if (console.bidCounter > 0) {
            tItemS highestBid = peek(console.bidStack);
            printf(" bids %d top bidder %s\n", console.bidCounter, highestBid.bidder);

            // Calcular incremento porcentual
            float originalPrice = console.consolePrice;
            float topBidPrice = highestBid.consolePrice;
            float increase = ((topBidPrice - originalPrice) / originalPrice) * 100.0;

            // Actualizar la consola con la puja más alta
            if (increase > maxIncrease) {
                maxIncrease = increase;
                topBidConsole = console;
                topBid = highestBid;
                foundTopBid = true;
            }
        } else {
            printf(". No bids\n");
        }

        // Actualizar estadísticas por marca
        if (console.consoleBrand == nintendo) {
            nintendoCount++;
            nintendoSum += console.consolePrice;
        } else {
            segaCount++;
            segaSum += console.consolePrice;
        }
    }

    // Mostrar estadísticas por marca
    printf("\nBrand     Consoles    Price  Average\n");
    printf("Nintendo%10d%9.2f%9.2f\n", nintendoCount, nintendoSum,
           (nintendoCount > 0) ? nintendoSum / nintendoCount : 0.0);
    printf("Sega    %10d%9.2f%9.2f\n", segaCount, segaSum,
           (segaCount > 0) ? segaSum / segaCount : 0.0);

    // Mostrar información de la mejor puja
    if (foundTopBid) {
        printf("Top bid: console %s seller %s brand %s price %.2f bidder %s top price %.2f increase %.2f%%\n",
               topBidConsole.consoleId, topBidConsole.seller,
               (topBidConsole.consoleBrand == nintendo) ? "nintendo" : "sega",
               topBidConsole.consolePrice, topBid.bidder, topBid.consolePrice, maxIncrease);
    } else {
        printf("Top bid not possible\n");
    }
}

/*
 * Objetivo: Procesar cada comando según su tipo
 * Entradas:
 *   - commandNumber: número del comando
 *   - command: tipo de comando (N, D, B, A, I, R, S)
 *   - param1, param2, param3, param4: parámetros del comando
 * Salidas: Imprime el resultado del comando
 */
void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4) {
    // Inicializar la lista si no se ha hecho aún
    if (!initialized) {
        createEmptyList(&consoleList);
        initialized = 1;
    }

    // Mostrar encabezado del comando
    printf("********************\n");

    switch (command) {
        case 'N':
            processNewCommand(commandNumber, param1, param2, param3, param4);
            break;
        case 'D':
            processDeleteCommand(commandNumber, param1);
            break;
        case 'B':
            processBidCommand(commandNumber, param1, param2, param3);
            break;
        case 'A':
            processAwardCommand(commandNumber, param1);
            break;
        case 'I':
            processInvalidateBidsCommand(commandNumber);
            break;
        case 'R':
            processRemoveCommand(commandNumber);
            break;
        case 'S':
            processStatsCommand(commandNumber);
            break;
        default:
            printf("Unknown command %c\n", command);
            break;
    }
}

/*
 * Objetivo: Leer y procesar los comandos desde un archivo
 * Entradas:
 *   - filename: nombre del archivo
 * Salidas: No hay valor de retorno
 */
void readTasks(char *filename) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {
        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4);
        }

        fclose(f);
    } else {
        printf("Cannot open file %s.\n", filename);
    }
}

/*
 * Objetivo: Función principal del programa
 * Entradas:
 *   - nargs: número de argumentos
 *   - args: array de argumentos
 * Salidas: Código de retorno del programa
 */
int main(int nargs, char **args) {
    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name);

    return 0;
}