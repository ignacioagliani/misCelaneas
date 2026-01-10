#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
Algoritmos y Programación I (TA130) – Curso Santisi – 2do parcialito – 14/10/2024
Resolver los siguientes problemas en forma clara y legible en código ISO-C99.
1. En el sistema BCD se utilizan 4 bits para representar dígitos decimales del 0 al
9. En un byte podemos encapsular dos dígitos BCD.
Implementar una función:
uint16_t sumar(uint8_t a, uint8_t b);
que reciba dos números de 2 dígitos BCD y devuelva su suma (que puede tener hasta 3 dígitos).
*/

uint16_t sumar(uint8_t a, uint8_t b) {
    uint8_t primer_digito_a = a >> 4;
    uint8_t segundo_digito_a = a & 0x0F;
    uint8_t primer_digito_b = b >> 4;
    uint8_t segundo_digito_b = b & 0x0F;

    int a_en_decimal = primer_digito_a * 10 + segundo_digito_a;
    int b_en_decimal = primer_digito_b * 10 + segundo_digito_b;

    int suma_en_decimal = a_en_decimal + b_en_decimal;
    int centenas = suma_en_decimal / 100;
    int decenas = (suma_en_decimal / 10) % 10;
    int unidades = suma_en_decimal % 10;

    uint16_t resultado = 0;
    resultado |= (uint16_t) (centenas << 8);
    resultado |= (uint16_t) (decenas << 4);
    resultado |= (uint16_t) (unidades);
    return resultado;
}

/* Explicación:
BCD = Binary Coded Decimal | 0x12 = 1    2
En binario:                        0001 0010
Para obtener le primer digito, desplazamos 4 unidades a la derecha el numero 0001 0010 -> 0000 0001
(lo mismo para b)
Para obtener el segundo, necesitamos considerar que 0x0F = 0000 1111. Entonces:
                                a        = 0001 0010
                                0x0F     = 0000 1111
                                a & 0x0F = 0000 0010
Nota: para lograr un 1 operando con AND, es necesario que los dos numeros sean 1, si ninguno o solo uno
es 1, el resultado es 0.

Como en las primeras 4 variables estan los numeros en decimal ya (C hace las operaciones sobre esos bits)
haces, por ejemplo 12 = (1 * 10) + 2. Luego sumas normalmente ambos numeros en base 10.

Se obtienen las centenas, decenas y unidades en base 10 y se las guarda en variables.

Creamos una variable de tipo entero sin signo de 16 bits para almacenar el resultado.

Hacemos un seguimiento de las operaciones (tomando como 12 en base 10 para operar):
Por lo tanto:
cententenas = 0
decenas = 1
unidades = 2

En Binario:
cententenas = 0000 0000 0000 0000
decenas =     0000 0000 0000 0001
unidades =    0000 0000 0000 0010

Ahora calculamos:
cententenas << 8 = 0000 0000 0000 0000 (desplazas 8 bits a la izquierda)
decenas << 4     = 0000 0000 0001 0000 (desplazas 4 bits a la izquierda)
unidades         = 0000 0000 0000 0010 (queda igual)

          resultado:           0000 0000 0000 0000
OR cententenas << 8:           0000 0000 0000 0000
                               ------------------------------
resultado OR cententenas << 8= 0000 0000 0000 0000

          resultado:           0000 0000 0000 0000
          OR decenas << 4:     0000 0000 0001 0000
                               ------------------------------
resultado OR decenas << 4    = 0000 0000 0001 0000


          resultado:           0000 0000 0001 0000
          OR unidades:         0000 0000 0000 0010
                               ------------------------------
resultado OR unidades        = 0000 0000 0001 0010

resultado = 0000 0000 0001 0010 [BCD]
*/

/*
int main(void) {
    uint16_t suma = sumar(0x12, 0x02);
    printf("0x%03X\n",suma);
    return 0;
}
*/

/*
2. Se tiene un tipo vector_t definido sobre una estructura. La misma tiene dos miembros: v de tipo
float * y n de tipo size_t, donde v es un vector dinámico de flotantes de longitud n:
    - Declarar la estructura struct vector,
    - Redefinirla como vector_t,
    - Implementar la función:
        vector_t *vector_clonar(const vector_t *vector);

que realiza una copia completa de vector en memoria nueva y la devuelva.
*/
struct vector {
    float* v;
    size_t n;
};

typedef struct vector vector_t;

