#include <stdio.h>
#include <string.h>

#define NUM_ALUMNOS 5

void main()
{
    // Definición de variables
    char nombres[NUM_ALUMNOS][50];
    int grupos[NUM_ALUMNOS];
    int edades[NUM_ALUMNOS];
    float calificaciones[NUM_ALUMNOS];

    float max_calificacion, min_calificacion;

    printf("||| Registro de Alumnos |||\n");

    // Captura de datos
    for (int i = 0; i < NUM_ALUMNOS; i++)
    {
        printf("\nAlumno %d\n", i + 1);

        printf("Nombre del alumno: ");
        scanf(" %[^\n]", nombres[i]);

        printf("Grupo: ");
        scanf("%d", &grupos[i]);

        printf("Edad: ");
        scanf("%d", &edades[i]);

        printf("Calificacion: ");
        scanf("%f", &calificaciones[i]);

        // Inicializar max y min
        if (i == 0)
        {
            max_calificacion = calificaciones[i];
            min_calificacion = calificaciones[i];
        }
        else
        {
            if (calificaciones[i] > max_calificacion)
                max_calificacion = calificaciones[i];

            if (calificaciones[i] < min_calificacion)
                min_calificacion = calificaciones[i];
        }
    }

    // Ordenar calificaciones de mayor a menor
    for (int i = 0; i < NUM_ALUMNOS - 1; i++)
    {
        for (int j = i + 1; j < NUM_ALUMNOS; j++)
        {
            if (calificaciones[i] < calificaciones[j])
            {
                float tempCal = calificaciones[i];
                calificaciones[i] = calificaciones[j];
                calificaciones[j] = tempCal;

                char tempNombre[50];
                strcpy(tempNombre, nombres[i]);
                strcpy(nombres[i], nombres[j]);
                strcpy(nombres[j], tempNombre);

                int tempGrupo = grupos[i];
                grupos[i] = grupos[j];
                grupos[j] = tempGrupo;

                int tempEdad = edades[i];
                edades[i] = edades[j];
                edades[j] = tempEdad;
            }
        }
    }

    printf("\n--- Lista ordenada por calificacion (Mayor a menor) ---\n\n");

    for (int i = 0; i < NUM_ALUMNOS; i++)
    {
        printf("Alumno: %s | Calificacion: %.2f | Grupo: %d\n",
               nombres[i], calificaciones[i], grupos[i]);
    }

    printf("\nEl alumno con mayor calificacion es %s\n", nombres[0]);
    printf("El alumno mas bajo de calificacion es %s\n", nombres[NUM_ALUMNOS - 1]);

    // Menu para ordenar por edad
    int opcion;
    printf("\nMENU\n");
    printf("1. Ordenar por edad (menor a mayor)\n");
    printf("2. Ordenar por edad (mayor a menor)\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);

    for (int i = 0; i < NUM_ALUMNOS - 1; i++)
    {
        for (int j = i + 1; j < NUM_ALUMNOS; j++)
        {
            int condicion = 0;

            if (opcion == 1 && edades[i] > edades[j])
                condicion = 1;

            if (opcion == 2 && edades[i] < edades[j])
                condicion = 1;

            if (condicion)
            {
                int tempEdad = edades[i];
                edades[i] = edades[j];
                edades[j] = tempEdad;

                char tempNombre[50];
                strcpy(tempNombre, nombres[i]);
                strcpy(nombres[i], nombres[j]);
                strcpy(nombres[j], tempNombre);

                int tempGrupo = grupos[i];
                grupos[i] = grupos[j];
                grupos[j] = tempGrupo;

                float tempCal = calificaciones[i];
                calificaciones[i] = calificaciones[j];
                calificaciones[j] = tempCal;
            }
        }
    }

    printf("\n--- Lista ordenada por edad ---\n\n");

    for (int i = 0; i < NUM_ALUMNOS; i++)
    {
        printf("Alumno: %s | Edad: %d | Grupo: %d | Calificacion: %.2f\n",
               nombres[i], edades[i], grupos[i], calificaciones[i]);
    }
}