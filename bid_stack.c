/*
TITLE: PROGRAMMING II LABS                   SUBTITLE: P2

AUTHOR 1: Ali Abu-afash Nayef  LOGIN 1: ali.nayef@udc.es

AUTHOR 2: Pedro Rodríguez Raposo  LOGIN 2: pedro.rodriguez.raposo@udc.es

GROUP: 1.2                                                        DATE: 03/04/2025
*/

#include "bid_stack.h"
#include <stdbool.h>

/*
 * Objetivo: Crear una pila vacía.
 * Precondiciones: Ninguna.
 * Postcondiciones: La pila queda inicializada como vacía (top = SNULL).
 */
void createEmptyStack(tStack* stack) {
    stack->top = SNULL;
}

/*
 * Objetivo: Insertar un elemento en la cima de la pila.
 * Entradas:
 *   - item: elemento a insertar.
 *   - stack: puntero a la pila.
 * Salidas:
 *   - true si el elemento fue apilado, false si la pila está llena.
 * Precondiciones: La pila debe estar inicializada.
 * Postcondiciones: Si hay espacio, el nuevo elemento queda en la cima.
 */
bool push(tItemS item, tStack* stack) {
    if (stack->top >= MAX_STACK - 1) {
        return false;  // La pila está llena
    }

    stack->top++;
    stack->data[stack->top] = item;
    return true;
}

/*
 * Objetivo: Eliminar el elemento situado en la cima de la pila.
 * Precondiciones: La pila debe estar inicializada y no estar vacía.
 * Postcondiciones: Se elimina el elemento de la cima.
 */
void pop(tStack* stack) {
    if (stack->top > SNULL) {
        stack->top--;
    }
}

/*
 * Objetivo: Recuperar el elemento de la cima sin eliminarlo.
 * Precondiciones: La pila debe estar inicializada y no estar vacía.
 * Postcondiciones: La pila no se modifica.
 */
tItemS peek(tStack stack) {
    return stack.data[stack.top];
}

/*
 * Objetivo: Determinar si la pila está vacía.
 * Salidas:
 *   - true si la pila está vacía, false en caso contrario.
 * Precondiciones: La pila debe estar inicializada.
 */
bool isEmptyStack(tStack stack) {
    return (stack.top == SNULL);
}