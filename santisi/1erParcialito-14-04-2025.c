#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define N 3
#define M 3
/*
Algoritmos y Programación I (TA130) – Curso Santisi – 1er parcialito – 14/04/2025
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
int potencia(int base, size_t exponente) {
    int resultado = 1;
    while (exponente > 0) {
        resultado = resultado * base;
        exponente -= 1;
    }
    return resultado;
}

unsigned int mi_atoi(const char s[]) {
    unsigned int numero = 0;
    size_t largo_arreglo = 0;
    while (s[largo_arreglo] != '\0') {
        largo_arreglo++;
    }
    for (size_t j = 0; j < largo_arreglo; j++) {
        int numero_no_casteado = (int)(s[j] - '0') * potencia(10,largo_arreglo-1-j);
        numero += (unsigned int) (numero_no_casteado);
    }
    return numero;
}

int main(void) {
    const char ejemplo[] = "5";
    printf("%u\n",mi_atoi(ejemplo));
    return 0;
}

/*
Explicación:
La función potencia permite calcular base^exponente.
En la función 'mi_atoi' creo una variable donde almaceno el ressultado como entero sin signo. Despues creo una 
vaiable donde almaceno el largo del arreglo. Luego, voy sumando las centenas, decenas y unidades del numero
(si es de tres cifras).
Seguimiento (para el "123"):

j = 0   s[j] = 1    largo_arreglo = 3   largo_aggreglo-1-j = 3 - 1 - 0 = 2
(int)(s[j] - '0') * potencia(10,largo_arreglo-1-j) = 1 * 100 = 100
numero = 0 + 100 = 100

j = 1   s[j] = 2    largo_arreglo = 3   largo_aggreglo-1-j = 3 - 1 - 1 = 1
(int)(s[j] - '0') * potencia(10,largo_arreglo-1-j) = 2 * 10 = 20
numero = 0 + 100 + 20 = 120

j = 2   s[j] = 3    largo_arreglo = 3   largo_aggreglo-1-j = 3 - 1 - 2 = 0
(int)(s[j] - '0') * potencia(10,largo_arreglo-1-j) = 3 * 1 = 3
numero = 0 + 100 + 20 + 3 = 123

Una vez que se termina el ciclo for, devuelve el resultado.

*/

/*
2. a. Escribir una función que reciba una matriz A en RN×M y que devuelva si cada una de las N filas de la
matriz suman lo mismo o no.
b. Dar un mínimo ejemplo de invocación de la función.
*/
bool suman_lo_mismo(int matriz[N][M]) {
    int suma1 = 0;
    int suma2 = 0;
    for (size_t j = 0; j < M; j++) {
        suma1 += matriz[0][j];
    }
    for (size_t i = 1; i < N; i++) {
        for (size_t j = 0; j < M; j++) {
            suma2 += matriz[i][j];
        }
        if (suma1 != suma2) {
            return false;
        }
        suma2 = 0;
    }
    return true;
}

/*
int main(void) {
    int matriz_ejemplo[N][M] = {
        {1,1,1},
        {1,1,1},
        {1,1,0}
    };
    bool suman_igual = suman_lo_mismo(matriz_ejemplo);
    if (suman_igual) {
        printf("Suman igual!\n");
    } else {
        printf("No suman igual\n");
    }
    return 0;
}
*/
/*
Explicación:
Creo dos variables, una que almacena la suma de la primer fila y otra que suma el resto de filas.
El primer ciclo for se encarga de sumar solo los elementos de la primer fila y aguarda el resultado en 'suma1'.
El segundo ciclo for se encarga de sumar el resto de filas. En el caso de R^3X3, suma la segunda fila. Despues, 
compara si la suma de la fila 1 es distinta a la de fila 2. En el caso que así sea, devuelve false, sino, reinicia
el contador 'suma2' con 0. Por último, repite el proceso con la tercer fila. Si la suma es igual, devuelve true.
*/


/*
3. Un inversor está decidido a hacer la diferencia con el precio del dólar. El precio del dólar está entre $1000 y
$1400. Si el dólar está por encima de $1200 quiere vender, y si está por debajo quiere comprar.
Escribir un programa que deje que el inversor ingrese la cotización del dólar y le diga si comprar o vender.
Realizar todas las validaciones pertinentes.
*/

/*
int main(void) {
    char buffer[8];
    printf("Ingrese una cotización: $");
    if (!fgets(buffer,sizeof(buffer),stdin)) {
        printf("ERROR al pedir dato\n");
        return 1;
    }
    if (buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }
    if (buffer[0] == '\0') {
        printf("ERROR entrada vacía\n");
        return 1;
    }
    if (buffer[0] == '-') {
        printf("ERROR las cotizaciones no pueden ser negativas\n");
        return 1;
    }
    for (int i = 0; i < strlen(buffer); i++) {
        if (!isdigit((unsigned char) buffer[i])) {
            printf("ERROR no todos los digitos son numeros\n");
            return 1;
        }
    }
    int cotizacion = atoi(buffer);
    if (cotizacion > 1200 && cotizacion <= 1400) {
        printf("Vender\n");
        return 0;
    } else if (cotizacion >= 1000 && cotizacion < 1200) {
        printf("Comprar\n");
        return 0;
    } else if (cotizacion == 1200) {
        printf("No comprar ni vender\n");
        return 0;
    } else {
        printf("Cotización Fuera de Rango");
        return 0;
    }
}
*/

/*
Explicación:
Creo un buffer de 8 bytes para almacenar el ingreso del usuario. Si falla el ingreso, imprimo error y devuelvo 1.
Quito el caracter del espacio. Si el primer elemento es '\0', la cadena esta vacia y eso es invalido.
Si el primer caracter es un menos, tambien está mal e imprimo un mensaje descriptivo y devuelvo 1.
Despues verifico que todos los caracteres sean numeros.
Si sale todo bien, lo convierto a int.
Por último, según las cotizaciones del usuario, imprime una cosa u otra.
*/