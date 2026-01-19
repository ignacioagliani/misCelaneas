#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "3erParcialito-26-05-2025.h"
/*
Algoritmos y Programación (TA130) – Curso Santisi – 3er parcialito –
26/05/2025
Resolver los siguientes problemas en forma clara y legible en código ISO-C99.
1. Se quiere implementar un sistema de turnos en un banco. Para esto se propone
un TDA que registre cada cliente que ingrese y que permita llamar al primero
que llegó.
a. Declarar la estructura que encapsula el TDA. Explicar qué representa
cada miembro y documentar la invariante de representación.
b. Implementar la primitiva char *turnos_proximo(turnos_t *t); que
devuelva el próximo cliente esperando en el sistema de turnos t.
c. Implementar la primitiva bool turnos_nuevo(turnos_t *t, const
char *cliente); que registre la llegada de un nuevo cliente en el
sistema.
turnos_t *t = turnos_crear();
turnos_nuevo(t, "Juan");
turnos_nuevo(t, "María");
turnos_nuevo(t, "Carlos");
turnos_proximo(t); // Juan
turnos_proximo(t); // María
turnos_nuevo(t, "Marta");
turnos_proximo(t); // Carlos
*/

struct nodo {
    char* cliente;
    struct nodo* siguiente;
};

typedef struct nodo nodo_t;

struct turnos {
    nodo_t* primero;
    nodo_t* ultimo;
    size_t cantidad;
};

turnos_t* turnos_crear(void) {
    turnos_t* nuevo_turno = malloc(sizeof(turnos_t));
    if (!nuevo_turno) {
        printf("No se pudo reservar memoria para crear un turno\n");
        return NULL;
    }
    nuevo_turno->primero = NULL;
    nuevo_turno->ultimo = NULL;
    nuevo_turno->cantidad = 0;
    return nuevo_turno;
}

char* turnos_proximo(turnos_t* t) {
    if (!t || t->cantidad == 0) {
        printf("No hay turnos\n");
        return NULL;
    }
    nodo_t* proximo = t->primero;
    if (!proximo) {
        printf("Turno invalido\n");
        return NULL;
    }
    char* proximo_turno = proximo->cliente;
    t->primero = proximo->siguiente;
    t->cantidad -= 1;
    if (t->cantidad == 0) {
        t->ultimo = NULL;
    }
    free(proximo);
    return proximo_turno;
}

bool turnos_nuevo(turnos_t *t, const char *cliente) {
    if (!t || !cliente) {
        printf("Datos Invalidos\n");
        return false;
    }
    nodo_t* turno_nuevo = malloc(sizeof(nodo_t));
    if (!turno_nuevo) {
        printf("No se puede reservar memoria para un nuevo turno\n");
        return false;
    }
    turno_nuevo->cliente = (char*) cliente;
    turno_nuevo->siguiente = NULL;
    if (t->cantidad == 0) {
        t->primero = turno_nuevo;
        t->ultimo = turno_nuevo;
    } else {
        t->ultimo->siguiente = turno_nuevo;
        t->ultimo = turno_nuevo;
    }
    t->cantidad += 1;
    return true;
}
/*
int main(void) {
    turnos_t *t = turnos_crear();
    turnos_nuevo(t, "Juan");
    turnos_nuevo(t, "María");
    turnos_nuevo(t, "Carlos");
    printf("%s\n",turnos_proximo(t)); // Juan
    printf("%s\n",turnos_proximo(t)); // María
    turnos_nuevo(t, "Marta");
    printf("%s\n",turnos_proximo(t)); // Carlos
}
*/

