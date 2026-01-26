#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Algoritmos y Programación I (95.11) – Curso Santisi – 2do parcialito – 20/10/2023
Resolver los siguientes problemas en forma clara y legible en código ISO-C99.
1. Implementar una función bool misma_cantidad(uint32_t n); que devuelva true si la cantidad de bits
prendidos en las posiciones impares de n es la misma que la de bits prendidos en las posiciones pares.
Por ejemplo, misma_cantidad(0100 1011) -> true porque están prendidos los bits 0, 1, 3 y 6; y dos de
ellos están en posiciones pares y dos en impares.
*/
bool misma_cantidad(uint32_t n) {
    int prendidos_pares = 0;
    int prendidos_impares = 0;
    int i = 0;
    while (n > 0) {
        uint32_t bit = n & 0x1;
        if (i % 2 == 0 && bit != 0) {
            prendidos_pares++;
        } 
        if (i % 2 != 0 && bit != 0) {
            prendidos_impares++;
        }
        i++;
        n >>= 1;
    }
    if (prendidos_pares == prendidos_impares) {
        return true;
    }
    return false;
}
/*
int main(void) {
    uint32_t n_ejemplo = 0x4B; // 0100 1011
    bool cantidad_igual = misma_cantidad(n_ejemplo);
    if (cantidad_igual) {
        printf("Misma Cantidad\n");
    } else {
        printf("Distinta Cantidad\n");
    }
    return 0;
}
*/

/*
Explicacion:
Primero, iniciamos tres variables enteras en cero: 'prendidos_pares', 'prendidos_impares' e 'i'. Vamos
a usar un ciclo while para recorrer el numero y mientras este sea mayor a cero, se va a ejecutar. En
el cuerpo del ciclo vamos a guardar el bit que estamos analizando usando una operacion AND. En el
caso del bit en la posicion cero, se tiene que:

                                 0100 1011
                                &0000 0001 -> 0x1
                                -----------
                                 0000 0001

Si el indice 'i' dividido 2 tiene resto cero (es par) y el bit es distinto de 0 (distinto de apagado),
sumamos 1 a 'prendidos_pares'. En cambio, si 'i' dividido 2 tiene diferente de resto cero (es impar) y
el bit es distinto de 0, sumamos 1 a 'prendidos_impares'. Luego, sumamos 1 al indice y desplazamos a
la derecha 1 bit de 'n'. Despues seguimos operando con el numero n >> 1:

                                 0010 0101
                                &0000 0001
                                -----------
                                 0000 0001

Así, hasta que el numero sea 0000 0000.
Una vez recorrido todo el numero, vemos si la cantidad de prendidos en posiciones pares es igual que
en impares. Si lo es, devolvemos true, sino devolvemos false.
*/

/*
2. Se quiere implementar una función char *join(char *cadenas[], size_t n, char separador); que
reciba un arreglo de n cadenas de caracteres y devuelva una única cadena que contenga a todas ellas con el
separador intercalado.
Por ejemplo, join({"Hola", "que", "tal"}, 3, ' ') -> "Hola que tal".
*/
char* join(char *cadenas[], size_t n, char separador) {
    if (!cadenas || n == 0) {
        printf("Argumento/s invalido/s\n");
        return NULL;
    }
    size_t largo_cadena = 0;
    for (size_t i = 0; i < n; i++) {
        largo_cadena += strlen(cadenas[i]);
        largo_cadena++;
    }
    char* cadena_unida = malloc(largo_cadena);
    if (!cadena_unida) {
        printf("No se pudo reservar memoria para alojar cadena\n");
        return NULL;
    }
    int k = 0;
    for (size_t palabra = 0; palabra < n; palabra++) {
        for (size_t posicion = 0; posicion < strlen(cadenas[palabra]); posicion++) {
            cadena_unida[k] = cadenas[palabra][posicion];
            k++;
        }
        if (palabra != n-1) {
        cadena_unida[k] = separador;
        k++;
        }
    }
    cadena_unida[k] = '\0';
    return cadena_unida;
}

int main(void) {
    char* cadena[] = {"hola","como","estas"};
    char* unida = join(cadena,3,'-');
    if (!unida) {
        return 1;
    }
    printf("%s\n",unida);
    free(unida);
    return 0;
}

/*
Explicacion:
Verificamos que la cadena no sea NULL o que 'n' sea 0. En ese caso, imprimimos un mensaje descriptivo
y devolvemos NULL. Luego, iniciamos en cero una variable que va a contener el largo de la cadena sepa-
rada. Recorremos cada elemento de 'cadenas', sumando la cantidad de letras de cada parabra a
'largo_cadena' y, sumando tambien 1 para cada separador y para el '\0' del final. Despues, reservamos
exactamente esa cantidad de memoria para almacenar la cadena en el heap. Si no se puede reservar, vamos
a imprimir un mensaje descritivo y devolvemos el puntero nulo. Despues, vamos a iniciar una variable
de tipo int que vamos a llamar 'k' en cero. Esta va a actuar como indice para escribir la cadena en
'cadena_unida'. Luego, recorremos 'cadenas', accediendo primero a su primer palabra. Teniendo a
disposicion esta palabra, vamos a almacenar en la posicion 'k' de 'cadena_unida' lo que esta en
'cadenas[palabra][posicion]', que al principio va a ser lo mismo que 'cadenas[0][0]'. Despues se va
incrementado 'posicion' y 'k' hasta llegar al final de la palabra. Cuando llegamos al final, nos
fijamos que no estamos en la ultima palabra. Si no estamos en la ultima palabra, agregamos el separador
y sumamos 1 a 'k'. Este ciclo se repite hasta recorrer todo el arreglo. Una vez recorrido todo el
arreglo, añadimos en la posicion 'k' el caracter '\0' para indicar el fin de la cadena y la devolvemos.
*/

