/*
TITLE: PROGRAMMING II LABS                   SUBTITLE: P2

AUTHOR 1: Ali Abu-afash Nayef  LOGIN 1: ali.nayef@udc.es

AUTHOR 2: Pedro Rodríguez Raposo  LOGIN 2: pedro.rodriguez.raposo@udc.es

GROUP: 1.2                                                        DATE: 03/04/2025
*/

#include "console_list.h"
#include <stdlib.h>
#include <string.h>

// Función auxiliar para crear un nuevo nodo
bool createNode(tPosL* p) {
    *p = malloc(sizeof(struct tNode));
    return (*p != LNULL);
}

/*
 * Objetivo: Crear una lista vacía
 * Entradas:
 *   - l: puntero a la lista a inicializar
 * Salidas:
 *   - Lista inicializada (vacía)
 * Precondiciones: Ninguna
 * Postcondiciones: La lista queda inicializada como vacía (LNULL)
 */
void createEmptyList(tList* l) {
    *l = LNULL;
}

/*
 * Objetivo: Determinar si la lista está vacía
 * Entradas:
 *   - l: lista
 * Salidas:
 *   - true si la lista está vacía, false en caso contrario
 * Precondiciones: La lista debe estar inicializada
 * Postcondiciones: No modifica la lista
 */
bool isEmptyList(tList l) {
    return (l == LNULL);
}

/*
 * Objetivo: Devolver la posición del primer elemento de la lista
 * Entradas:
 *   - l: lista
 * Salidas:
 *   - Posición del primer elemento de la lista
 *   - LNULL si la lista está vacía
 * Precondiciones: La lista debe estar inicializada
 * Postcondiciones: No modifica la lista
 */
tPosL first(tList l) {
    return l;
}

/*
 * Objetivo: Devolver la posición del último elemento de la lista
 * Entradas:
 *   - l: lista
 * Salidas:
 *   - Posición del último elemento de la lista
 *   - LNULL si la lista está vacía
 * Precondiciones: La lista debe estar inicializada
 * Postcondiciones: No modifica la lista
 */
tPosL last(tList l) {
    tPosL p;

    if (isEmptyList(l)) {
        return LNULL;
    }

    for (p = l; p->next != LNULL; p = p->next);
    return p;
}

/*
 * Objetivo: Devolver la posición siguiente a una posición dada
 * Entradas:
 *   - p: posición en la lista
 *   - l: lista
 * Salidas:
 *   - Posición siguiente a p
 *   - LNULL si p es la última posición o no es válida
 * Precondiciones: La lista debe estar inicializada
 * Postcondiciones: No modifica la lista
 */
tPosL next(tPosL p, tList l) {
    if (p == LNULL) {
        return LNULL;
    }
    return p->next;
}

/*
 * Objetivo: Devolver la posición anterior a una posición dada
 * Entradas:
 *   - p: posición en la lista
 *   - l: lista
 * Salidas:
 *   - Posición anterior a p
 *   - LNULL si p es la primera posición o no es válida
 * Precondiciones: La lista debe estar inicializada
 * Postcondiciones: No modifica la lista
 */
tPosL previous(tPosL p, tList l) {
    tPosL q;

    if (p == l) {
        return LNULL;
    }

    for (q = l; q != LNULL && q->next != p; q = q->next);
    return q;
}

/*
 * Objetivo: Insertar un elemento en la lista de forma ordenada por consoleId
 * Entradas:
 *   - d: elemento a insertar
 *   - l: puntero a la lista
 * Salidas:
 *   - true si se insertó correctamente
 *   - false si no hay memoria disponible
 * Precondiciones: La lista debe estar inicializada
 * Postcondiciones: Si hay memoria disponible, la lista incluye el elemento
 *                 en la posición que le corresponde ordenada por consoleId
 */
bool insertItem(tItemL d, tList *l) {
    tPosL q, p, r;

    // Crear el nuevo nodo
    if (!createNode(&q)) {
        return false;
    }

    q->data = d;
    q->next = LNULL;

    // Si la lista está vacía, el nuevo nodo es el primero
    if (isEmptyList(*l)) {
        *l = q;
        return true;
    }

    // Buscar la posición donde insertar (ordenado por consoleId)
    p = *l;
    r = LNULL;

    while ((p != LNULL) && (strcmp(p->data.consoleId, d.consoleId) < 0)) {
        r = p;
        p = p->next;
    }

    // Si hay que insertar al principio
    if (r == LNULL) {
        q->next = *l;
        *l = q;
    } else {
        // Insertar entre r y p
        q->next = r->next;
        r->next = q;
    }

    return true;
}


/*
 * Objetivo: Eliminar el elemento de una posición específica de la lista
 * Entradas:
 *   - p: posición del elemento a eliminar
 *   - l: puntero a la lista
 * Salidas: No hay valor de retorno
 * Precondiciones:
 *   - La lista no está vacía
 *   - La posición p es válida
 *   - La consola en dicha posición tiene una pila de pujas vacía
 * Postcondiciones: El elemento en la posición p es eliminado
 */
void deleteAtPosition(tPosL p, tList* l) {
    tPosL q;

    if (p == *l) {
        // Eliminar el primer elemento
        *l = p->next;
    } else {
        // Eliminar un elemento que no es el primero
        q = previous(p, *l);
        q->next = p->next;
    }

    free(p);
}

/*
 * Objetivo: Obtener el elemento en una posición específica de la lista
 * Entradas:
 *   - p: posición del elemento a obtener
 *   - l: lista
 * Salidas:
 *   - El elemento en la posición p
 * Precondiciones: La posición p debe ser válida en la lista
 * Postcondiciones: No modifica la lista
 */
tItemL getItem(tPosL p, tList l) {
    return p->data;
}

/*
 * Objetivo: Actualizar el elemento en una posición específica de la lista
 * Entradas:
 *   - d: nuevo valor para el elemento
 *   - p: posición del elemento a actualizar
 *   - l: puntero a la lista
 * Salidas: No hay valor de retorno
 * Precondiciones: La posición p debe ser válida en la lista
 * Postcondiciones: El elemento en la posición p es actualizado con el valor d
 */
void updateItem(tItemL d, tPosL p, tList* l) {
    p->data = d;
}

/*
 * Objetivo: Buscar un elemento en la lista por su identificador de consola
 * Entradas:
 *   - id: identificador de consola a buscar
 *   - l: lista
 * Salidas:
 *   - Posición del elemento si se encuentra
 *   - LNULL si no se encuentra o la lista está vacía
 * Precondiciones: La lista debe estar inicializada
 * Postcondiciones: No modifica la lista
 */
tPosL findItem(tConsoleId id, tList l) {
    tPosL p;

    // La lista está ordenada por consoleId, aprovechamos este hecho
    for (p = l; (p != LNULL) && (strcmp(p->data.consoleId, id) < 0); p = p->next);

    // Verificar si encontramos el elemento o si ya pasamos donde debería estar
    if (p != LNULL && strcmp(p->data.consoleId, id) == 0) {
        return p;  // Encontrado
    }

    return LNULL;  // No encontrado
}
