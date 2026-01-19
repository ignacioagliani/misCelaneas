#ifndef TURNOS_H
#define TURNOS_H

#include <stdbool.h>

typedef struct turnos turnos_t;

// Crea un sistema de turnos vacío. Devuelve NULL si falla.
turnos_t* turnos_crear(void);

// Devuelve un puntero a char con el nombre del siguiente cliente o NULL si algo falla.
char* turnos_proximo(turnos_t* t);

// Crea nuevos turnos. Devuelve true si se creo bien y false en caso contrario.
bool turnos_nuevo(turnos_t *t, const char *cliente);

#endif
