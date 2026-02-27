#include <stdio.h>

#define PARCIALES 3

void main()
{
    int numAlumnos;

    printf("Ingrese la cantidad de alumnos: ");
    scanf("%d", &numAlumnos);

    float matriz[PARCIALES][numAlumnos];
    float sumaFila[PARCIALES] = {0};
    float sumaColumna[numAlumnos];
    float promedioAlumno[numAlumnos];
    float promedioParcial[PARCIALES];

    char nombre[numAlumnos][50];
    char grupo[numAlumnos][20];

    // Captura de datos
    for (int j = 0; j < numAlumnos; j++)
    {
        printf("\nAlumno %d\n", j + 1);

        printf("Nombre: ");
        scanf("%s", nombre[j]);

        printf("Grupo: ");
        scanf("%s", grupo[j]);

        for (int i = 0; i < PARCIALES; i++)
        {
            printf("Ingrese calificacion Parcial %d: ", i + 1);
            scanf("%f", &matriz[i][j]);
        }
    }

    // Calculo de sumas
    for (int i = 0; i < PARCIALES; i++)
    {
        for (int j = 0; j < numAlumnos; j++)
        {
            sumaFila[i] += matriz[i][j];
        }
        promedioParcial[i] = sumaFila[i] / numAlumnos;
    }

    for (int j = 0; j < numAlumnos; j++)
    {
        sumaColumna[j] = 0;
        for (int i = 0; i < PARCIALES; i++)
        {
            sumaColumna[j] += matriz[i][j];
        }
        promedioAlumno[j] = sumaColumna[j] / PARCIALES;
    }

    // Mostrar tabla
    printf("\n\n---------------- TABLA DE CALIFICACIONES ----------------\n\n");

    printf("\t\t");
    for (int j = 0; j < numAlumnos; j++)
    {
        printf("Alumno %d\t", j + 1);
    }
    printf("\n");

    for (int i = 0; i < PARCIALES; i++)
    {
        printf("Parcial %d\t", i + 1);
        for (int j = 0; j < numAlumnos; j++)
        {
            printf("%.2f\t\t", matriz[i][j]);
        }
        printf("\n");
    }

    printf("\nPromedio Alumno\t");
    for (int j = 0; j < numAlumnos; j++)
    {
        printf("%.2f\t\t", promedioAlumno[j]);
    }

    printf("\n\nPromedio Parcial\n");
    for (int i = 0; i < PARCIALES; i++)
    {
        printf("Parcial %d: %.2f\n", i + 1, promedioParcial[i]);
    }
}