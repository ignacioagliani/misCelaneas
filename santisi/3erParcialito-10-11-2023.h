#ifndef VOTACION_H

#define VOTACION_H

#include <stdbool.h>

typedef struct votacion votacion_t;

// votacion_crear devuelve un puntero a una nueva votacion si no ocurren errores o NULL si ocurren.
votacion_t* votacion_crear(void);

// votacion_porcentaje_opcion devuelve un flotante con el porcentaje de votos de
// 'opcion' en la votacion 'v'. Devuelve -1 si falla.
float votacion_porcentaje_opcion(const votacion_t *v, const char *opcion);

// votacion_votar permite añadir un voto a la 'opcion' en la votacion 'v', Devuelve
// false si falla o true si sale todo bien.
bool votacion_votar(votacion_t *v, const char *opcion);

#endif
