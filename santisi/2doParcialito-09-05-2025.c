#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
/*
Algoritmos y Programación (TA130) – Curso Santisi – 2do parcialito – 09/05/2025
Resolver los siguientes problemas en forma clara y legible en código ISO-C99.
1. El formato de números de punto flotante FP8 E4M3 permite almacenar un número de la forma
(−1)^s × 2e × m, donde s es el signo, e el exponente y m la mantisa según el siguiente esquema:
MSB LSB
+----+----+----+----+----+----+----+----+
| s | e3 | e2 | e1 | e0 | m2 | m1 | m0 |
+----+----+----+----+----+----+----+----+
Se pide:
Definir el tipo fp8_t en base al tipo uint8_t.
Implementar la función int comparar_fp8(fp8_t a, fp8_t b); que compare los números a
y b. La función debe devolver negativo si a < b, positivo si a > b y cero si a = b.
Si un número es positivo (s = 0) y otro negativo (s = 1) ese número será mayor. Lo mismo si un
exponente es mayor que otro y luego si una mantisa es mayor a otra, en ese orden.
*/
typedef uint8_t fp8_t;

int comparar_fp8(fp8_t a, fp8_t b) {
    if (a == b) {
        return 0;
    }
    if (a >> 7 < b >> 7 ) {
        return 1;
    }
    if (a >> 7 > b >> 7 ) {
        return -1;
    }
    fp8_t e = 0x78; // 0x78 = 01111000
    fp8_t exp_a = (a & e) >> 3;
    fp8_t exp_b = (b & e) >> 3;
    if (exp_a > exp_b) {
        return 1;
    }
    if (exp_a < exp_b) {
        return -1;
    }
    fp8_t m = 0x07; // 0x07 = 000000111
    fp8_t mant_a = a & m;
    fp8_t mant_b = b & m;
    if (mant_a > mant_b) {
        return 1;
    }
    return -1;
}
/*
int main(void) {
    fp8_t n1 = 0x12;
    fp8_t n2 = 0x12;
    int resultado = comparar_fp8(n1,n2);
    if (resultado == 0) {
        printf("Son iguales!\n");
    } else if (resultado == 1) {
        printf("N1 > N2\n");
    } else {
        printf("N2 > N1\n");
    }
    return 0;
}
*/
/*
Explicación:
Primero, defino el tipo que el enunciado pide.

Segundo, creo la función 'comparar_fp8'. En esta función, lo primero que hago es pregunta si los numeros a y b,
del tipo fp8_t, son iguales. En caso afirmativo,devuelvo cero. Si no son iguales, continuo preguntando si el signo
de 'a' es menor al signo de 'b', si ese es el caso, devuelvo uno. El signo de los numeros los obtengo desplazando
desplazando siete digitos de 'a' y de 'b' a la derecha. Si el signo es 1, el numero es negativo, y si es 0, es 
positivo. Por lo tanto, si el signo de 'a' es 0 y el de 'b' es 1, inexorablemente 'a' es mas grande por ser positivo.
Luego, pregunto si el signo de 'b' es menor que el de 'a'. Si lo es, devuelvo -1.

a = 10111011
b = 11010100

a >> 7 = 00000001 -> negativo
Asi obtenemos el signo

Despues obtengo los exponentes de 'a' y de 'b'. ¿Como los obtengo? haciendo las siguiente operaciones.

a = 10111011
b = 11010100

a = 1       0111       011
b = 1       1010       100
   signo   exponente  mantisa

    10111011
 &  01111000
  -------------
r = 00111000

r >> 3 = 00000111 -> exponente

Vamos por partes. Primero, necesitamos obtener unicamente los signo del exponente, dejando ceros donde esta
el signo y la mantisa. Esto lo hacemos haciendo la operacion AND con el número 01111000, que en formato
hexadecimal es 0x78. Listo, ya tenemos el numero, pero nos sobran una banda de ceros por derecha, los cuales
nos modifican el resultado, dando un numero el cual no nos sirve. ¿Que hacemos? Movemos los tres ceros a la derecha.
De esta manera, nos quedamos solo con el exponente. ¿Y los ceros a izquierda? Con esos no hay drama, no nos cambian
nada. Listorti, ya tenemos los exponentes, los cuales vamos a comparar. Si el exponente de a es mayor que el b, 
se devuelve 1. En cambio, si el exponente de b es mayor que el de a, devuelve -1.

Finalmente, necesitamos obtener la mantisa, que son los ultimos tres digitos. Para ello, volvemos a usar la 
operacion AND, dejando tres unos en las ultimas tres posiciones. Por lo tanto, almacenamos el resultado de 
a & 0x07 y b & 0x07 en variables. ¿Por qué 0x07 y no 0000 0111? Porque C interpreta los números en base 10,
lo cual no nos sirve en este caso, entonces es crusial escribirlos en base 16.

101110111
000000111
----------
000000111 -> mantisa

Entonces si la mantisa de a es mayor que la de b, se devuelve 1. En caso contrario, se devuelve -1.

*/

