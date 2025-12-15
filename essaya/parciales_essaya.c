#include <stdio.h>
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

int main(void) {
    return 0;
}
