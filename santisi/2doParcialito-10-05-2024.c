#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
/*
Algoritmos y Programación I (TA130–95.11) – Curso Santisi – 2do parcialito – 10/05/2024
Resolver los siguientes problemas en forma clara y legible en código ISO-C99.
1. Se requiere implementar por software la instrucción Biet Field Extract de los procesadores Intel x86:
uint32_t bextr(uint32_t a, uint16_t b);
El byte más liviano de b es un inicio y el más pesado una longitud. La función extrae longitud bits de a a
partir de esa posición.
Ejemplo: a = 1001 0011 1011 1101, b = 0000 1000 0000 0100, en este caso el inicio es 0000 0100, es
decir 4 y la longitud es 0000 1000, es decir 8. Entonces se extraerán 8 bits de a desde la posición 4 y se
devolverá 0011 1011.
*/
uint32_t bextr(uint32_t a, uint16_t b) {
    uint16_t inicio = b & 0xFF;
    uint16_t longitud = b >> 8;
    if (longitud == 0 || longitud >= 32 || inicio >= 32) {
        return 0;
    }
    uint32_t a_desplazado = a >> inicio;
    uint32_t mascara;
    mascara = (1u << (uint32_t) longitud) - 1u;
    uint32_t bytes_extraidos = a_desplazado & mascara;
    return bytes_extraidos;
}
/*
int main(void) {
    uint32_t a = 0x93BD; // 0x93BD = 1001 0011 1011 1101
    uint16_t b = 0x0804; // 0x0804 = 0000 1000 0000 0100
    uint32_t c = bextr(a,b);
    printf("0x%X\n",c);
    return 0;
}
*/
/*
En la funcion, lo primero que hago es obtener el inicio y la longitud. ¿Como?
Haciendo las siguientes operaciones:

b = 0000 1000 0000 0100

Inicio (los 8 bits de la derecha):
  0000 1000 0000 0100
& 0000 0000 1111 1111 -> 0xFF
----------------------
  0000 0000 0000 0100

Longitud (los 8 bits de la izquierda):
  0000 1000 0000 0100 >> 8 = 0000 0000 0000 1000

En el caso de que la longitud sea 0 o mayor o igual a 32 o el inicio mayor o igual a 32 (casos borde), devuelve 0.
Ya teniendo el inicio y la longitud, podemos operar sobre el numero 'a'. Lo primero que hago es mover un cantidad
'inicio' de bits a la derecha y guardar ese numero en una variable.

a = 1001 0011 1011 1101
a >> 'inicio' = a >> 4 = 0000 1001 0011 1011

Joya, podemos ver que los ultimos 8 digitos son los que necesitacion, así que creamos una mascara para obtenerlos.
¿Qué es una mascara? Es una secuencia de bits con los cuales operamos para obtener los bits que necesitamos.
En este caso, vamos a usar:

mascara = (1u << (uint32_t) longitud) - 1u

¿Que es 1u? es para representar un 1 unsigned (sin signo).
¿Que es (uint32_t) longitud? Convierte la longitud de uint16_t a uint32_t para operar con 'a_desplazado', el
cual es uint32_t.

mascara = (1u << (uint32_t) longitud) - 1u
mascara = (0000 0000 0000 0001 << 8) - 1u
mascara = (0000 0001 0000 0000) - 1u
mascara = 0000 0001 0000 0000 - 1u
mascara = 0000 0000 1111 1111

Entonces, operando con AND, nos queda:
a_desplazado: 0000 1001 0011 1011
& mascara   : 0000 0000 1111 1111
            ------------------------
bytes_extrai: 0000 0000 0011 1011

Guardamos el resultado este en una variable y lo devolvemos.

*/

/*
2. Se tiene un tipo terminal_t definido sobre una estructura. La misma tiene dos miembros: historial de
tipo char (*)[MAX_STRING] y nhistorial de tipo size_t:
Declarar la estructura struct terminal,
Redefinirla como terminal_t,
Implementar la función:
terminal_t *terminal_clonar(const terminal_t *t);
que realiza una copia completa de t en memoria nueva y la devuelve.
*/
#define MAX_STRING 48

struct terminal {
    char (*historial)[MAX_STRING];
    size_t nhistorial;
};

typedef struct terminal terminal_t;

