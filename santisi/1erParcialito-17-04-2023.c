#include <stdio.h> // para printf y fgets
#include <stdbool.h>
/*
Algoritmos y Programación I (95.11) – Curso Santisi – 1er parcialito – 17/04/2023
Resolver los siguientes problemas en forma clara y legible en código ISO-C99.

1. En el mundo del software una forma frecuente de abreviar nombres de proyectos consiste en reemplazar
todas sus letras, salvo la primera y la última por el número de letras que fueron reemplazadas. Por ejemplo,
siguiendo esta idea el proyecto "kubernetes" suele abreviarse como "k8s".
a. Implementar una función void abreviar_nombre(char nombre[]); que reciba una cadena de entre 3
y 11 caracteres y la abrevie según este formato.
No se permite el uso de funciones de biblioteca en este ejercicio. Todo lo necesario debe ser implementado.
b. Con un pequeño código de ejemplo mostrar cómo utilizar a la función con la cadena del ejemplo anterior.
*/
void abreviar_nombre(char nombre[]) {
    int len = 0;
    while (nombre[len] != '\0') {
        len += 1;
    }
    if (len < 3 || len > 11) {
        return;
    }
    nombre[1] = (char)('0' + (len-2)); //
    nombre[2] = nombre[len - 1];
    nombre[3] = '\0';
}
/*
int main(void) {
    char cadena[] = "kubernetes";
    abreviar_nombre(cadena);
    printf("%s\n",cadena); // Esta funcion es de la biblioteca stdio, pero por lo que entiendo, la restriccion de las bbiliotecas es solo para el (a).
    return 0;
}
*/

/*
2. Una matriz es simétrica si tiene simetría con respecto a su diagonal principal o, lo que es lo mismo, si sus
filas son iguales a sus columnas.
a. Escribir una función es_simetrica que reciba una matriz de flotantes de tamaño N×N y que retorne si
la misma es simétrica o no.
b. Teniendo #define N 3 escribir un pequeño ejemplo de código que declare y defina una matriz, llame a
la función del punto anterior e imprima un mensaje para el usuario según el resultado.
*/
#define N 3
bool es_simetrica(float matriz[][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matriz[i][j] != matriz[j][i]) {
                return false;
            }
        }
    }
    return true;
}
/*
int main(void) {
    float matriz_no_sim[N][N] = {{1,1,1},{0,0,1},{9,5,8}};
    float matriz_sim[N][N] = {{1,0,0},{0,1,0},{0,0,1}};
    bool simetria = es_simetrica(matriz_no_sim);
    if (simetria == true) {
        printf("La matriz es simética.\n");
    } else {
        printf("La matriz no es simétrica.\n");
    }
    return 0;
}
*/

/*
3. En un sistema masa-resorte el período se calcula como T = 2𝛑 √(m/k), siendo m la masa y k la constante del
resorte.
Escribir un programa que le pida al usuario una masa y una constante elástica y que, de ser posible, le
muestre el período resultante.
Nota: para calcular una raíz cuadrada puede utilizarse la función double sqrt(double x); de la biblioteca
<math.h>.
*/
#include <math.h>
#include <stdlib.h> // para poder usar atof
#define PI 3.14159
int main(void) {
    char masa[16];
    char k_elastica[16];
    printf("Masa (en kilogramos): \n");
    if (!fgets(masa,16,stdin)) {
        return 1;
    }
    printf("Constante elástica (en N/m): ");
    if (!fgets(k_elastica,16,stdin)) {
        return 1;
    }
    double m = atof(masa);
    double k = atof(k_elastica);
    if (m < 0 || k <= 0) {
        printf("Alguno de los datos, ya sea la m=%fkg o k=%fN/m, son inválidos\n",m,k);
        return 1;
    }
    double T = 2 * PI * sqrt(m / k);
    printf("T=%f s\n",T);
    return 0;
}
