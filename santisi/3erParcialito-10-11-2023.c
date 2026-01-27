#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "3erParcialito-10-11-2023.h"
/*
Algoritmos y Programación I (95.11) – Curso Santisi – 3er parcialito –
10/11/2023
Resolver los siguientes problemas en forma clara y legible en código ISO-C99.
1. Se quiere modelar el TDA votación, que permita decidir entre diferentes opciones.
Se pide:
a. Declarar la estructura que encapsula el TDA. Explicar qué representa
cada miembro y documentar la invariante de representación.
b. Implementar la primitiva float votacion_porcentaje_opcion(const
votacion_t *v, const char *opcion); que devuelva el porcentaje de
votos de la opcion.
c. Implementar la primitiva bool votacion_votar(votacion_t *v,
const char *opcion); que agregue la opción a la lista de opciones.
votacion_t *v = votacion_crear();
votacion_votar(v, "membrillo");
votacion_votar(v, "batata");
votacion_votar(v, "pastelera");
votacion_votar(v, "batata");
votacion_porcentaje_opcion(v, "membrillo"); // 0.25 o 25
*/
typedef struct diccionario_votacion {
    char* clave;
    int valor;
} votos_t;

struct votacion {
    votos_t** votos;
    int votos_emitidos;
    int cantidad_candidatos;
    int capacidad;
};

votacion_t* votacion_crear(void) {
    votacion_t* nueva_votacion = malloc(sizeof(votacion_t));
    if (!nueva_votacion) {
        return NULL;
    }
    nueva_votacion->cantidad_candidatos = 0;
    nueva_votacion->votos_emitidos = 0;
    nueva_votacion->capacidad = 5;
    nueva_votacion->votos = malloc(nueva_votacion->capacidad * sizeof(votos_t*));
    if (!nueva_votacion->votos) {
        free(nueva_votacion);
        return NULL;
    }
    return nueva_votacion;
}

float votacion_porcentaje_opcion(const votacion_t *v, const char *opcion) {
    if (!v || !opcion || v->votos_emitidos == 0) {
        return -1.0;
    }
    for (int i = 0; i < v->cantidad_candidatos; i++) {
        if (strcmp(v->votos[i]->clave, opcion) == 0) {
            return (float) ((float)v->votos[i]->valor / v->votos_emitidos) * 100;
        }
    }
    return -1;
}

bool votacion_votar(votacion_t *v, const char *opcion) {
    if (!v || !opcion) {
        return false;
    }

    for (int i = 0; i < v->cantidad_candidatos; i++) {
        if (strcmp(v->votos[i]->clave,opcion) == 0) {
            v->votos[i]->valor += 1;
            v->votos_emitidos += 1;
            return true;
        }
    }
    if (v->cantidad_candidatos >= v->capacidad) {
        v->capacidad *= 2;
        votos_t** realocado = realloc(v->votos,v->capacidad * sizeof(votos_t*));
        if (!realocado) {
            return false;
        }
        v->votos = realocado;
    }
    votos_t* nuevo_candidato = malloc(sizeof(votos_t));
    if (!nuevo_candidato) {
        return false;
    }
    char* nombre_candidato = malloc(strlen(opcion) + 1);
    if (!nombre_candidato) {
        free(nuevo_candidato);
        return false;
    }
    strcpy(nombre_candidato,opcion);
    nuevo_candidato->clave = nombre_candidato;
    nuevo_candidato->valor = 1;
    v->votos_emitidos += 1;
    v->votos[v->cantidad_candidatos] = nuevo_candidato;
    v->cantidad_candidatos += 1;
    return true;
}

/*
int main(void) {
    votacion_t *v = votacion_crear();
    if (!v) {
        return 1;
    }
    votacion_votar(v, "membrillo");
    votacion_votar(v, "batata");
    votacion_votar(v, "pastelera");
    votacion_votar(v, "batata");
    float porc = votacion_porcentaje_opcion(v, "membrillo"); // 0.25 o 25
    printf("Resultado: %.1f%%\n",porc);
    for (int i = 0; i < v->cantidad_candidatos; i++) {
        free(v->votos[i]->clave);
        free(v->votos[i]);
    }
    free(v->votos);
    free(v);
    return 0;
}
*/
/*
Explicacion:

*/