terminal_t* terminal_clonar(const terminal_t* t) {
    if (!t) {
        printf("Parametro inválido\n");
        return NULL;
    }
    terminal_t* clonado = malloc(sizeof(terminal_t));
    if (!clonado) {
        printf("No se pudo reservar memoria\n");
        return NULL;
    }
    clonado->historial = NULL;
    clonado->nhistorial = t->nhistorial;
    if (t->historial) {
        size_t tamaño_historial = sizeof(*t->historial) * t->nhistorial;
        char (*historial_clonado)[MAX_STRING] = malloc(tamaño_historial);
        if (!historial_clonado) {
            printf("No se pudo reservar memoria para el historial\n");
            free(clonado);
            return NULL;
        }
        memcpy(historial_clonado,t->historial,tamaño_historial);
        clonado->historial = historial_clonado;
    }
    return clonado;
}

void imprimir_terminal(const terminal_t* term) {
    if (term) {
        size_t nhist = term->nhistorial;
        for (size_t i = 0; i < nhist; i++) {
            printf("%s\n",term->historial[i]);
        }
        printf("%zu\n",nhist);
    } else {
        printf("Error al cargar terminal\n");
    }
}

int main(void) {
    terminal_t ejemplo;
    ejemplo.nhistorial = 3;
    ejemplo.historial = malloc(ejemplo.nhistorial * sizeof(*ejemplo.historial));
    if (!ejemplo.historial) {
        return 0;
    }
    strcpy(ejemplo.historial[0],"hola");
    strcpy(ejemplo.historial[1],"como");
    strcpy(ejemplo.historial[2],"estas");
    terminal_t* clon = terminal_clonar(&ejemplo);
    if (!clon) {
        free(ejemplo.historial);
        return 0;
    }
    imprimir_terminal(clon);
    free(ejemplo.historial);
    free(clon->historial);
    free(clon);
    return 0;
}

/*
Explicación:
Primero defino una constante global MAX_STRING totalmente arbitraria. El valor mucho no importa en este caso. En
verdad, no sería un constante global. #define crea un macro del preprocesador. Esto significa que se crea una
regla de reemplazo de texto que se aplica antes de compilar.

Segundo, defino el struct como lo pide en el enunciado y despues lo redefino como 'terminal_t'.

Dentro de la función 'terminal_clonar', verifico que 't' no sea NULL. Si lo es imprimo un mensaje descriptivo y 
devuelvo el puntero nulo. Despues trato de reservar la cantidad de memoria necesaria para alojar un dato de tipo
'terminal_t'. Si no se puede reservar dicha memoria, imprimo un mensajito avisando eso y devuelvo NULL. Una vez
reservada la esa memoria, inicio en esa direccion de memoria a 'historial' como NULL y a 'nhistorial' con el mismo
valor que tiene el parametro 't'. Si 't->historia' no es nulo, calculo la cantidad de memoria necesaria para
almacenar el historial. Esta cantidad de memoria se calcula como el tamaño de un arreglo de MAX_STRING
chars (48 bytes en este caso) multiplicado por la cantidad de registros (nhistorial). Luego, trato de reservar esa
cantidad de memoria para un puntero de un arreglo de chars de MAX_STRING de tamaño. Si no se puede reservar esta
cantidad de memoria, imprimo un mensaje informando la situacion, libero la memoria previamente reservada para
'clonado' y devuelvo NULL. Luego, copio en la direccion de memoria de 'historial_clonado' una cantidad 'tamaño_historial'
de bytes de la direccion de memoria 't->historial'. Por último, asigno en 'clonado->historial' el historial cargado
en 'historial_clonado' y devuelvo 'clonado'.

Las otras dos funciones ('imprimir_terminal' y 'main') son de verificacion. No son tan importantes.
*/