vector_t* vector_clonar(const vector_t* vector) {
    if (!vector) {
        return NULL;
    }
    
    vector_t* clonado = malloc(sizeof(vector_t));
    if (!clonado) {
        return NULL;
    }

    clonado->n = vector->n;
    clonado->v = NULL;

    if (clonado->n == 0) {
        return clonado;
    }

    clonado->v = malloc(sizeof(float) * clonado->n);
    if (clonado->v == NULL) {
        free(clonado);
        return NULL;
    }

    for (size_t i = 0; i < clonado->n; i++) {
        clonado->v[i] = vector->v[i];
    }
    return clonado;
}

/*
Explicación:
Primero creo la estructura tal como lo pide la consigna.
Despues la redefino con el alias vector_t.
Dentro de la función, verifico que 'vector' sea válido, si no lo es, devuelve el puntero NULL.
Luego, reservo la memoria suficiente para almacenar un vector_t en el heap y controlo que se pueda
reservar, sino devulve NULL.
Como 'clonado' y 'vector' son punteros, uso la notacion '->' para acceder a su contenido. Si fuese un
struct, uso '.'.
Si la longitud de clonado es 0, lo devuelvo. En caso contrario, reservo en la variable 'v' dentro de 
'clonado' la cantidad de memoria junta para alojar una cantidad 'n' de floats.
Si no se puede reservar, libero la memoria ocupada por 'clonado' y devuelvo el puntero nulo.
Finalmente, copio elemento a elemento lo que hay en la variable 'v' de 'vector' y lo inserto
en la misma posición de la variable 'v' de 'clonado' y una vez se termine de clonar, devuelvo
el clon.
*/

/*
int main(void){
    float arreglo_floats[2] = {10.2f,20.1f};
    vector_t ejemplo;
    ejemplo.v = arreglo_floats;
    ejemplo.n = 2;
    vector_t* copy = vector_clonar(&ejemplo);
    printf("n: %zu\n",copy->n);
    for (size_t i = 0; i < copy->n;i++) {
        printf("%f\n",copy->v[i]);
    }
    free(copy->v);
    free(copy);
    return 0;
}
*/

/*
Implementar una función char *leer_linea(); que lea una línea desde stdin (hasta el '\n'). Debe
devolver la cadena leída o NULL en caso de error.
*/
char *leer_linea(void) {
    size_t len = 0;
    size_t capacidad = 12;
    char* linea = malloc(capacidad);
    if (!linea) {
        return NULL;
    }
    int c;
    for (;;) {
        c = getchar();
        if (len + 1 >= capacidad) {
            capacidad = capacidad * 2;
            char* linea_realocada = realloc(linea,capacidad);
            if (!linea_realocada) {
                free(linea);
                return NULL;
            }
            linea = linea_realocada;
        }
        if (c == '\n') {
            break;
        }
        if (c == EOF) {
            if (len == 0) {
                free(linea);
                return NULL;
            }
            break;
        }
        linea[len] = (char) c;
        len += 1;
    }
    linea[len] = '\0';
    return linea;
}

/*
Explicacion:
Creo dos variables. Una con la longitud y otra con la capacidad.
Reservo la cantidad de memoria de 'capacidad'. Si fallo la asignacion de memoria, devuelve el
puntero nulo.
Luego creo la variable 'c' donde se van a lamacenar los caracteres, hago un while true [for(;;)] y
le pido al usuairo una entrada por la standard input, si la cantidad de caracteres ingresada por el
usuario es mayor a la memoria reservada, agrandop la capacidad de memoria al doble.
¿por que hago un ciclo y no simplemente 'c = getchar()'? porque getchar solo captura un solo caracter.
de la manera que lo estoy haciendo, si ponés 'hola', gracias al for(;;), registra 'h' en la primera
iteracion, 'o' en la segunda y así hasta llegar a '\n' (el ENTER sin incluir). Si falla el ingreso (EOF),
y no se tipeo nada, libera la memoria y debuelve el puntero nulo, si se llegó a ecribirf algo, solo
sale del ciclo. Despues convierte c a char (proque la funcion getchar() devuelve int). Luego incrementa
en 1 la longitud.
Por último, en la ultima posicion inserta un '\0' para finalizar la cadena y la devuelve.
*/

int main(void) {
    char* line = leer_linea();
    if (!line) {
        printf("Error.\n");
        return 1;
    }
    printf("%s\n",line);
    free(line);
    return 0;
}