/*
Explicación:
Imaginate que vas al banco Rio a hacer un tramite. Querés abrir una cuenta bancaria para tu flamante empresa, pero
tenés adelante a Juan, María y Carlos ¿Qué tenés que hacer? Una cola! Bárbaro, vamos a implementar una cola enlazada
para este problema. Usemos la intuición: en una cola, llega primero el amigo Juan, despues María, despues Charly y
último vos. Primero atienden a Juan, despues a María, despues a Carlos y último a vos. Asi funcionan la colas. Acá
y en la China.
Primero, definimos un nodo en una estructura. Los nodos van a ser los elementos de nuestra cola. Cada nodo contiene
el nombre del cliente y la direccion de memoria del siguiente cliente en ser atendido (otro nodo). En este caso,
cada persona es un nodo: Juan,María, Carlos y vos.
Ahora definimos la estructura de turnos, la cual va a tener como elementos la primer persona en ser atendida, la
última y la cantidad total de personas.

¿Que es una invariante de representacion y cuales son en este caso?
Las invariantes de representacion son las condiciones que siempre son verdaderas en el TDA. En este caso son:
    - 'primero': primera persona en la cola. Si 'cantidad' == 0, 'primero' == NULL. Si 'cantidad' > 0, 'primero' != 
       NULL
    - 'ultimo': ultima persona en la cola. Si 'cantidad' == 0, 'ultimo' == NULL. Si 'cantidad' > 0, 'ultimo' != 
       NULL
    - 'cantidad': cantidad de personas en la cola.

El archivo '.h':
Este archivo almacena la interfaz de TDA. Ahí definí una constante, la cual llamé 'TURNOS_H'. Esta sirve para evitar
multiples inclusiones. Además, en ese archivo se almacenan las declaraciones de las funciones y una breve descripción
de lo que hacen.

La funnción 'turnos_crear' va a inicializar un nuevo sistema de turnos, la cual, si es exitosa, va a devolver un
turnos_t* (puntero a turnos_t) con la primer y ultima persona en NULL y la cantidad en 0. Esto lo podemos pensar
como si fuesemos al banco a la hora que abre: no hay primera ni ultima persona porque recien acaba de abrir. Si
llega a fallar, imprime un mensaje informativo y devuelve el puntero nulo.
La funcion 'turnos_proximo' nos devuelve una cadena diciendonos quien es el proximo en la cola. La función recibe
un 't', que es un puntero a un sistema de turnos. Si esa 't' es NULL (!t) o no hay clientes en la cola (t->cantidad==0),
la función imprime un mensaje informativo y devuelve NULL. Ahora, guardamos el nodo que contiene a laproxima persona
en la cola (el dato que vamos a devolver) en la variable 'proximo'. Para esto, agarramos de 't' el nodo que está
en 'primero', lo cual es razonable. Si 'proximo' es NULL, imprime un mensaje informativo y devuelve NULL. En otro
caso, guardamos el nombre del siguiente cliente en 'proximo_turno' y necesitamos actualizar nuestra cola. Para esto
hacemos que el primer cliente en la fila sea el siguiente al primero (pasa de ser Juan a ser María) y disminuimos
1 la cantidad de gente en la fila. Si la cantidad de gente en la fila es cero (en el hipotetico caso de que Juan
haya sido la única persona esperando), hacemos que la última persona en 't' sea NULL ('primero' ya es NULL, porque
si Juan era el unico elemento de la cola, gracias a la funcion 'turnos_nuevo', la variable 'siguiente' vale NULL, y
como antes hicimos t->primero = proximo->siguiente, t->primero ya vale NULL. Lo único que necesetamos hacer es que
último valga NULL, porque si no lo fijamos en NULL, 'ultimo' sigue valiendo 'Juan'.). por ultimo, liberamos la
mamoria que ocupa 'proximo', porque John ya no está en la cola, y devolvemos el nombre del primero en la cola.

Ahora vamos con la funcion 'turnos_nuevo', la cual crea turnos. Verificamos que 't' y 'cliente' no sean NULL. Si lo
son, imprimimos un mensaje y devolvemos false. En el caso de que no lo sean, reservamos memoria para un nodo en
la variable 'turno_nuevo', si no se puede reservar, imprimimos un mensaje informativo y devolvemos false. En
'turno_nuevo' vamos a tener una variable 'cliente' la cual va a almacenar el nombre del cliente y una variable
'siguiente' con un puntero al siguiente nodo. En 'cliente' vamos a castear el parametro 'const char* cliente' para
convertirlo a 'char* cliente' y lo almacenamos en 'turno_nuevo->cliente'. En 'turno_nuevo->siguiente' ponemos NULL,
porque no hay nadie después del último. Si la cantidad de gente en la cola es 0, hacemos que 'turno_nuevo' sea la
primer y última persona en la cola. En el caso de que haya más gente, hacemos que el siguiente al último sea 
'turno_nuevo' (es decir, la persona que estaba última pasa a estar anteultima) y fijamo como última persona en la cola
a 'turno_nuevo'. Por ultimo devolvemos true.
*/

