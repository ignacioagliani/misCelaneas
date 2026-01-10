#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // para INT_MIN
#include <string.h>
#include <ctype.h> // para tolower()
/*
Advertencia (si cursas con Essaya): los ejercicios del generador de ejercicios de parcial de
la web de Essaya NO representan el nivel de ejercicios tomados en los exámenes.
Los ejercicios de la web son sustancialmente más sencillos de lo que terminan tomando (experiencia
personal mía).
*/

/*
Escribir una función en C que reciba un arreglo de enteros y su tamaño,
y devuelva el índice del elemento máximo
*/
int _devolver_indice_maximo(int* arreglo, int len, int indice_max) {
    if (len == 1) {
        return indice_max;
    }
    if (arreglo[len-1] > arreglo[indice_max]) {
        return _devolver_indice_maximo(arreglo,len-1,len-1);
    }
    return _devolver_indice_maximo(arreglo,len-1,indice_max);
}

int devolver_indice_maximo(int* arreglo, int len) {
    if (len <= 0) {
        printf("Largo Inváliso\n");
        return -1;
    }
    int indice_max = 0;
    return _devolver_indice_maximo(arreglo,len,indice_max);
}

/*
Escribir un programa en C que lea una matriz de enteros de tamaño 3x3 y
calcule la suma de los elementos de la diagonal principal.

Lo escribo como funcion, no como programa.
*/
int calcular_traza_3x3(int matriz[][3]) {
    int traza = 0;
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++){
            if (i == j) {
                traza += matriz[i][j];
            }
        }
    }
    return traza;
}

/*Mas General*/
int traza(int n_col,int i, int matriz[][n_col]) {
    if (i == 1) {
        return matriz[0][0];
    }
    return matriz[i-1][i-1] + traza(n_col,i-1,matriz);
}

/*
Escribir un programa en C que le pida al usuario un número positivo y verifique
que dicho número se encuentre dentro de un rango definido (el cual debe ser definido 
como constantes en el código). En caso de que el número no se encuentre dentro del rango 
el programa debe continuar pidiendo hasta que el usuario no ingrese nada o bien ingrese 
un número correcto.

Lo escribo como funcion. Se asume que el usuario ingresa numeros (atoi convierte texto a 0)
*/
void pedir_numero_rango(void) {
    const int minimo = 0;
    const int maximo = 10;
    const int size_buf = 8;
    char buffer[size_buf];
    for (;;) {
        if (fgets(buffer, size_buf, stdin) == NULL) {
            return;
        }
        if (buffer[0] == '\n') {
            return;
        }
        int numero = atoi(buffer);
        if (numero > minimo && numero < maximo) {
            return;
        }
    } 
}

/*
Escribir un programa en C que lea números enteros y los almacene en un arreglo.
Luego debe imprimir el arreglo en orden inverso.

Se escruibe como funcion
*/
void leer_e_imprimir_arreglo(void) {
    size_t i = 0;
    const size_t size_b = 50; // Arbitrario
    const size_t max_len = 100; // Arbitrario
    int arreglo[max_len];
    char buffer[size_b];
    for (;;) {
        if (!fgets(buffer, size_b, stdin)) {
            break;
        }
        if (buffer[0] == '\n' || i == max_len) {
            while (i != 0) {
                printf("%d ",arreglo[i-1]);
                i--;
            }
            return;
        }
        int numero = atoi(buffer);
        arreglo[i] = numero;
        i++;
    }
}

/*
Escribir en C la función int obtener_valor(const int vector[], int len, int pos).
La función debe devolver el valor que se encuentra en vector[pos], interpretando pos como
en Python. Es decir, pos puede tomar valores entre -len y len - 1; y para los valores
negativos busca los elementos comenzando desde la última posición del vector. Si pos no es
válida, devolver la constante INT_MIN (asumir que la constante ya fue declarada).
*/
int obtener_valor(const int vector[], int len, int pos) {
    if (pos >= 0 && pos < len) {
        return vector[pos];
    } else if (pos < 0 && (pos * -1) <= len) {
        return vector[pos + len];
    } else {
        return INT_MIN;
    }
}

/*
Escribir en C la función `char* strslice(const char* cadena, size_t inicio, size_t fin, size_t step);`
que recibe por parámetro una cadena, un inicio, fin y step, y devuelve la porción de cadena indicada
alojada en el heap. La cantidad de bytes reservados debe ser la necesaria para alojar la cadena
resultante, y no mayor.
*/
char* strslice(const char* cadena, size_t inicio, size_t fin, size_t step) {
    size_t largo_cadena = strlen(cadena);
    if (step == 0 || inicio > fin || fin > largo_cadena) {
        return NULL;
    }
    char cadena_sliceada[largo_cadena + 1];
    size_t j = 0;
    for (size_t i = inicio; i < fin; i+=step) {
        cadena_sliceada[j] = cadena[i];
        j++;
    }
    cadena_sliceada[j] = '\0';
    size_t bytes_reserva = j + 1;
    char* slice = malloc(bytes_reserva);
    if (!slice) {
        return NULL;
    }
    strcpy(slice,cadena_sliceada);
    return slice;
}

