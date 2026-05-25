#include <stdio.h>
#include <stdlib.h>
float** asignarMemoria(int estudiantes, int asignaturas);
void liberarMemoria(float** notas, int estudiantes);

int main() {
    int n;
    const int ASIG = 3;

    printf("Ingrese el numero de estudiantes: ");
    scanf("%d", &n);

    float** notas = asignarMemoria(n, ASIG);
    
    
    liberarMemoria(notas, n);
    return 0;
}

float** asignarMemoria(int estudiantes, int asignaturas) {
    float** matriz = (float**)malloc(estudiantes * sizeof(float*));
    for (int i = 0; i < estudiantes; i++) {
        matriz[i] = (float*)malloc(asignaturas * sizeof(float));
    }
    return matriz;
}

void liberarMemoria(float** notas, int estudiantes) {
    for (int i = 0; i < estudiantes; i++) {
        free(notas[i]);
    }
    free(notas);
}
void leerNotas(float** notas, int n, int m) {
    for (int i = 0; i < n; i++) {
        printf("\nEstudiante %d:\n", i + 1);
        for (int j = 0; j < m; j++) {
            do {
                printf("  Asignatura %d: ", j + 1);
                scanf("%f", (*(notas + i) + j)); // Uso de punteros
                if (*(*(notas + i) + j) < 0 || *(*(notas + i) + j) > 10) {
                    printf("  [Error] La nota debe estar entre 0 y 10.\n");
                }
            } while (*(*(notas + i) + j) < 0 || *(*(notas + i) + j) > 10);
        }
    }
}
void reporteEstudiantes(float** notas, int n, int m) {
    printf("\n--- REPORTE POR ESTUDIANTE ---\n");
    for (int i = 0; i < n; i++) {
        float suma = 0, max = *(*(notas + i) + 0), min = *(*(notas + i) + 0);
        for (int j = 0; j < m; j++) {
            float actual = *(*(notas + i) + j);
            suma += actual;
            if (actual > max) max = actual;
            if (actual < min) min = actual;
        }
        printf("Estudiante %d | Promedio: %.2f | Max: %.2f | Min: %.2f\n", 
                i + 1, suma / m, max, min);
    }
}
void reporteAsignaturas(float** notas, int n, int m) {
    printf("\n--- REPORTE POR ASIGNATURA ---\n");
    for (int j = 0; j < m; j++) {
        float suma = 0, max = *(*(notas + 0) + j), min = *(*(notas + 0) + j);
        for (int i = 0; i < n; i++) {
            float actual = *(*(notas + i) + j);
            suma += actual;
            if (actual > max) max = actual;
            if (actual < min) min = actual;
        }
        printf("Asignatura %d | Promedio: %.2f | Max: %.2f | Min: %.2f\n", 
                j + 1, suma / n, max, min);
    }
}
void estadisticasAprobacion(float** notas, int n, int m);

estadisticasAprobacion(notas, n, ASIG);

void estadisticasAprobacion(float** notas, int n, int m) {
    printf("\n--- ESTADISTICAS DE APROBACION ---\n");
    for (int j = 0; j < m; j++) {
        int ap = 0, rep = 0;
        for (int i = 0; i < n; i++) {
            if (*(*(notas + i) + j) >= 6.0) ap++;
            else rep++;
        }
        printf("Asig. %d | Aprobados: %d | Reprobados: %d\n", j + 1, ap, rep);
    }
}