/*
2. Se tiene un archivo de texto para configurar una aplicación. Cada línea del
archivo es una secuencia: "clave=valor\n".
a. Se pide escribir una función bool leer_clave_valor(FILE *f, char
*clave, char *valor); que lea de un archivo f una línea y devuelva la
clave y el valor leídos. La función debe devolver false en caso de falla.
b. Se pide escribir una función bool escribir_clave_valor(FILE *f,
const char *clave, const char *valor); que escriba en el archivo f
un par clave-valor en el formato indicado. La función debe devolver
false en caso de falla.
*/
bool leer_clave_valor(FILE *f, char *clave, char *valor) {
    if (!f || !clave || !valor) {
        printf("Error con el archivo, clave y/o valor\n");
        return false;
    }
    char linea[256];
    if (!fgets(linea,sizeof(linea),f)) {
        printf("Error al leer linea\n");
        return false;
    }
    size_t i = 0;
    char key[sizeof(linea)];
    char value[sizeof(linea)];
    while (linea[i] != '=') {
        if (linea[i] == '\0') {
            return false;
        }
        key[i] = linea[i];
        i++;
    }
    key[i] = '\0';
    i += 1;
    size_t j = 0;
    while (linea[i] != '\0') {
        if (linea[i] == '\n') {
            break;
        }
        value[j] = linea[i];
        i++;
        j++;
    }
    value[j] = '\0';
    strcpy(clave,key);
    strcpy(valor,value);
    return true;
}

bool escribir_clave_valor(FILE *f, const char *clave, const char *valor) {
    if (!f || !clave || !valor) {
        printf("Error relacionado al archivo, clave y/o valor\n");
        return false;
    }
    size_t longitud_linea = strlen(clave) + strlen(valor) + 3;
    char linea[longitud_linea];
    size_t i = 0;
    size_t j = 0;
    while (clave[j] != '\n' && clave[j] != '\0') {
        linea[i] = clave[j];
        i++;
        j++;
    }
    j = 0;
    linea[i] = '=';
    i++;
    while (valor[j] != '\n' && valor[j] != '\0') {
        linea[i] = valor[j];
        i++;
        j++;
    }
    linea[i] = '\n';
    linea[i+1] = '\0';
    int resultado = fputs(linea,f);
    if (resultado == EOF) {
        printf("Ocurrio un error al escribir la linea\n");
        return false;
    }
    return true;
}

/*
int main(void) {
    char ruta_archivo[12] = "ejemplo.txt";
    FILE* archivo = fopen(ruta_archivo,"r");
    if (!archivo) {
        return 1;
    }
    char* clave = malloc(256);
    if (!clave) {
        fclose(archivo);
        return 1;
    }
    char* valor = malloc(256);
    if (!valor) {
        free(clave);
        fclose(archivo);
        return 1;
    }
    // Primer Linea
    bool se_copio = leer_clave_valor(archivo,clave,valor);
    if (se_copio) {
        printf("Clave: %s | Valor: %s\n",clave,valor);
    }
    // Segunda Linea
    se_copio = leer_clave_valor(archivo,clave,valor);
    if (se_copio) {
        printf("Clave: %s | Valor: %s\n",clave,valor);
    }
    free(clave);
    free(valor);
    fclose(archivo);
    archivo = fopen(ruta_archivo,"a");
    if (!archivo) {
        return 1;
    }
    const char nueva_clave[] = "Clave Nueva 1";
    const char nuevo_valor[] = "Valor Nuevo 1";
    bool salio_bien = escribir_clave_valor(archivo,nueva_clave,nuevo_valor);
    fclose(archivo);
    if (!salio_bien) {
        return 1;
    }
    return 0;
}
*/

