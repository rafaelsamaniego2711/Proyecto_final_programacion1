#include <stdio.h>
#include <stdlib.h>
float** asignarMemoria(int estudiantes, int asignaturas);
void leerNotas(float** notas, int n, int m);
void reporteEstudiantes(float** notas, int n, int m);
void reporteAsignaturas(float** notas, int n, int m);
void estadisticasAprobacion(float** notas, int n, int m);
void liberarMemoria(float** notas, int estudiantes);

int main() {
    int n;
    const int ASIG = 3; 

    printf("========================================\n");
    printf("   GESTIÓN DE CALIFICACIONES ESCOLARES  \n");
    printf("========================================\n");
    
    printf("Ingrese el número de estudiantes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("[Error] Cantidad de estudiantes no válida.\n");
        return 1;
    }

    float** notas = asignarMemoria(n, ASIG);
    
    leerNotas(notas, n, ASIG);
    
    reporteEstudiantes(notas, n, ASIG);
    
    reporteAsignaturas(notas, n, ASIG);
    
    estadisticasAprobacion(notas, n, ASIG);
    
    liberarMemoria(notas, n);
    
    printf("\n========================================\n");
    printf("     PROGRAMA FINALIZADO CON ÉXITO     \n");
    printf("========================================\n");
    
    return 0;
}

float** asignarMemoria(int estudiantes, int asignaturas) {
    float** matriz = (float**)malloc(estudiantes * sizeof(float*));
    for (int i = 0; i < estudiantes; i++) {
        *(matriz + i) = (float*)malloc(asignaturas * sizeof(float));
    }
    return matriz;
}

void leerNotas(float** notas, int n, int m) {
    for (int i = 0; i < n; i++) {
        printf("\nNotas del Estudiante %d:\n", i + 1);
        for (int j = 0; j < m; j++) {
            do {
                printf("  Asignatura %d [0-10]: ", j + 1);
                scanf("%f", (*(notas + i) + j));
                if (*(*(notas + i) + j) < 0.0 || *(*(notas + i) + j) > 10.0) {
                    printf("  [Error] La nota debe estar entre 0 y 10. Intente de nuevo.\n");
                }
            } while (*(*(notas + i) + j) < 0.0 || *(*(notas + i) + j) > 10.0);
        }
    }
}

void reporteEstudiantes(float** notas, int n, int m) {
    printf("\n========================================\n");
    printf("        REPORTE POR ESTUDIANTE\n");
    printf("========================================\n");
    for (int i = 0; i < n; i++) {
        float suma = 0;
        float max = *(*(notas + i) + 0);
        float min = *(*(notas + i) + 0);
        
        for (int j = 0; j < m; j++) {
            float val = *(*(notas + i) + j);
            suma += val;
            if (val > max) max = val;
            if (val < min) min = val;
        }
        printf("Est. %d -> Promedio: %.2f | Máx: %.2f | Mín: %.2f\n", 
                i + 1, suma / m, max, min);
    }
}

void reporteAsignaturas(float** notas, int n, int m) {
    printf("\n========================================\n");
    printf("        REPORTE POR ASIGNATURA\n");
    printf("========================================\n");
    for (int j = 0; j < m; j++) {
        float suma = 0;
        float max = *(*(notas + 0) + j);
        float min = *(*(notas + 0) + j);
        
        for (int i = 0; i < n; i++) {
            float val = *(*(notas + i) + j);
            suma += val;
            if (val > max) max = val;
            if (val < min) min = val;
        }
        printf("Asig. %d -> Promedio: %.2f | Máx: %.2f | Mín: %.2f\n", 
                j + 1, suma / n, max, min);
    }
}

void estadisticasAprobacion(float** notas, int n, int m) {
    printf("\n========================================\n");
    printf("      ESTADÍSTICAS DE APROBACIÓN\n");
    printf("========================================\n");
    for (int j = 0; j < m; j++) {
        int aprobados = 0;
        int reprobados = 0;
        
        for (int i = 0; i < n; i++) {
            if (*(*(notas + i) + j) >= 6.0) {
                aprobados++;
            } else {
                reprobados++;
            }
        }
        printf("Asig. %d -> Aprobados: %d | Reprobados: %d\n", j + 1, aprobados, reprobados);
    }
}

void liberarMemoria(float** notas, int estudiantes) {
    for (int i = 0; i < estudiantes; i++) {
        free(*(notas + i));
    }
    free(notas);
}