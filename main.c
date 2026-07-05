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
            case 9: printf("Saliendo...\n"); break;
            default: printf("Opcion no valida.\n");
        }
    } while (opcion != 9);
    return 0;
}