/*
Explicacion:
Función 'leer_clave_valor':
Valido que todos los parametros sean válido (distintos del puntero nulo). Si alguno es NULL, imprimo un mensaje 
descriptivo y devuelvo false. Despues de validar esto, creo un arreglo de caracteres llamado 'linea' al cual
le asigne arbitrariamente 256 caracteres. En ese arreglo se va a almacenar la linea del archivo. Si no se puede
leer la linea, ya sea porque se llegó al final u ocurrió un error, imprimo un mensaje informando el error y
devuelvo false. Después, inicializo en 0 la variable 'i' de tipo size_t, la cual nos va a servir como indice a
medida que vayamos recorriendo la linea. Además, vamos a inicializar dos arreglo de chars mas, ambos con el
tamaño de 'linea'. Uno de los arreglo va a ser para la clave 'key' y otro para el valor 'value'. Una vez hecho
esto, vamos a completar ambos arreglo con la informacion necesaria. Primeramente, voy a completar 'key'. Para
estoy voy a hacer uso de un ciclo while. Mientras el caracter en la posicion 'i' de 'linea' sea distinto de
'=', dentro del cuerpo del ciclo preguntamos si se llegó al final de la cadena, el cual se indica con el caracter
'\0'. Si esto es así, significa que no hay ningun 'valor', lo cual está mal, es un error, así que devuelvo false.
En caso contrario, voy colocando en la posición 'i' de 'key' lo que hay en la posicion 'i' de 'linea'. Una vez que
se llegó al igual '=', esto indica el fin de la clave, así que aigno en la última posicion de 'key' el caracter '\0'.
Sumamos 1 al indice para saltearnos el '=' de 'linea' y continuamos hallando el valor. Creamos un nuevo índice 'j',
el cual va a ser útil a la hora de llenar 'value'. De nuevo usamos un ciclo while, pero esta vez con la condicion de
ejecutar el cuerpo del ciclo mientras el caracter en la posicion 'i' de linea sea distinto al fin de linea '\0'.
Dentro del cuerpo del ciclo, si llegamos al caracter '\n', dejamos de iterar porque llegamos al fin del valor. En
otro caso, almacenamos en la posicion 'j' de 'value' lo que está en la posicion 'i' de 'linea'. En cada iteracion, 
aumetamos 1 'i' y 'j' (en el while anterior hay que hacer lo mismo, me olvide de aclararlo). Por último, copiamos
en los punteros que pasamos por parametro lo recolectado en 'key' y 'value' y devolvemos true.

Función 'escribir_clave_valor': validamos que no haya ocurrido un error el archivo o la clave o el valor, si alguno
de ellos es NULL, imprimo un mensaje informativo y devuelvo false. Despues de validar eso, calculo la longitud de la
linea a escribir ¿Como lo hago? Averiguo el largo de la clave y del valor y a eso le sumo tres ¿Por que 3? Porque 
ademas de almacenar los caracteres necesarios para la clave y el valor, necesito almacenar un '=', un '\n' para
el salto de linea y un '\0' para indicar el fin de la cadena. Teniendo el largo necesario de la linea a escribir,
me voy a crear un arreglito de chars de esa longitud y dos indices: 'i' para recorrer 'linea' y 'j' para recorrer
'clave' y 'valor'. Copiamos todo el contenido de clave en 'linea' usando un while. Mientras linea[i] sea distinta
a '\n' y '\0', ponemos en la posicion 'i' de 'linea' lo que está en la posición 'j' de clave. Despues incrementamos
1 'i' y 'j'. Una vez recorrida toda 'clave', reiniciamos 'j' en 0, agregamos un '=' en la posicion 'i' de linea y
aumentamos 1 'i' para pasar a la siguiente posicion. Repetimos exactamente el mismo proceso para 'valor', con la
diferencia de que terminado el ciclo 'while' agregamos en la posicion 'i' de 'linea' el caracter '\n' y en la
posición 'i+1' el caracter '\0'. Ya teniendo toda la linea armada, tratamos de insertarla en el archivo usando la
función fputs, la cual sirve para insertar lineas enteras en archivos. Si fputs devuelve End Of File, imprimimos 
un mensaje descriptivo con el error y devolvemos false. En el caso de que haya salido todo bien, devolvemos true.
*/

/*
3. Escribir un programa que se ejecute como:
./reconfigurar vieja.conf nueva.conf clave valor
que tome un archivo de configuración como el del ejercicio 2. vieja.conf y
genere con él un archivo nueva.conf actualizado. El archivo actualizado deberá
contener la misma configuración de vieja.conf pero la clave dada se debe
reemplazar por el valor nuevo. En caso de que la clave no se encuentre en el
archivo vieja.conf agregarla al final del archivo nuevo.
Se deben reutilizar las funciones del ejercicio 2.
¡Suerte! :)
*/

int main(int cantidad_argumentos, char** arreglo_argumentos) {
    if (cantidad_argumentos != 5) {
        printf("Cantidad de argumentos invalida\n");
        return 1;
    }
    char* conf_vieja = arreglo_argumentos[1];
    char* conf_nueva = arreglo_argumentos[2];
    char* clave = arreglo_argumentos[3];
    char* valor =arreglo_argumentos[4];
    FILE* archivo_conf_vieja = fopen(conf_vieja,"r");
    if (!archivo_conf_vieja) {
        printf("Problemas al abrir el archivo de configuracion vieja\n");
        return 1;
    }
    FILE* archivo_conf_nueva = fopen(conf_nueva,"w");
    if (!archivo_conf_nueva) {
        printf("Problemas al abrir el archivo de configuracion nueva\n");
        fclose(archivo_conf_vieja);
        return 1;
    }
    char clave_viejo[256];
    char valor_viejo[256];
    bool encontrado = false;
    while (leer_clave_valor(archivo_conf_vieja,clave_viejo,valor_viejo) != false) {
        if (strcmp(clave_viejo,clave) == 0) {
            if (!escribir_clave_valor(archivo_conf_nueva,clave,valor)) {
                printf("No se pudo escribir nueva configuracion\n");
                fclose(archivo_conf_nueva);
                fclose(archivo_conf_vieja);
                return 1;
            }
            encontrado = true;
        } else {
            if (!escribir_clave_valor(archivo_conf_nueva,clave_viejo,valor_viejo)) {
                printf("No se pudo escribir nueva configuracion\n");
                fclose(archivo_conf_nueva);
                fclose(archivo_conf_vieja);
                return 1;
            }
        }
    }
    if (!encontrado) {
        if (!escribir_clave_valor(archivo_conf_nueva,clave,valor)) {
                printf("No se pudo escribir nueva configuracion\n");
                fclose(archivo_conf_nueva);
                fclose(archivo_conf_vieja);
                return 1;
        }
    }
    fclose(archivo_conf_nueva);
    fclose(archivo_conf_vieja);
    return 0;    
}

