#include <stdio.h>
#include "libros.h"

int main() {
    struct Inventario miLibreria;
    miLibreria.total = 0;
    int opcion;
    do {
        opcion = mostrarmenu();
        switch (opcion) {
            case 1: registrolibro(&miLibreria); break;
            case 2: listarlibros(&miLibreria); break;
            case 3: buscarLibro(&miLibreria); break;
            case 4: actualizarLibro(&miLibreria); break;
            case 5: eliminarLibro(&miLibreria); break;
            case 6: {
    int subopcion;
    printf("\n--- Control de Stock ---\n");
    printf("1. Consultar y Actualizar stock\n");
    printf("2. Identificar libros agotados\n");
    printf("3. Identificar libros con stock bajo\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &subopcion);
    while (getchar() != '\n');

    switch(subopcion) {
        case 1: gestionarStock(&miLibreria); break;
        case 2: identificarLibrosAgotados(&miLibreria); break;
        case 3: identificarLibrosStockBajo(&miLibreria); break;
        default: printf("Opcion no valida.\n");
    }
    break;
}
            case 7: reportePorClasificacion(&miLibreria); break;         
            case 9: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida.\n");
        }
    } while (opcion != 9);
    return 0;
}
