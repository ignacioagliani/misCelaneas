#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
/*
Algoritmos y Programación I (95.11) – Curso Essaya – 1er parcialito – 23/09/2022
Resolver los siguientes problemas en forma clara y legible en código ISO-C99.
1. Escribir una función
void imprimir_numero(int n);
que dado un número n lo imprima por stdout. Este problema debe ser resuelto sin el uso de ninguna
función de biblioteca con excepción de putchar().
Por ejemplo, si la función se invoca como imprimir_numero(9511); la misma debe imprimir por la
pantalla 9511.
*/
void imprimir_numero(int n) {
    if (n == 0) {
        putchar('0');
        return;
    }
    if (n < 0) {
        putchar('-');
        n = (-1) * n;
    }
    char invertido[11];
    int i = 0;
    while (n > 0) {
        invertido[i] = (char) (n % 10) + '0';
        n = n / 10;
        i++;
    }
    invertido[i] = '\0';
    i--;
    while (i >= 0) {
        putchar(invertido[i]);
        i--;
    }
}

/*
int main(void) {
    int n = -123;
    imprimir_numero(n);
    return 0;
}
*/

/*
Explicación:
Si el numero que nos pasan por parametro es 0, imprimimos solo '0' y salimos de la funcion. Si el numero es negativo,
imprimimos un menos '-' y convertimos ese numero a positivo. Ahora vamos a almacenar el numero invertido en un 
arreglo de caracteres de 11 caracteres de capacidad: 10 para los ints (ya que el maximo numero que pueden almacenar
las variables de tipo int tiene 10 cifras) y 1 para el caracter '\0'. Ahora inicializamos con 0 una variable 'i'
que nos va a ayudar a completar 'invertido'. El seguimiento del algoritmo para invertir el numero es:

n = 123  |  i = 0  |  invertido = "";
n = 123  |  i = 1  |  invertido = "3"; -> 123 % 10 = 3
n = 12   |  i = 2  |  invertido = "32"; -> 12 % 10 = 2
n = 1    |  i = 3  |  invertido = "321"; -> 1 % 10 = 1
n = 0 -> Salió del ciclo

Observacion [(char) (n % 10) + '0';]: es necesario incluir el '(char)' y el ' + '0' ' para convertir el digito
de int a char (esta accion se llama 'castear de int a char').

Una vez extraido todo el numero, colocamos el caracter '\0' para indicar el fin de la cadena. Es necesario restarle
1 a 'i' para no imprimir el '\0' en el siguiente ciclo while, en el cual vamos a imprimir de manera invertida el
arreglo de numeros invertidos, lo cual va a resultar igual a imprimir los números con el orden que nos piden.
Mientras 'i' sea mayor o igual a cero (cero es el primer indice, necesitamos incluirlo por eso es mayor o igual y
no simplemente mayor estricto), imprimimos el caracter en posición 'i' de 'invertido' y restamos 1 al indice.
*/

/*
2. Un conocido periodista emprendió una cruzada contra el lenguaje inclusivo en el cual considera que
cualquier palabra que contenga el carácter 'e' es un ejemplo de esto y debe ser censurado.
a. Escribir una función es_inclusiva que reciba una cadena de caracteres y que retorne si contiene
alguna letra 'e' o no.
b. Escribir un pequeño ejemplo de código que invoque a la función con alguna cadena e imprima
un mensaje según el resultado.
*/

bool es_inclusiva(const char* cadena) {
    size_t i = 0;
    while (cadena[i] != '\0') {
        char minuscula = tolower(cadena[i]);
        if (minuscula == 'e') {
            return true;
        }
        i++;
    }
    return false;
}

