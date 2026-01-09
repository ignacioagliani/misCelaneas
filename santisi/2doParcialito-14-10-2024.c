#include <stdint.h>
#include <stdio.h>
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
                                x & 0x0F = 0000 0010
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
cententenas << 8 = 0000 0000 0000 0000 (desplazas 8 bits a la derecha)
decenas << 4     = 0000 0000 0001 0000 (desplazas 4 bits a la derecha)
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

int main(void) {
    uint16_t suma = sumar(0x12, 0x02);
    printf("0x%03X\n",suma);
    return 0;
}
