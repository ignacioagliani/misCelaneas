#include <stdio.h>
/*
Algoritmos y Programación I (TA130) – Curso Santisi – 1er parcialito – 27/09/2024
Resolver los siguientes problemas en forma clara y legible en código ISO-C99.
1. a. Escribir una función
unsigned int mi_atoi(const char s[]);
que dada una cadena de caracteres s devuelva el número entero contenido en ella. No deben realizarse
validaciones.
Por ejemplo: mi_atoi("130") -> 130.
Aclaración: No está permitido el uso de funciones de la biblioteca. Todas las necesarias deben ser
implementadas.
Ayuda: Los caracteres numéricos '0' al '9' son consecutivos en la tabla ASCII.
b. Dar un mínimo ejemplo de invocación de la función.
*/
unsigned int potencia(size_t n,size_t i) {
    if (i == 0) {
        return 1;
    }
    return n * potencia(n,i-1);
}

unsigned int mi_atoi(const char s[]) {
    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }
    unsigned int numero_int = 0;
    for (size_t i = 0; i < len; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            int digito = (size_t) (s[i] - '0');
            numero_int += (unsigned int) (digito * (potencia((size_t) 10,len-1-i)));
        }
    }
    return numero_int;
}
/*
int main(void) {
    const char ejemplo[7] = "123654";
    unsigned int numero = mi_atoi(ejemplo);
    printf("%u\n",numero);
    return 0;
}
*/
/*
Explicacion
*/

/*
2. a. Escribir una función que reciba una matriz M en R^N×N y que devuelva si la matriz recibida es la matriz
identidad.
b. Dar un mínimo ejemplo de invocación de la función.
*/
#include <stdbool.h>
#define N 3
bool es_identidad(int matriz[][N]) {
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            if (i != j) {
                if (matriz[i][j] != 0) {
                    return false;
                }
            }
            if (i == j) {
                if (matriz[i][j] != 1) {
                    return false;        
                }
            }
        }
    }
    return true;
}
/*
int main(void) {
    int M[N][N] = {{1,0,0},{0,1,0},{0,0,1}};
    bool identidad = es_identidad(M);
    if (identidad) {
        printf("Es identidad!\n");
    } else {
        printf("No es identidad\n");
    }
    return 0;
}
*/
/*
Explicacion:

*/

/*
3. Los parcialitos de Algoritmos y Programación se puntuan del 0 al 10 y se aprueban con más de 4.
Escribir un programa que deje que el docente ingrese la nota de un parcialito y que le diga si el alumno
aprobó o reprobó.
Realizar todas las validaciones pertinentes.
*/
#include <string.h> // para strlen()
#include <stdlib.h> // para atoi()
#include <ctype.h>  // para isdigit()
int main(void) {
    printf("Escribir una nota del 0 al 10: \n");
    char buffer[8];
    if (!fgets(buffer,sizeof(buffer),stdin)) {
        printf("ERROR: no se pudo cargar nota\n");
        return 1;
    }
    if (strlen(buffer) - 1 > 2) {
        printf("ERROR: nota demasiado larga\n");
        return 1;
    }
    if (buffer[0] == '-') {
        printf("ERROR: no se admiten calificaciones negativas\n");
        return 1;
    }
    if (buffer[0] == '\n') {
        printf("ERROR: nota vacía\n");
        return 1;
    }
    buffer[strlen(buffer)-1] = '\0';
    for (size_t i = 0; i < strlen(buffer); i++) {
        if (!isdigit((unsigned char)buffer[i])) {
            printf("ERROR: no todos los caracteres son digitos\n");
            return 1;
        }
    }
    int nota = atoi(buffer);
    if (nota > 10) {
        printf("ERROR: la nota es mayor a 10\n");
        return 1;
    }
    if (nota < 4) {
        printf("El alumno reprobó\n");
        return 0;
    } else {
        printf("El alumno aprobó\n");
        return 0;
    }
}
/*
Explicacion
*/