/*
3. Se tiene una estructura que representa a una carta de baraja española. La misma contiene el valor de la carta,
que es un número entre 1 y 12, y el palo, que es un enumerativo con las etiquetas ORO, ESPADA, BASTO y COPA.
- Declarar el enumerativo enum palo y la estructura struct carta.
- Redefinir struct carta como carta_t.
- Teniendo ya implementada una función carta_t *sacar_carta_del_mazo(); que al ser llamada devuelve
una nueva carta implementar la función:
carta_t **tirar_reyes(size_t *n);
que llame a sacar_carta_del_mazo() la cantidad de veces que haga falta hasta obtener un rey (valor
12). Debe devolver un arreglo con cada una de las cartas sacadas hasta el momento (incluyendo el rey).
Se debe devolver, además, la cantidad de cartas sacadas en n.
¡Suerte! :)
*/
enum palo {
    ORO,
    ESPADA,
    BASTO,
    COPA
};

struct carta {
    int numero;
    enum palo p;
};

typedef struct carta carta_t;

carta_t *sacar_carta_del_mazo(); // Asumimos que existe

carta_t** tirar_reyes(size_t* n) {
    if (!n) {
        printf("El puntero es nulo\n");
        return NULL;
    }
    size_t cantidad_cartas_sacadas = 0;
    size_t capacidad = 4;
    carta_t** arreglo_sacadas = malloc(capacidad * sizeof(carta_t*));
    if (!arreglo_sacadas) {
        printf("No se pudo reservar mamoria\n");
        return NULL;
    }
    for (;;) {
        if (cantidad_cartas_sacadas >= capacidad) {
            capacidad *= 2;
            carta_t** realocado = realloc(arreglo_sacadas,capacidad * sizeof(carta_t*));
            if (!realocado) {
                for (size_t i = 0; i < cantidad_cartas_sacadas; i++) {
                    free(arreglo_sacadas[i]);
                }
                free(arreglo_sacadas);
                printf("No se pudo reservar mamoria\n");
                return NULL;
            }
            arreglo_sacadas = realocado;
        }
        carta_t* carta = sacar_carta_del_mazo();
        arreglo_sacadas[cantidad_cartas_sacadas] = carta;
        cantidad_cartas_sacadas += 1;
        if (carta->numero == 12) {
            break;
        }
    }
    *n = cantidad_cartas_sacadas;
    return arreglo_sacadas;
}

/*
Explicacion:
Primero, definimos el enumerativo para los palos y la estructura para las cartas. Luego, la redefinimos.
Los enumerativos sirven para enmascarar constates enteras como palabras. En este caso, ORO=0,
ESPADA=1,...
Ya metiendonos de lleno en la funcion, verificamos que el puntero 'n' no sea NULL. Si lo es, imprimimos
un mensaje descriptivo informandolo y devolvemos el puntero nulo. Luego, iniciamos en cero una variable
de tipo size_t donde se almacenara la cantidad de cartas sacadas y otra variable con la cantidad de
cartas que el arreglo va a poder almacenar. Despues, vamos a reservar memoria para almacenar una
cantidad 'capacidad' de punteros a 'cartas_t' en la variable 'arreglo_sacadas' de tipo cartas_t**.
Si no se puede reservar esta memoria, imprimimos un mensaje descriptivo y devolvemos NULL.
Duespues, hacemos un bucle infinito, en el cual lo primero que hacemos es verificar que haya
memoria para almacenar una carta en 'arreglo_sacadas'. Si no queda mas memoria, duplicamos 'capacidad'
y ampliamos la memoria del arreglo usando la funcion 'realloc()'. Si no se puede reservar esta memoria
adicional,  recorremos el arreglo para liberar la memoria que ocupan cada una de las cartas en el
arreglo, liberamos la memoria que ocupa el arreglo en sí, imprimimos un mensaje informativo y
devolvemos NULL.
Luego, guardamos en una variable 'carta' lo que resulta de llamar a la función 'sacar_carta_del_mazo()'.
La variable 'cantidad_cartas_sacadas' va a hacer las veces de indice, de manera tal que vamos a
insertar en la posicion 'cantidad_cartas_sacadas' del arreglo a 'carta'. Ahora incrementamos en 1 a
esta variable y, si el numero de esta carta es 12, salimos del ciclo. Finalmente, almacenamos en 'n'
la cantidad de cartas que sacamos y devolvemos el arreglo.
*/