/*
int main(void) {
    char cadena_ejemplo[] = "hola don pepito";
    bool es_incl = es_inclusiva(cadena_ejemplo);
    if (es_incl) {
        printf("Es inclusiva\n");
    } else {
        printf("No es inclusiva\n");
    }
    return 0;
}
*/
/*
Explicacion:
Primero, creamos una variable de tipo size_t llamada 'i' y la inicializamos en 0. Esta variable la vamos a usar como
indice para recorrer nuestra 'cadena'. Para recorrer la cadena usamos un ciclo while. Mientras el caracter en la
posicion 'i' sea diferente a '\0' (el caracter que indica el fin de las cadenas), guardamos la letra que estamos
analizando y la convertimos a minuscula. Preguntamos si esa letra es igual a 'e' (la convertimos en minuscula para
solamente preguntar si la letra es 'e' y no preguntar si es 'e' o 'E' mayuscula). Si es 'e' la letra, devolvemos
true. Si no lo es, aumentamo 1 el indice 'i' y seguimos iterando. Una vez que se llega al final sin encontrar
una letra 'e', devolvemos false.

En el programita guardamos una cadena random y creamos una variable bool en la cual se va a guardar el resultado
de pasar por parametro esa cadena a la funcion 'es_inclusiva'. Si es inclusiva, imprime un mensaje, si no lo es,
imprime otro. Por último, devuelve 0 para indicar que se ejecutó correctamente.
*/

/*
3. Escribir un programa que le pida al usuario una distancia y un tiempo y que, de ser posible, calcule y
muestre la velocidad asociada.
¡Suerte! :)
*/

int main(void) {
    char buffer[11];
    int distacia;
    int tiempo;
    printf("Introduzca una distancia (en metros)\n");
    if (!fgets(buffer,sizeof(buffer),stdin)) {
        printf("No se pudo capturar el input\n");
        return 1;
    }
    distacia = atoi(buffer);
    if (distacia < 0) {
        printf("Distancia invalida\n");
        return 1;
    }
    printf("Introduzca un tiempo (en segundos)\n");
    if (!fgets(buffer,sizeof(buffer),stdin)) {
        printf("No se pudo capturar el input\n");
        return 1;
    }
    tiempo = atoi(buffer);
    if (tiempo <= 0) {
        printf("Tiempo Invalido\n");
        return 1;
    }
    float velocidad = (float) distacia / tiempo;
    printf("Velocidad: %fm/s\n",velocidad);
    return 0;
}

/*
Explicacion:
Recordatorio del CBC: v = d / t

Como nos piden un programa, vamos a encapsular todo en una función 'main'. Dentro de este 'main', vamos a definir
un buffer, en el cual se van a almacenar las entradas por teclado del usuario. Vamos a usar un solo buffer y no
dos simplemente porque no es necesario. Debido a que el maximo numero que se puede almacenar en una variable
de tipo numero entero es 2.147.483.647, que son diez digitos, el buffer que vamos a crear va a tener 10
caracteres y uno mas para el '\0'. También declaramos dos variables de tipo int. Una para la distancia y otra
para el timepo. Después de esto, imprimimos un mensaje descriptivo para pedir la distancia. Para pedirle al usuario
un dato por teclado, vamos a usar la función fgets de la libreria standard input/output (stdio). Esta función recibe
tres parametros: el buffer donde se almacenarán los datos, el tamaño del buffer, y de dónde los va a leer a estos
datos.En nuestro caso, el buffer está en la variable 'buffer', para obtener el tamaño voy a usar la función sizeof(),
aunque también podríamos haber puesto 12 directamente, pero no está bueno porque estaríamos hardcodeando el tamaño.
Si el buffer llega a cambiar su tamaño en algún momento, la función 'sizeof' nos ahorra el tiempo de cambiarlo
manualmente. El último parametro es de donde va a leer el dato. En este caso es la entrada estandar o standard
input (stdin), lo cual vendría a ser el teclado. Si hay algún problema al leer el dato, imprimimos un mensaje
informativo y devolvemos 1, lo cual indica que surgió un error. Después, usamos la funcion 'ASCII to Int' (atoi)
de la libreria standard (stdlib) para transformar un texto a número. En este caso, transformamos la entrada del
usuario (que, a pesar de haber introducido un número, se guarda como char) a numero entero.
Aclaración: si el usuario escribe texto, se toma como 0. Se asume que el usuario solo ingresa numeros enteros.
Si el numero ingresado por el usuario es negativo, imprimimos un mensaje avisando que eso no es una distancia
válida y devolvemos 1.
Este mismo proceso se realiza para el tiempo, así que no lo voy a volver a explicar.
Por último, guardamos la velocidad resultante en una variable de tipo float, la imprimimos y devolvemos 0 para
indicar que el programa se ejecutó con exito.
*/