/*
Implementar una función char *centrar(const char *cadena, size_t largo); que centre la cadena a
una línea de largo caracteres y la devuelva.
Por ejemplo dada la llamada con ("hola", 10) la función debe devolver la cadena "   hola   ".
*/
char* centrar(const char* cadena, size_t largo) {
    size_t largo_cadena = strlen(cadena);
    size_t espacios_izquierda = 0;
    size_t espacios_derecha = 0;
    if (largo_cadena > largo) {
        printf("Cantidad de caracteres insuficiente\n");
        return NULL;
    }
    size_t espacios_totales = largo - largo_cadena;
    if (espacios_totales % 2 == 0) {
        espacios_izquierda = espacios_totales / 2;
        espacios_derecha = espacios_totales / 2;
    }
    if (espacios_totales % 2 != 0) {
        espacios_izquierda = (espacios_totales / 2) + 1;
        espacios_derecha = espacios_totales / 2;
    }
    char* cadena_centrada = malloc(largo + 1);
    if (!cadena_centrada) {
        printf("No se pudo reservar memoria\n");
        return NULL;
    }
    size_t i = 0;
    while (espacios_izquierda > 0) {
         cadena_centrada[i] = ' ';
         i++;
         espacios_izquierda--;
    }
    size_t j = 0;
        while (largo_cadena > 0) {
         cadena_centrada[i] = cadena[j];
         i++;
         j++;
         largo_cadena--;
    }
    while (espacios_derecha > 0) {
        cadena_centrada[i] = ' ';
        i++;
        espacios_derecha--;
    }
    cadena_centrada[i] = '\0';
    return cadena_centrada;
}

/*
int main(void) {
    const char ejemplo[5] = "hola";
    size_t largo = 10;
    char* centrada = centrar(ejemplo,largo);
    if (!centrada) {
         return 0;
    }
    printf("%s\n",centrada);
    free(centrada);
    return 0;
}
*/

/*
Explicacion:
Aclaración: lo que yo entendí del ejercicio es que la cadena centrada a devolver tiene una cantidad 'largo' de
longitud. Con el ejemplo de cadena="hola" y largo=10, serían 3 espacios a la izquierda, cuatro caracteres en 
el medio (propios de la cadena 'hola') y 3 espacios a la derecha, resultando en una cadena de largo=3+4+3=10.

En la función lo primero que hago es inicializar tres variables:
    - 'largo_cadena': almacena el largo de la cadena, sin contar al caracter '\0'.
    - 'espacios_izquierda': inicializo en cero.
    - 'espacios_derecha': inicializo en cero.

Si el largo de la cadena es mayor al largo pasado por parametro (lo cual sería un error porque ni siquiera te
alcanzan los caracteres para contener a la propia cadena), imprimo un mensaje informativo y devuelvo NULL.
En el caso de que efectivamente el largo pasado por parametro sea mayor al largo de la cadena, calculo la cantidad
total de espacios haciendo la resta entre el 'largo' y 'largo_cadena'. En este caso, es: 10-4=6. Ahora bien, si
el resultado de esta resta es par, van a haber la misma cantidad de espacios por izquierda y por derecha. En cambio,
si es impar, no va a quedar perfectamente centrada, así que arbitrariamente elejí que el espacio extra esté a la
izquierda. Ya disponiendo de el largo de la cadena final, reservo esa cantdad de memoria + 1. Ese + 1 es para el
caracter '\0' que indica el fin de una cadena de texto. Si no se puede reservar esa memoria, imprimo un mensaje
informativo y devuelvo el puntero nulo. En este punto, creo una varible de tipo size_t la cual va a contener el
índice actual de la cadena, así que lo voy a iniciar en cero. Para agragar los espacios por izquierda, voy a
usar un ciclo while. Mientras la cantidad de espacios por izquierda sea mayor a cero, voy a insertar en la
posición 'i' un caracter ' ' en 'cadena_centrada'. Una vez insertado, aumento en una unidad el índice 'i' y
disminuyo en una unidad la cantidad de espacios por izquierda. Una vez añadidos todos los espacios a la izquierda
(o sea, cuando 'espacios_izquierda' sea cero), voy a añadir los caracteres de 'cadena'. Para esto, creo otro indice,
al cual voy a llamar 'j'. Otra vez voy a usar un while, pero esta vez la condición es que se ejecute este bucle
mientras 'largo_cadena' sea mayor a cero. Si se cumple esta condición, inserto en la posiciín 'i' de 'cadena_centrada' lo
que está en la posición 'j' de 'cadena'. Despues de eso, aumento 1 'i' y 'j', pero disminuyo 1 'largo_cadena'. Para
insertar los espacios por derecha hago lo mismo que en los espacios por izquierda. Finalmente, agrego el caracter
'\0' en la última posicion y devuelvo la cadena centrada.
*/
