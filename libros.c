#include "libros.h"
#include <stdio.h>
#include <string.h>

int mostrarmenu () {
    int opcion;
    printf ("\n-----Gestion de libros-----\n");
    printf ("1.) Registrar libro\n");
    printf ("2.) Listar libros\n");
    printf ("3.) Buscar libro\n");
    printf ("4.) Actualizar libro\n");
    printf ("5.) Eliminar libro\n");
    printf ("6.) Consultar stock\n");
    printf ("7.) Reportes\n");
    printf ("8.) Guardar cambios\n");
    printf ("9.) Salir\n");
    printf ("Ingrese el numero de opcion deseada: ");
    scanf ("%d", &opcion);
    while (getchar() != '\n');
    return opcion;
}

void registrolibro(struct Inventario *inv) {
    if (inv->total >= MAX_LIBROS) {
        printf("\nError: No hay espacio disponible.\n");
        return;
    }
    struct Libro nuevo;
    printf("\n--- Registro de libros ---\n");
    printf("Ingrese el codigo del libro: ");
    fgets(nuevo.codigo_libro, 20, stdin);
    nuevo.codigo_libro[strcspn(nuevo.codigo_libro, "\n")] = 0;
    printf("Ingrese el titulo del libro: ");
    fgets(nuevo.titulo, 100, stdin);
    nuevo.titulo[strcspn(nuevo.titulo, "\n")] = 0;
    printf("Ingrese la clasificacion: ");
    fgets(nuevo.clasificacion, 50, stdin);
    nuevo.clasificacion[strcspn(nuevo.clasificacion, "\n")] = 0;
    printf("Ingrese el autor del libro: ");
    fgets(nuevo.autor_principal, 80, stdin);
    nuevo.autor_principal[strcspn(nuevo.autor_principal, "\n")] = 0;
    printf("Ingrese el isbn: ");
    fgets(nuevo.isbn, 20, stdin);
    nuevo.isbn[strcspn(nuevo.isbn, "\n")] = 0;
    
    printf("Ingrese el titulo del libro: ");
    fgets(nuevo.titulo, 100, stdin);
    nuevo.titulo[strcspn(nuevo.titulo, "\n")] = 0;
    
    printf("Ingrese la clasificacion: ");
    fgets(nuevo.clasificacion, 50, stdin);
    nuevo.clasificacion[strcspn(nuevo.clasificacion, "\n")] = 0;
    
    printf("Ingrese el autor del libro: ");
    fgets(nuevo.autor_principal, 80, stdin);
    nuevo.autor_principal[strcspn(nuevo.autor_principal, "\n")] = 0;
    
    printf("Ingrese el isbn: ");
    fgets(nuevo.isbn, 20, stdin);
    nuevo.isbn[strcspn(nuevo.isbn, "\n")] = 0;
    printf("Ingrese el stock: ");
    scanf("%d", &nuevo.stock);
    while (getchar() != '\n');
    inv->libros[inv->total] = nuevo;
    inv->total++;
    printf("\nEl libro '%s' ha sido registrado exitosamente\n", nuevo.titulo);
}

void listarlibros(struct Inventario *inv) {
    if (inv->total == 0) {
        printf("\nEl inventario esta vacio.\n");
        return;
    }

    printf("\n--- Listado de Libros ---\n");
    // Cabecera alineada a la izquierda con el ancho definido
    printf("%-10s | %-20s | %-15s | %-15s | %-10s | %-6s\n", 
           "Codigo", "Titulo", "Clasif.", "Autor", "ISBN", "Stock");
    printf("---------------------------------------------------------------------------------------------\n");

    // Ciclo para imprimir los datos reales
    for (int i = 0; i < inv->total; i++) {
        printf("%-10s | %-20s | %-15s | %-15s | %-10s | %-6d\n", 
               inv->libros[i].codigo_libro, 
               inv->libros[i].titulo, 
               inv->libros[i].clasificacion, 
               inv->libros[i].autor_principal, 
               inv->libros[i].isbn, 
               inv->libros[i].stock);
    }
}
void buscarLibro(struct Inventario *inv) {
    char busqueda[100];
    int tipo;
    printf("\nBuscar por: 1.Codigo, 2.Titulo, 3.Clasificacion, 4.Autor, 5.ISBN: ");
    scanf("%d", &tipo);
    while (getchar() != '\n');
    printf("Ingrese el valor a buscar: ");
    fgets(busqueda, 100, stdin);
    busqueda[strcspn(busqueda, "\n")] = 0;
    int encontrado = 0;
    for (int i = 0; i < inv->total; i++) {
        int match = 0;
        if (tipo == 1 && strcmp(inv->libros[i].codigo_libro, busqueda) == 0) match = 1;
        else if (tipo == 2 && strcmp(inv->libros[i].titulo, busqueda) == 0) match = 1;
        else if (tipo == 3 && strcmp(inv->libros[i].clasificacion, busqueda) == 0) match = 1;
        else if (tipo == 4 && strcmp(inv->libros[i].autor_principal, busqueda) == 0) match = 1;
        else if (tipo == 5 && strcmp(inv->libros[i].isbn, busqueda) == 0) match = 1;
        if (match) {
            printf("Encontrado: %s | Titulo: %s | Autor: %s\n", inv->libros[i].codigo_libro, inv->libros[i].titulo, inv->libros[i].autor_principal);
            encontrado = 1;
        }
    }
    if (!encontrado) printf("\nNo se encontraron resultados.\n");
}

        printf("%-10s | %-20s | %-15s | %-15s | %-10s | %d\n", 
               inv->libros[i].codigo_libro, 
               inv->libros[i].titulo, 
               inv->libros[i].clasificacion, 
               inv->libros[i].autor_principal, 
               inv->libros[i].isbn, 
               inv->libros[i].stock);
    }

