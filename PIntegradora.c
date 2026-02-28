#include <stdio.h>
#include <string.h>

#define PARCIALES 3
#define MATERIAS 4
#define MAX_ALUMNOS 50
#define APROBACION 6.0

int main()
{
    int numAlumnos;
    int opcion;

    printf("Ingrese la cantidad de alumnos (max %d): ", MAX_ALUMNOS);
    scanf("%d", &numAlumnos);

    while (numAlumnos <= 0 || numAlumnos > MAX_ALUMNOS)
    {
        printf("Cantidad invalida. Ingrese nuevamente: ");
        scanf("%d", &numAlumnos);
    }

    // Arreglo tridimensional
    float calificaciones[PARCIALES][MATERIAS][MAX_ALUMNOS] = {0};

    // Arreglos auxiliares
    char nombres[MAX_ALUMNOS][50];
    char materias[MATERIAS][30];
    char estatus[MAX_ALUMNOS];

    int p, m, a;

    do
    {
        printf("\n========= MENU =========\n");
        printf("1. Capturar nombres de alumnos\n");
        printf("2. Capturar nombres de materias\n");
        printf("3. Capturar calificaciones\n");
        printf("4. Mostrar tabla\n");
        printf("5. Modificar calificacion\n");
        printf("6. Calcular promedios\n");
        printf("7. Maximo y minimo por parcial\n");
        printf("0. Salir\n");
        printf("Seleccione opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            for (a = 0; a < numAlumnos; a++)
            {
                printf("Nombre del alumno %d: ", a + 1);
                scanf("%s", nombres[a]);
            }
            break;

        case 2:
            for (m = 0; m < MATERIAS; m++)
            {
                printf("Nombre de la materia %d: ", m + 1);
                scanf("%s", materias[m]);
            }
            break;

        case 3:
            for (p = 0; p < PARCIALES; p++)
            {
                for (m = 0; m < MATERIAS; m++)
                {
                    for (a = 0; a < numAlumnos; a++)
                    {
                        do
                        {
                            printf("Parcial %d - %s - %s: ",
                                   p + 1, materias[m], nombres[a]);
                            scanf("%f", &calificaciones[p][m][a]);

                            if (calificaciones[p][m][a] < 0.0 || calificaciones[p][m][a] > 10.0)
                                printf("Calificacion invalida (0-10)\n");

                        } while (calificaciones[p][m][a] < 0.0 || calificaciones[p][m][a] > 10.0);
                    }
                }
            }
            break;

        case 4:
            for (p = 0; p < PARCIALES; p++)
            {
                printf("\n====== PARCIAL %d ======\n", p + 1);

                for (m = 0; m < MATERIAS; m++)
                {
                    printf("\nMateria: %s\n", materias[m]);
                    for (a = 0; a < numAlumnos; a++)
                    {
                        printf("%s: %.2f\n",
                               nombres[a],
                               calificaciones[p][m][a]);
                    }
                }
            }
            break;

        case 5:
        {
            printf("Ingrese parcial (1-3): ");
            scanf("%d", &p);
            printf("Ingrese materia (1-4): ");
            scanf("%d", &m);
            printf("Ingrese alumno (1-%d): ", numAlumnos);
            scanf("%d", &a);

            while (p < 1 || p > PARCIALES ||
                   m < 1 || m > MATERIAS ||
                   a < 1 || a > numAlumnos)
            {
                printf("Indices fuera de rango. Intente nuevamente.\n");
                printf("Parcial (1-3): ");
                scanf("%d", &p);
                printf("Materia (1-4): ");
                scanf("%d", &m);
                printf("Alumno (1-%d): ", numAlumnos);
                scanf("%d", &a);
            }

            do
            {
                printf("Nueva calificacion: ");
                scanf("%f", &calificaciones[p - 1][m - 1][a - 1]);

            } while (calificaciones[p - 1][m - 1][a - 1] < 0.0 ||
                     calificaciones[p - 1][m - 1][a - 1] > 10.0);

            break;
        }

        case 6:
        {
            float promedioAlumno;
            float promedioMateria;

            for (a = 0; a < numAlumnos; a++)
            {
                float suma = 0;
                int contador = 0;

                for (p = 0; p < PARCIALES; p++)
                    for (m = 0; m < MATERIAS; m++)
                    {
                        suma += calificaciones[p][m][a];
                        contador++;
                    }

                promedioAlumno = suma / contador;

                if (promedioAlumno >= APROBACION)
                    estatus[a] = 'A';
                else
                    estatus[a] = 'R';

                printf("Alumno %s Promedio: %.2f Estatus: %c\n",
                       nombres[a], promedioAlumno, estatus[a]);
            }

            for (p = 0; p < PARCIALES; p++)
            {
                for (m = 0; m < MATERIAS; m++)
                {
                    float suma = 0;

                    for (a = 0; a < numAlumnos; a++)
                        suma += calificaciones[p][m][a];

                    promedioMateria = suma / numAlumnos;

                    printf("Parcial %d Materia %s Promedio: %.2f\n",
                           p + 1, materias[m], promedioMateria);
                }
            }
            break;
        }

        case 7:
            for (p = 0; p < PARCIALES; p++)
            {
                float max = calificaciones[p][0][0];
                float min = calificaciones[p][0][0];
                int maxM = 0, maxA = 0, minM = 0, minA = 0;

                for (m = 0; m < MATERIAS; m++)
                    for (a = 0; a < numAlumnos; a++)
                    {
                        if (calificaciones[p][m][a] > max)
                        {
                            max = calificaciones[p][m][a];
                            maxM = m;
                            maxA = a;
                        }

                        if (calificaciones[p][m][a] < min)
                        {
                            min = calificaciones[p][m][a];
                            minM = m;
                            minA = a;
                        }
                    }

                printf("\nParcial %d\n", p + 1);
                printf("Maximo: %.2f Materia: %s Alumno: %s\n",
                       max, materias[maxM], nombres[maxA]);
                printf("Minimo: %.2f Materia: %s Alumno: %s\n",
                       min, materias[minM], nombres[minA]);
            }
            break;
        }

    } while (opcion != 0);

    return 0;
}