/*
Implementar en C la función char* strreplace(const char* cadena, char viejo, char nuevo);
que recibe una cadena, un caracter viejo y un caracter nuevo. La función debe devolver una nueva
cadena alojada en el heap donde todas las ocurrencias de viejo hayan sido reemplazadas por nuevo.
Si no hay ocurrencias, la cadena resultante debe ser idéntica a la original. La cantidad de bytes
reservados debe ser la necesaria para alojar la cadena resultante, y no mayor.
*/
char* strreplace(const char* cadena, char viejo, char nuevo) {
    size_t len_cadena = strlen(cadena);
    size_t len_remplazada = len_cadena + 1; 
    char cadena_remplazada[len_remplazada];
    size_t j = 0;
    while (j < len_cadena) {
        if (cadena[j] == viejo) {
            cadena_remplazada[j] = nuevo;
        } else {
            cadena_remplazada[j] = cadena[j];
        }
        j++;
    }
    cadena_remplazada[j] = '\0';
    char* remplazado_heap = malloc(len_remplazada);
    if (!remplazado_heap) {
        return NULL;
    }
    strcpy(remplazado_heap,cadena_remplazada);
    return remplazado_heap;
}

/*
Implementar en C una función que reciba un número entero y devuelva 1 si es primo,
0 en caso contrario.
*/
int es_primo(int n) {
    if (n <= 1) {
        return 0;
    }
    if (n == 2) {
        return 1;
    }
    if (n % 2 == 0) {
        return 0;
    }
    for (int i = 3; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

/*
Escribir un programa en C que lea números enteros desde la entrada estándar hasta
encontrar un 0, y luego imprima la suma de todos los números leídos.
*/
void leer_y_sumar(void) {
    int suma = 0;
    char buffer[16];
    for (;;) {
        if (!fgets(buffer,16,stdin)) {
            printf("Ingresaste un caracter inválido!\n");
            return;
        }
        int numero = atoi(buffer);
        if (numero == 0) {
            printf("Suma: %d\n",suma);
            return;
        }
        suma += numero;
    }
}

/*
Implementar en C una función que reciba dos cadenas de caracteres y devuelva 1 si son
iguales, 0 en caso contrario. No usar la función strcmp.
*/
int son_iguales(const char* cadena1, const char* cadena2) {
    size_t len_cadena1 = strlen(cadena1);
    size_t len_cadena2 = strlen(cadena2);
    if (len_cadena1 == len_cadena2){
        size_t i = 0;
        while (i < len_cadena1) {
            if (cadena1[i] != cadena2[i]) {
                return 0;
            }
            i++;
        }
        return 1;
    }
    return 0;
}

/*
Escribir un programa en C que lea una cadena de caracteres y cuente cuántas vocales contiene.
*/
size_t contar_vocales(const char* cadena) {
    size_t cantidad_vocales = 0;
    size_t i = 0;
    while (cadena[i] != '\0') {
        char minuscula = (char)tolower((unsigned char)cadena[i]);
        if (minuscula == 'a' || minuscula == 'e' || minuscula == 'i' || minuscula == 'o' || minuscula == 'u') {
            cantidad_vocales++;
        }
        i++;
    }
    return cantidad_vocales;
}

/*
Escribir una función en C que reciba un arreglo de enteros y su tamaño, y devuelva el
índice del elemento máximo
*/
/*
size_t devolver_indice_mayor(const int* arreglo, size_t len) {
    if (len == 0) {
        return 0;
    }
    size_t indice = 0;
    int mayor_elemento = arreglo[0];
    for (int i = 1; i < len; i++) {
        if (arreglo[i] > mayor_elemento) {
            mayor_elemento = arreglo[i];
            indice = i;
        }
    }
    return indice;
}
*/
/*
Implementar una función char* remover_digitos(const char* str) que reciba una cadena y 
retorne una nueva cadena eliminando todos los dígitos. La cadena retornada debe estar
alojada en el heap. La cantidad de bytes reservados debe ser la necesaria para alojar la
cadena resultante, y no mayor.
Ejemplo:
Para la cadena: "Hola123Mundo456"
Se debe devolver: "HolaMundo"
*/
char* remover_digitos(const char* str) {
    int lenstr = strlen(str);
    char cadena_sin_digitos[lenstr + 1];
    size_t j = 0;
    for (int i = 0; i < lenstr; i++) {
        if (str[i] < '0' || str[i] > '9') {
            cadena_sin_digitos[j] = str[i];
            j++;
        }
    }
    cadena_sin_digitos[j] = '\0';
    char* cadena_heap = malloc(j + 1);
    if (!cadena_heap) {
        return NULL;
    }
    strcpy(cadena_heap,cadena_sin_digitos);
    return cadena_heap;
}

int main(void) {
    const char p[]= "Hola123Mundo456";
    char* c = remover_digitos(p);
    printf("%s\n",c);
    free(c);
    return 0;
}