/*
Aclaración 1: me parece horriblemente redactada la consigna.

Explicación (de lo que entendí):
Tenemos un archivo con una configuracion vieja, otro con una configuracion nueva, una clave y un valor. Lo que
se pide es:
    - Si la clave que le pasas cuando ejecutás el programa es igual a la del archivo de configuración vieja,
      escribís en el archivo de configuracion nueva, escribís es clave y el valor pasado por parametro.
    - Si las claves son distintas, copias lo del archivo viejo en el archivo nuevo.

Aclaración 2: para que el programa ejecute con: './reconfigurar vieja.conf nueva.conf clave valor' es necesario
compilar este programa en un archivo 'reconfigurar.c' y crear un ejecutable con nombre 'reconfigurar'. Por cuestión
de no crear archivos extra, lo hago acá mismo.

La función 'main' va a recibir dos parametros: un entero 'cantidad_argumentos' y un puntero a un arreglo de chars
'arreglo_argumentos', el cual va a contener el todos los argumentos. ¿Cuales son los argumentos?

    ./reconfigurar      vieja.conf      nueva.conf      clave       valor
    |-------------|     |---------|     |--------|      |----|      |----|
    1er argumento       2do argumento   3er argumento   4to arg.    5to. argumento

¿En qué momento se 'completan' estos parametros? Gran pregunta. La respuesta es que el sistema operativo
automaticamente las completa al ejecutar el programa.
Entoces, si la cantidad de argumentos es diferente de 5 (faltan o sobran argumentos), imprimo un mensaje descriptivo
y devuelvo 1.
Despues de checkear esto, guardo en variables el nombre del archivo con la configuracion vieja, el nombre del 
archivo con la configuracion nueva, la clave y el valor. Ahora intentamos abrir el archivo con la configuracion
vieja. Si no podemos, imprimimos un mensaje descriptivo y devolvemos 1. Luego, tratamos de abrir el archivo con
la nueva configuracion en modo escritura. Si no podemos, imprimimos un mensaje descriptivo, cerramos el archivo
con la configuracion vieja, y devolvemos 1. Ya con los archivos abiertos, creamos 2 arreglos de chars de una
longitud arbitraria: un de los arreglos es para almacenar la clave del archivo con la vieja configuracion y otro
para almacenar el valor del archivo de la vieja configuracion. A su vez, vamos a definir en false una variable de
tipo booleano. Esta es necesaria ya que, si el archivo con la configuracion vieja está vacío o no se encuentra la
clave buscada, nos va a permitir escribir 'clave' y 'valor' igualmente. Mientras el archivo 'vieja.conf' tenga
lineas para leer, comparamos el contenido de 'clave' con el de 'clave_viejo' (¿por que usamos string compare 
strcmp() y no "=="? Porque "==" compara direcciones de memoria y strcmp() cadenas). Entonces, si strcmp() == 0,
significa que las cadenas son iguales, por lo tanto, escribimos en el archivo de configuracion nueva, la clave
y el nuevo valor. Si surge un error, imprimimos un mensaje informativo, cerramos el archivo de configuracion nueva,
cerramos el archivo de configuracion vieja y delvolvemos 1. A su vez, hacemos que 'encontrado' sea true. En otro caso,
escribimos en el archivo de configuracion nueva lo mismo que en el de configuracion vieja y realizamos el mismo 
checkeo de si hubieron errores de escritura. En el caso de que 'encontrado' sea falso, escribimos 'clave' y 'valor'
en el archivo de configuracion nueva, verificando de que no hayan surgido errores de escritura. Por último, se
cierran ambos archivos y se devuelve 0.
*/