/*
2. Se tiene una estructura alumno con un padrón de tipo int y un nombre de tipo char *:
Declarar la estructura y redefinirla como alumno_t.
Implementar la función alumno_t *clonar_alumno(const alumno_t *a); que devuelva una
copia exacta de a en memoria nueva.
*/
struct alumno {
    int padron;
    char* nombre;
};

typedef struct alumno alumno_t;

alumno_t* clonar_alumno(const alumno_t* a) {
    if (!a) {
        printf("ERROR a no es valido\n");
        return NULL;
    }
    alumno_t* clon = malloc(sizeof(alumno_t));
    if (!clon) {
        printf("No se pudo reservar memoria\n");
        return NULL;
    }
    clon->padron = a->padron;
    clon->nombre = NULL;
    if (a->nombre) {
        size_t bytes_nombre = strlen(a->nombre) + 1;
        char* copia_nombre = malloc(bytes_nombre);
        if (!copia_nombre) {
            printf("ERROR no se pudo reservar memoria para el nombre\n");
            free(clon);
            return NULL;
        }
        memcpy(copia_nombre,a->nombre,bytes_nombre);
        clon->nombre = copia_nombre;
    }
    return clon;
}

void imprimir_struct_alumno(const alumno_t* datos) {
    int padron = datos->padron;
    char* nombre = datos->nombre;
    printf("Padrón: %d\nNombre: %s\n",padron,nombre);
}
/*
int main(void) {
    alumno_t alumno_ejemplo;
    alumno_ejemplo.padron = 111111;
    alumno_ejemplo.nombre = "Ignacio";
    alumno_t* clon = clonar_alumno(&alumno_ejemplo);
    imprimir_struct_alumno(clon);
    free(clon->nombre);
    free(clon);
    return 0;
}
*/

/*
Explicación:
Primero, defino la estructura 'alumno'.
Segundo, redefino 'alumno' como 'alumno_t'.
Tercero, dentro de la funcion, valido que el puntero 'a' no sea nulo (!a -> a == NULL).
Cuarto, reservo la cantidad necesaria de memoria en el heap para almacenar un dato 'alumno_t'.
Quinto, valido qu ese haya podido reservar esa mamoria. En caso negativo, imprimo un mensaje informativo y
devuelvo NULL.
Despues, guardo en la variable 'padron' de 'clon' el padron que está en 'a'.
Luego, inicializo la variable 'nombre' de 'clon' con el puntero nulo.
En el caso de que el nombre en la varible 'a' sea distinto a NULL, guardo en una variable la cantidad de bytes
justa que voy a usar para almacenar el nombre. ¿Por que esa cantidad de strlen + 1? Tomemos como ejemplo mi nombre,
"Ignacio":

Nombre -> "Ignacio" | len = 7 | len + 1 = 8

Lo que quiero guardar en clon->nombre es "Ignacio\0", lo cual son 8 caracteres.

clon->nombre = "Ignacio\0"

Debido al caracter '\0', el cual indica el final de una cadena de caracteres, es necesario reservar un byte
mas que el largo del nombre.
Observación: en la variable 'nombre' está la cadena "Ignacio\0", lo cual técnicamente serían 8 caracteres, pero la
función strlen no cuanta el caracter '\0', por eso hay que sumarle manualmente 1.

Teniendo ya la cantidad de memoria en una variable, usamos la funcion 'malloc()' para reservar memoria para almacenar
el nombre. Si no se puede reservar esa memoria,se imprime un mensaje informativo, se libera lo reservado para 'clon'
y delvuelve el puntero nulo.
Si sale todo bien, se usa la funcion memory copy 'memcpy()', la cual recibe tres argumentos:

1er argumento: En qué direccion de memoria vas a almacenar lo copiado
2do argumento: Qué direccion de memoria vas a copiar
3er argumento: La cantidad de bytes que vas a copiar

En este caso, vamos a almacenar en 'copia_nombre' lo que está en 'a->nombre' y la cantidad 'bytes_nombres'.
Almacenamos en 'clon->nombre' la variable 'copia_nombre' y devolvemos 'clon'.
La funcion de imprimir el struct no la pide el ejercicio, pero la hice yo para checkear nomás.
*/

