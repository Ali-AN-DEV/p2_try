/*
TITLE: PROGRAMMING II LABS                   SUBTITLE: P2

AUTHOR 1: Ali Abu-afash Nayef  LOGIN 1: ali.nayef@udc.es

AUTHOR 2: Pedro Rodríguez Raposo  LOGIN 2: pedro.rodriguez.raposo@udc.es

GROUP: 1.2                                                        DATE: 03/04/2025
*/

#include "console_list.h"
#include <string.h>

/*
 * Objetivo: Crear una lista vacía
 * Entradas:
 *   - l: puntero a la lista a inicializar
 * Salidas:
 *   - Lista inicializada (vacía)
 * Precondiciones: Ninguna
 * Postcondiciones: La lista queda inicializada como vacía
 */
void createEmptyList(tList* l) {
    l->lastPos = LNULL;
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
    return (l.lastPos == LNULL);
}

/*
 * Objetivo: Devolver la posición del primer elemento de la lista
 * Entradas:
 *   - l: lista
 * Salidas:
 *   - Posición del primer elemento de la lista
 *   - LNULL si la lista está vacía
 * Precondiciones: La lista debe estar inicializada y NO VACÍA
 * Postcondiciones: No modifica la lista
 */
tPosL first(tList l) {
    if (isEmptyList(l)) {
        return LNULL;
    }
    return 0;
}

/*
 * Objetivo: Devolver la posición del último elemento de la lista
 * Entradas:
 *   - l: lista
 * Salidas:
 *   - Posición del último elemento de la lista
 *   - LNULL si la lista está vacía
 * Precondiciones: La lista debe estar inicializada y NO VACÍA
 * Postcondiciones: No modifica la lista
 */
tPosL last(tList l) {
    return l.lastPos;
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
    if (p == LNULL || p >= l.lastPos) {
        return LNULL;
    }
    return p + 1;
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
    if (p == LNULL || p <= 0) {
        return LNULL;
    }
    return p - 1;
}

/*
 * Objetivo: Insertar un elemento en la lista de forma ordenada por consoleId
 * Entradas:
 *   - d: elemento a insertar
 *   - l: puntero a la lista
 * Salidas:
 *   - true si se insertó correctamente
 *   - false si no hay espacio disponible
 * Precondiciones: La lista debe estar inicializada
 * Postcondiciones: Si hay espacio disponible, la lista incluye el elemento
 *                 en la posición que le corresponde ordenada por consoleId
 */
bool insertItem(tItemL d, tList *l) {
    tPosL pos, i;

    // Verificar si hay espacio
    if (l->lastPos == MAX_LIST - 1) {
        return false;
    }

    // Si la lista está vacía
    if (isEmptyList(*l)) {
        l->data[0] = d;
        l->lastPos = 0;
        return true;
    }

    // Buscar la posición donde insertar (ordenado por consoleId)
    pos = 0;
    while (pos <= l->lastPos && strcmp(l->data[pos].consoleId, d.consoleId) < 0) {
        pos++;
    }

    // Desplazar elementos hacia la derecha
    for (i = l->lastPos; i >= pos; i--) {
        l->data[i + 1] = l->data[i];
    }

    // Insertar el nuevo elemento
    l->data[pos] = d;
    l->lastPos++;

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
 * Postcondiciones: El elemento en la posición p es eliminado
 */
void deleteAtPosition(tPosL p, tList* l) {
    tPosL i;

    // Desplazar elementos hacia la izquierda
    for (i = p; i < l->lastPos; i++) {
        l->data[i] = l->data[i + 1];
    }

    l->lastPos--;

    // Si la lista queda vacía
    if (l->lastPos < 0) {
        l->lastPos = LNULL;
    }
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
    return l.data[p];
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
    l->data[p] = d;
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
    tPosL pos;

    // La lista está ordenada por consoleId, aprovechamos este hecho
    for (pos = 0; pos <= l.lastPos; pos++) {
        int cmp = strcmp(l.data[pos].consoleId, id);
        if (cmp == 0) {
            return pos;  // Encontrado
        }
        if (cmp > 0) {
            break;  // Ya pasamos donde debería estar
        }
    }

    return LNULL;  // No encontrado
}