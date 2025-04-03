#include "bid_stack.h"
#include <stdbool.h>
#include <stdlib.h>

// Función auxiliar para crear un nuevo nodo
bool createNode(tPosS* p) {
    *p = malloc(sizeof(struct tNodeS));
    return (*p != SNULL);
}

/*
 * Objetivo: Crear una pila vacía.
 * Precondiciones: Ninguna.
 * Postcondiciones: La pila queda inicializada como vacía (SNULL).
 */
void createEmptyStack(tStack* stack) {
    *stack = SNULL;
}

/*
 * Objetivo: Insertar un elemento en la cima de la pila.
 * Entradas:
 *   - item: elemento a insertar.
 *   - stack: puntero a la pila.
 * Salidas:
 *   - true si el elemento fue apilado, false si no hay memoria o la pila está llena.
 * Precondiciones: La pila debe estar inicializada.
 * Postcondiciones: Si hay memoria y la pila no supera 25 elementos, el nuevo elemento queda en la cima.
 */
bool push(tItemS item, tStack* stack) {
    tPosS aux;
    int count = 0;
    tPosS current = *stack;

    // Verificar que la pila no supere el máximo de 25 pujas.
    while (current != SNULL && count < MAX_STACK) {
        count++;
        current = current->next;
    }
    if (count >= MAX_STACK) {
        return false; // La pila está llena.
    }

    if (!createNode(&aux)) {
        return false; // Error al asignar memoria.
    }

    aux->data = item;
    aux->next = *stack;
    *stack = aux;
    return true;
}

/*
 * Objetivo: Eliminar el elemento situado en la cima de la pila.
 * Precondiciones: La pila debe estar inicializada y no estar vacía.
 * Postcondiciones: Se elimina el elemento de la cima y se libera la memoria.
 */
void pop(tStack* stack) {
    tPosS aux;
    if (*stack != SNULL) {
        aux = *stack;
        *stack = (*stack)->next;
        free(aux);
    }
}

/*
 * Objetivo: Recuperar el elemento de la cima sin eliminarlo.
 * Precondiciones: La pila debe estar inicializada y no estar vacía.
 * Postcondiciones: La pila no se modifica.
 */
tItemS peek(tStack stack) {
    return stack->data;
}

/*
 * Objetivo: Determinar si la pila está vacía.
 * Salidas:
 *   - true si la pila está vacía, false en caso contrario.
 * Precondiciones: La pila debe estar inicializada.
 */
bool isEmptyStack(tStack stack) {
    return (stack == SNULL);
}
