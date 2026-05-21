#include <stdio.h>
#include <stdlib.h>

// Definición de constantes
#include <stdio.h>
#include <stdlib.h>

#define ASIGNATURAS 3

// Prototipos de funciones
void ingresarNotas(float **notas, int estudiantes);
void procesarEstudiantes(float **notas, int estudiantes);
void procesarAsignaturas(float **notas, int estudiantes);

int main() {
    int estudiantes;

    printf("=== GESTION DE CALIFICACIONES ===\n");
    printf("Ingrese el numero de estudiantes: ");
    scanf("%d", &estudiantes);

    // Asignación dinámica de memoria para la matriz [estudiantes][ASIGNATURAS]
    float **notas = (float **)malloc(estudiantes * sizeof(float *));
    for (int i = 0; i < estudiantes; i++) {
        notas[i] = (float *)malloc(ASIGNATURAS * sizeof(float));
    }

    // Llamada a las funciones principales
    ingresarNotas(notas, estudiantes);
    procesarEstudiantes(notas, estudiantes);
    procesarAsignaturas(notas, estudiantes);

    // Liberación de memoria
    for (int i = 0; i < estudiantes; i++) {
        free(notas[i]);
    }
    free(notas);

    return 0;
}

void ingresarNotas(float **notas, int estudiantes) {
    printf("\n--- REGISTRO DE NOTAS ---\n");
    for (int i = 0; i < estudiantes; i++) {
        printf("\nEstudiante %d:\n", i + 1);
        for (int j = 0; j < ASIGNATURAS; j++) {
            do {
                printf("  Nota Asignatura %d (0-10): ", j + 1);
                scanf("%f", &notas[i][j]);
                if (notas[i][j] < 0 || notas[i][j] > 10) {
                    printf("  [Error] La nota debe estar entre 0 y 10. Intente de nuevo.\n");
                }
            } while (notas[i][j] < 0 || notas[i][j] > 10);
        }
    }
}

void procesarEstudiantes(float **notas, int estudiantes) {
    printf("\n=========================================================\n");
    printf("               REPORTE POR ESTUDIANTE\n");
    printf("=========================================================\n");
    printf("Estudiante\tPromedio\tNota Max\tNota Min\n");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < estudiantes; i++) {
        float suma = 0;
        float max = notas[i][0];
        float min = notas[i][0];

        for (int j = 0; j < ASIGNATURAS; j++) {
            suma += notas[i][j];
            if (notas[i][j] > max) max = notas[i][j];
            if (notas[i][j] < min) min = notas[i][j];
        }

        float promedio = suma / ASIGNATURAS;
        printf("Estudiante %d\t%.2f\t\t%.2f\t\t%.2f\n", i + 1, promedio, max, min);
    }
}

void procesarAsignaturas(float **notas, int estudiantes) {
    printf("\n=========================================================\n");
    printf("               REPORTE POR ASIGNATURA\n");
    printf("=========================================================\n");
    printf("Asig.\tPromedio\tNota Max\tNota Min\tAprob.\tReprob.\n");
    printf("---------------------------------------------------------\n");

    for (int j = 0; j < ASIGNATURAS; j++) {
        float suma = 0;
        float max = notas[0][j];
        float min = notas[0][j];
        int aprobados = 0;
        int reprobados = 0;

        for (int i = 0; i < estudiantes; i++) {
            float notaActual = notas[i][j];
            suma += notaActual;

            if (notaActual > max) max = notaActual;
            if (notaActual < min) min = notaActual;

            if (notaActual >= 6.0) {
                aprobados++;
            } else {
                reprobados++;
            }
        }

        float promedio = suma / estudiantes;
        printf("Asig. %d\t%.2f\t\t%.2f\t\t%.2f\t\t%d\t%d\n", 
               j + 1, promedio, max, min, aprobados, reprobados);
    }
    printf("=========================================================\n");
}