/*
3. Implementar una función char *leer_linea(); que lea una línea desde stdin (hasta el '\n'). Debe
devolver la cadena leída o NULL en caso de error.
*/
char* leer_linea() {
    size_t longitud = 0;
    size_t capacidad = 64;
    char* linea = malloc(capacidad);
    if (!linea) {
        printf("No se pudo reservar memoria");
        return NULL;
    }
    int c = getchar();
    if (c == EOF) {
        free(linea);
        return NULL;
    }
    while (c != EOF && c != '\n') {
        if (longitud + 1 >= capacidad) {
            capacidad = capacidad * 2;
            char* realocado = realloc(linea,capacidad);
            if (!realocado) {
                printf("No se pudo realocar memoria\n");
                free(linea);
                return NULL;
            }
            linea = realocado;
        }
        linea[longitud] = (char) c;
        c = getchar();
        longitud++;
    }
    linea[longitud] = '\0';
    return linea;
}

int main(void) {
    char* leido = leer_linea();
    if (!leido) {
        return 0;
    }
    printf("%s\n",leido);
    free(leido);
    return 0;
}

/*
Explicación:
La manera en la cual encaré el ejercicio es almacenando la cadena en un arreglo dinamico (un arreglo el cual va
creciendo a medida que le cargás caracteres).
Primero inicialize´'longitud' en cero, porque todavía no le cargué nada, y 'capacidad' la inicie en 64. La capacidad
es la cantidad de caracteres que el arreglo va a tener en primera instancia.
Luego, reservo la cantidad 'capacidad' de bytes en el heap. Si no se pueden reservar, imprimo un mensaje informativo
y devuelvo NULL.
Despues, uso la función 'getchar()' para pedir un caracter. Si c == EOF, libero lo reservado en 'linea' devuelvo NULL.

Mientras el caracter insertado por el usuario sea
diferente a End Of File y distinto a ENTER '\n' (¿por que esta condicion? Por ejemplo, si el usuario apreta '\n',
tenemos que '\n' != EOF y '\n' == '\n', entonces esto es false, así que sale del ciclo. Hago esta aclaracion porque
al principio pensaba que la condicion correcta era while (c != EOF || c != '\n'), pero no tiene sentido, porque si
c == EOF, nunca va a ser igual a '\n', por lo tanto, el ciclo no termina mas, es infinito. Ya que, considerando
c='\n', (c != EOF || c == '\n') -> true y siempre va a ser true).

Dentro del bloque if, lo primero que hago es fijarme si la longitud + 1 es mayor a la capacidad ¿Por que? Porque
consideremos una cadena de 32 caracteres (o sea, longitud = 32). Imaginemos que el usuario quiere guardar esa
cadena en 'linea'. Además de esos 32 caracteres, al final hay que guardar '\0' para indicar el fin de la cadena,
lo cual demanda un byte extra, es decir, 33 caracteres. Pero si la capacidad es 32, no entra el '\0', así que,
si la cadena sin '\0' tiene longitud = 32, inexorablemente vamos a tener que aumentar la cantidad de memoria que
le reservamos a 'linea'. ¿Y cómo hacemos esto? Primero, multiplicamos por 2 la capacidad. Luego, usamos la
funcion reallocation, realloc(), la cual recibe como primer argumento el nombre de la variable a la cual le reser
vamos memoria y como segundo argumento el nuevo tamaño. Si no se puede reservar mas memoria, se imprime un
mensaje informativo, se libera la memoria previamente reservada y devuelve NULL. Si se puede reservar, pisamos
el contenido de 'linea' para hacerlo igual a la variable en la cual realocamos memoria (el cual es igual a lo
que teníamos en línea, pero con mas memoria).
En el caso de que no se entre al bloque if, se guarda en la posicion 'longitud' el caracter introducido por
el usuario, pero es necesario castearlo a char, porque lafuncion getchar() devuelve int. Después, la longitud
se incrementa en 1 y se repite el ciclo. Una vez fuera del ciclo, se agrega el caracter '\0' en la última
posicion y se devuelve la línea.
*/
