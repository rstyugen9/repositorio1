#include <stdio.h>

void main()
{
    int numero, iteraciones;
    int condiciones = 0;

    while (condiciones != 2)
    {
        printf("\n::Generador de Tablas de Multiplicar::\n");

        printf("Ingrese un número entero PAR:\n");
        if (scanf("%d", &numero) != 1)
        {
            printf("El numero es fraccionario o invalido, favor de volver a ingresarlo\n");
            while (getchar() != '\n'); // limpiar buffer
            continue;
        }

        if (numero % 2 == 0)
        {
            printf("El numero %d es PAR y es entero\n", numero);
            condiciones++;
        }
        else
        {
            printf("El numero no es PAR, favor de volver a ingresarlo\n");
        }

        printf("\nIngrese la cantidad de iteraciones (entero PAR):\n");
        if (scanf("%d", &iteraciones) != 1)
        {
            printf("La cifra es fraccionaria o invalida, favor de volver a ingresarla\n");
            while (getchar() != '\n');
            condiciones = 0;
            continue;
        }

        if (iteraciones % 2 == 0)
        {
            printf("La cifra de iteraciones %d es PAR y entero\n", iteraciones);
            condiciones++;
        }
        else
        {
            printf("La cifra no es PAR, favor de volver a ingresarla\n");
        }

        if (condiciones < 2)
        {
            condiciones = 0;
            numero = 0;
            iteraciones = 0;
        }
    }

    // Cabecera de la tabla
    printf("\nTabla de multiplicar del %d\n", numero);
    printf("-----------------------------\n");

    for (int i = 1; i <= iteraciones; i++)
    {
        int resultado = numero * i;
        printf("%2d x %2d = %3d\n", numero, i, resultado);

        if (i % 10 == 0)
        {
            printf("----------- BLOQUE 10 -----------\n");
        }
    }

    printf("-----------------------------\n");

    return 0;
}