#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para malloc

/*
Ejercicio 17.1. Escribir una función que permita calcular el área de un rectángulo dada su basey altura.
*/
int calcular_area_rectangulo(int base, int altura) {
    int area = base * altura;
    return area;
}

/*
Ejercicio 17.2. Escribir una función que reciba un número entero n y calcule el factorial de n.
a) En forma iterativa.
*/
size_t calcular_factorial_iterativo(size_t n) {
    size_t contador = 0;
    size_t factorial = 1;
    while (contador < n) {
        factorial = factorial * (n - contador);
        contador += 1;
    }
    return factorial;
}

/*
b) En forma recursiva.
*/
size_t calcular_factorial_recursivo(size_t n) {
    if (n == 0) {
        return 1;
    }
    return n * calcular_factorial_recursivo(n - 1);
}

/*
Ejercicio 17.3. Escribir una función que reciba un arreglo de números y la cantidad de elementos, y devuelva el promedio.
*/

float devolver_promedio(int* arreglo_numeros,int* longitud) {
    if (longitud == 0) {
        return (float)0;
    }
    int suma = 0;
    for (int i = 0; i < *longitud; i++) {
        suma += arreglo_numeros[i];
    }
    return ((float)suma/ *longitud);
}

/*
Ejercicio 17.4. Usando las funciones printf y sizeof, escribir un programa que imprima el
tamaño en bytes de cada uno de los siguientes tipos: bool, char, short, int, long, float, double,
bool*, char*, short*, int*, long*, float*, double*.

Aviso: yo lo voy a hacer como una función, no como un programa.
Si fuese un programa, la funcion deberia llamarse 'main'.
*/
void imprimir_tamano_datos(void) {
    size_t tam_bool = sizeof(bool);
    size_t tam_char = sizeof(char);
    size_t tam_short = sizeof(short);
    size_t tam_int = sizeof(int);
    size_t tam_long = sizeof(long);
    size_t tam_float = sizeof(float);
    size_t tam_double = sizeof(double);
    size_t tam_puntero_a_bool = sizeof(bool*);
    size_t tam_puntero_a_char = sizeof(char*);
    size_t tam_puntero_a_short = sizeof(short*);
    size_t tam_puntero_a_int = sizeof(int*);
    size_t tam_puntero_a_long = sizeof(long*);
    size_t tam_puntero_a_float = sizeof(float*);
    size_t tam_puntero_a_double = sizeof(double*);
    printf("Bytes que ocupa un bool: %zu\nBytes que ocupa un char: %zu\nBytes que ocupa un short: %zu\n"
        "Bytes que ocupa un int: %zu\nBytes que ocupa un long: %zu\nBytes que ocupa un float: %zu\n"
        "Bytes que ocupa un double: %zu\nBytes que ocupa un puntero a bool: %zu\nBytes que ocupa un puntero a char: %zu\n"
        "Bytes que ocupa un puntero a short: %zu\nBytes que ocupa un puntero a int: %zu\n"
        "Bytes que ocupa un puntero a long: %zu\nBytes que ocupa un puntero a float: %zu\n"
        "Bytes que ocupa un puntero a double: %zu\n",tam_bool,tam_char,tam_short,tam_int,tam_long,tam_float,tam_double,
    tam_puntero_a_bool,tam_puntero_a_char,tam_puntero_a_short,tam_puntero_a_int,tam_puntero_a_long,tam_puntero_a_float,
    tam_puntero_a_double);
}

/*
Ejercicio 17.5. Implementar la función unsigned int strlen(const char *s) que devuelve la
longitud de la cadena s (sin contar el último caracter '\0').
a) En forma iterativa.

Atención: le pongo strlenn con dos 'n' porque no funca con solo una. Te pide incluir '<string.h>'
*/

unsigned int strlenn(const char *s) {
    unsigned int contador = 0;
    while (s[contador] != '\0') {
        contador++;
    }
    return contador;
}

/*
b) En forma recursiva.
*/
unsigned int _strlen_recursivo(const char* s, size_t n) {
    if (s[n] == '\0') {
        return n;
    }
    return _strlen_recursivo(s, n+1);
}

unsigned int strlen_recursivo(const char* s) {
    size_t n = 0;
    unsigned int len = _strlen_recursivo(s,n);
    return len;
}

/*
Ejercicio 17.6. Implementar la función void invertir(char *s) que invierte la cadena s (in-
place).
*/

void invertir(char* s) {
    size_t i = 0;
    size_t len = strlenn(s) - 1;
    while (i < len) {
        char caracter = s[i]; // Guarda primer caracter
        s[i] = s[len];        // El caracter i pasa a ser igual al de len (en la primera iteracion, el primer caracter pasa a ser igual al último)
        s[len] = caracter;    // El ultimo caracter pasa a ser igual al primero (lo mismo que el paso anterior, pero con el caracter en la posicion 'len')
        i++;
        len--;
    }
}

/*
Ejercicio 17.7. Implementar la función void strcpy(const char *origen, char *destino) que
copia la cadena origen en la dirección de memoria apuntada por destino. Asumir que destino
apunta a un arreglo de caracteres con espacio suficiente (strlen(origen) + 1).

IDEM: le pongo strcopy porque sino no funca
*/
void strcopy(const char *origen, char *destino) {
    size_t len = strlenn(origen);
    for (size_t i = 0; i < len; i++) {
        destino[i] = origen[i];
    }
    destino[len] = '\0';
}

int main() {
    char p[] = "holabb";
    char* copia = malloc(24);
    strcopy(p,copia);
    printf("%s\n",copia);
    free(copia);
    return 0;
}
