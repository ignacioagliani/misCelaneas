#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // para INT_MIN
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


int main(void) {
    const int arr[6] = {1,2,3,4,5,6};
    int p = 2;
    int val = obtener_valor(arr,6,p);
    printf("%d\n",val);
    return 0;
}
