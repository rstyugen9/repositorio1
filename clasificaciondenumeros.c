#include <stdio.h>

int main() {
    int x1, x2, x3;
    float temp;

    // Validación de x1
    do {
        printf("Ingresa el primer numero entero: ");
        if (scanf("%f", &temp) != 1) {
            printf("Entrada invalida.\n");
            while(getchar() != '\n'); // limpiar buffer
            continue;
        }

        if (temp != (int)temp) {
            printf("No es un numero entero. Intenta de nuevo.\n");
        } else {
            x1 = (int)temp;
            break;
        }

    } while (1);

    // Validación de x2
    do {
        printf("Ingresa el segundo numero entero: ");
        if (scanf("%f", &temp) != 1) {
            printf("Entrada invalida.\n");
            while(getchar() != '\n');
            continue;
        }

        if (temp != (int)temp) {
            printf("No es un numero entero. Intenta de nuevo.\n");
        } else {
            x2 = (int)temp;
            break;
        }

    } while (1);

    // Validación de x3
    do {
        printf("Ingresa el tercer numero entero: ");
        if (scanf("%f", &temp) != 1) {
            printf("Entrada invalida.\n");
            while(getchar() != '\n');
            continue;
        }

        if (temp != (int)temp) {
            printf("No es un numero entero. Intenta de nuevo.\n");
        } else {
            x3 = (int)temp;
            break;
        }

    } while (1);

    // Módulo de cada número (ejemplo módulo 2)
    printf("\n--- MODULO DE CADA NUMERO (%%2) ---\n");
    printf("x1 %% 2 = %d\n", x1 % 2);
    printf("x2 %% 2 = %d\n", x2 % 2);
    printf("x3 %% 2 = %d\n", x3 % 2);

    printf("\n--- COMPARACIONES ---\n");

    // Si son iguales
    if (x1 == x2 && x2 == x3) {
        printf("Los tres numeros son iguales\n");
    } else {
        printf("Los tres numeros NO son iguales\n");
    }

    // Si x1 es mayor a x2
    if (x1 > x2) {
        printf("x1 es mayor que x2\n");
    }

    // Si x1 es mayor a x3
    if (x1 > x3) {
        printf("x1 es mayor que x3\n");
    }

    // Si x2 es igual a x3
    if (x2 == x3) {
        printf("x2 es igual a x3\n");
    }

    // Si x2 es mayor a x1
    if (x2 > x1) {
        printf("x2 es mayor que x1\n");
    }

    return 0;
}