/*
2. Se tiene un archivo binario que contiene un size_t n seguido de n valores
flotantes de doble precisión, según el siguiente esquema:
+----+----+----+----+----+- -+----+
| n | a1 | a2 | a3 | a4 | ... | an |
+----+----+----+----+----+- -+----+
a. Escribir una función bool escribir_doubles(const char *r, const
double a[], size_t n); que reciba una ruta r y un arreglo a de n
doubles y los escriba en un archivo binario según el formato anterior.
b. Escribir una función double *leer_doubles(const char *r, size_t
*n); que reciba una ruta r a un archivo binario y devuelva por el nombre
el arreglo de doubles contenido en él y en n la cantidad de elementos
leídos.
*/
bool escribir_doubles(const char *r, const double a[], size_t n) {
    if (!r) {
        return false;
    }
    if (n > 0 && !a) {
        return false;
    }
    FILE* archivo = fopen(r,"wb");
    if (!archivo) {
        return false;
    }
    if (fwrite(&n,sizeof(size_t),1,archivo) != 1) {
        fclose(archivo);
        return false;
    }
    if (fwrite(a,sizeof(*a),n,archivo) != n) {
        fclose(archivo);
        return false;
    }
    fclose(archivo);
    return true;
}

double *leer_doubles(const char *r, size_t *n) {
    if (!r || !n) {
        return NULL;
    }
    FILE* archivo = fopen(r,"rb");
    if (!archivo) {
        return NULL;
    }
    size_t elementos_leidos;
    if (fread(&elementos_leidos,sizeof(size_t),1,archivo) != 1) {
        fclose(archivo);
        return NULL;
    }
    double* arreglo_contenido = malloc(elementos_leidos * sizeof(double));
    if (!arreglo_contenido) {
        fclose(archivo);
        return NULL;
    }
    if (fread(arreglo_contenido,sizeof(double),elementos_leidos,archivo) != elementos_leidos) {
        free(arreglo_contenido);
        fclose(archivo);
        return NULL;
    }
    fclose(archivo);
    *n = elementos_leidos;
    return arreglo_contenido;
}

/*
int main(void) {
    size_t n = 3;
    size_t n1;
    const char r[] = "ejemplo.bin";
    const double a[] = {1.12,2.3,9.6};
    if (!escribir_doubles(r,a,n)) {
        return 1;
    }
    double* arr = leer_doubles(r,&n1);
    if (!arr) {
        return 1;
    }
    printf("%zu\n",n1);
    for (size_t i = 0; i < n; i++) {
        printf("%f\n",arr[i]);
    }
    return 0;
}
*/
/*
3. Dado el formato (y las funciones) del ejercicio 2 escribir un programa que se
ejecute:
$ ./transformar entrada salida a b
que cargue en memoria el arreglo de coordenadas contenido en el archivo
binario entrada y aplique la transformación ax+b a cada uno de sus elementos
y lo guarde en el archivo binario salida.
Se deben utilizar las funciones desarrolladas en el punto 2.
¡Suerte! :)
*/

int main(int argc, char** argv) {
    if (argc != 5) {
        return 1;
    }
    const char* entrada = argv[1];
    const char* salida = argv[2];
    double a = atof(argv[3]);
    double b = atof(argv[4]);
    size_t doubles_leidos = 0;
    double* arreglo_doubles = leer_doubles(entrada,&doubles_leidos);
    if (!arreglo_doubles && doubles_leidos != 0) {
        return 1;  // error real de lectura
    }
    if (doubles_leidos == 0) {
        if (!escribir_doubles(salida,NULL,0)) {
            free(arreglo_doubles);
            return 1;
        }
        free(arreglo_doubles);
        return 0;
    }
    double transformados[doubles_leidos];
    for (size_t i = 0; i < doubles_leidos; i++) {
        double x = arreglo_doubles[i];
        transformados[i] = a*x+b;
    }
    if (!escribir_doubles(salida,transformados,doubles_leidos)) {
        free(arreglo_doubles);
        return 1;
    }
    free(arreglo_doubles);
    return 0;
}
