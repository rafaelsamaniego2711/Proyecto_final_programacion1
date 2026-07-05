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
    // Validacion de Codigo alfanumerico (Versión limpia)
int esCorrecto; 
do {
    esCorrecto = 1; 
    printf("Ingrese el codigo del libro: ");
    fgets(nuevo.codigo_libro, 20, stdin);
    nuevo.codigo_libro[strcspn(nuevo.codigo_libro, "\n")] = 0;

    // 1. Validar vacío
    if (strlen(nuevo.codigo_libro) == 0) {
        printf("Error: El codigo no puede estar vacio.\n");
        esCorrecto = 0;
        continue; // Saltar al inicio del bucle
    }

    // 2. Validar alfanumérico
    for (int i = 0; i < strlen(nuevo.codigo_libro); i++) {
        char c = nuevo.codigo_libro[i];
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
            printf("Error: Solo letras y numeros.\n");
            esCorrecto = 0;
            break; 
        }
    }

    // 3. Validar UNICIDAD (Aquí está el secreto)
    if (esCorrecto == 1) { // Solo si pasó las pruebas anteriores, buscamos duplicados
        for (int i = 0; i < inv->total; i++) {
            if (strcmp(inv->libros[i].codigo_libro, nuevo.codigo_libro) == 0) {
                printf("Error: Este codigo ya existe en el inventario.\n");
                esCorrecto = 0;
                break;
            }
        }
    }
} while (esCorrecto == 0);
do {
    printf("Ingrese el titulo del libro: ");
    fgets(nuevo.titulo, 100, stdin);
    nuevo.titulo[strcspn(nuevo.titulo, "\n")] = 0; // Limpiamos el \n

    if (strlen(nuevo.titulo) == 0) {
        printf("Error: El titulo no puede estar vacio.\n");
    }
} while (strlen(nuevo.titulo) == 0); // Esto hace que se repita si está vacío
    nuevo.titulo[strcspn(nuevo.titulo, "\n")] = 0;
    if (strlen(nuevo.titulo) == 0) {
    printf("Error: El titulo no puede estar vacio.\n");
    return; 
}
    printf("Ingrese la clasificacion: ");
    fgets(nuevo.clasificacion, 50, stdin);
    nuevo.clasificacion[strcspn(nuevo.clasificacion, "\n")] = 0;
    do {
    printf("Ingrese el autor del libro: ");
    fgets(nuevo.autor_principal, 80, stdin);
    nuevo.autor_principal[strcspn(nuevo.autor_principal, "\n")] = 0;

    if (strlen(nuevo.autor_principal) == 0) {
        printf("Error: El autor no puede estar vacio.\n");
    }
} while (strlen(nuevo.autor_principal) == 0);
    nuevo.autor_principal[strcspn(nuevo.autor_principal, "\n")] = 0;
    if (strlen(nuevo.autor_principal) == 0) {
    printf("Error: El autor no puede estar vacio.\n");
    return;
}
    int isbnValido;
    do {
        isbnValido = 1;
        printf("Ingrese el ISBN: ");
        fgets(nuevo.isbn, 20, stdin);
        nuevo.isbn[strcspn(nuevo.isbn, "\n")] = 0;

        for (int i = 0; i < inv->total; i++) {
            if (strcmp(inv->libros[i].isbn, nuevo.isbn) == 0) {
                printf("Error: Este ISBN ya existe.\n");
                isbnValido = 0;
                break; // Sale del for
            }
        }
    } while (isbnValido == 0);
    
do {
    printf("Ingrese el stock: ");
    scanf("%d", &nuevo.stock);
    while (getchar() != '\n'); // Limpia el buffer
    
    if (nuevo.stock < 0) {
        printf("Error: El stock debe ser mayor o igual a 0.\n");
    }
} while (nuevo.stock < 0);
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
    printf("\n%-10s | %-20s | %-15s | %-15s | %-10s | %-6s\n", "Codigo", "Titulo", "Clasif.", "Autor", "ISBN", "Stock");
    printf("------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < inv->total; i++) {
        int match = 0;
        if (tipo == 1 && strcmp(inv->libros[i].codigo_libro, busqueda) == 0) match = 1;
        else if (tipo == 2 && strcmp(inv->libros[i].titulo, busqueda) == 0) match = 1;
        else if (tipo == 3 && strcmp(inv->libros[i].clasificacion, busqueda) == 0) match = 1;
        else if (tipo == 4 && strcmp(inv->libros[i].autor_principal, busqueda) == 0) match = 1;
        else if (tipo == 5 && strcmp(inv->libros[i].isbn, busqueda) == 0) match = 1;
            if (match) {
            printf("%-10s | %-20s | %-15s | %-15s | %-10s | %-6d\n", 
            inv->libros[i].codigo_libro, 
            inv->libros[i].titulo, 
            inv->libros[i].clasificacion, 
            inv->libros[i].autor_principal, 
            inv->libros[i].isbn, 
            inv->libros[i].stock);
        }
    }
}
void actualizarLibro(struct Inventario *inv) {
    char codigoBusqueda[20];
    printf("\n--- Actualizar libro ---\n");
    printf("Ingrese el codigo del libro a actualizar: ");
    scanf("%s", codigoBusqueda);
    while (getchar() != '\n'); // Limpia el buffer

    int indice = -1;
    for (int i = 0; i < inv->total; i++) {
        if (strcmp(inv->libros[i].codigo_libro, codigoBusqueda) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Error: Libro no encontrado.\n");
        return;
    }

    // Si llegamos aquí, el libro existe. Ahora el menú de edición:
    int opcion;
    printf("\nQue campo desea modificar?\n");
    printf("1. Codigo\n2. Titulo\n3. Clasificacion\n4. Autor\n5. ISBN\n6. stockOpcion: ");
    scanf("%d", &opcion);
    while (getchar() != '\n');

    switch (opcion) {
        case 1: // Modificar codigo
            do {
                printf("Nuevo codigo: ");
                fgets(inv->libros[indice].codigo_libro, 20, stdin);
                inv->libros[indice].codigo_libro[strcspn(inv->libros[indice].codigo_libro, "\n")] = 0;
            } while (strlen(inv->libros[indice].codigo_libro) == 0);
            break;
        case 2: // modificar titulo
            do {
                printf("Nuevo titulo: ");
                fgets(inv->libros[indice].titulo, 100, stdin);
                inv->libros[indice].titulo[strcspn(inv->libros[indice].titulo, "\n")] = 0;
            } while (strlen(inv->libros[indice].titulo) == 0);
            break;
            
        case 3: // Modificar clasificacion
            do {
                printf("Nueva clasificacion: ");
                fgets(inv->libros[indice].clasificacion, 50, stdin);
                inv->libros[indice].clasificacion[strcspn(inv->libros[indice].clasificacion, "\n")] = 0;
            } while (strlen(inv->libros[indice].clasificacion) == 0);
            break;
        case 4: // Modificar autor
            do {
                printf("Nuevo autor: ");
                fgets(inv->libros[indice].autor_principal, 80, stdin);
                inv->libros[indice].autor_principal[strcspn(inv->libros[indice].autor_principal, "\n")] = 0;
            } while (strlen(inv->libros[indice].autor_principal) == 0);
            break;
        case 5: // Modificar isbn
            do {
                printf("Nueva ISBN: ");
                fgets(inv->libros[indice].isbn, 20, stdin);
                inv->libros[indice].isbn[strcspn(inv->libros[indice].isbn, "\n")] = 0;
            } while (strlen(inv->libros[indice].isbn) == 0);
            break;
        case 6: // Modificar stock
        printf("Nuevo stock: ");
        scanf("%d", &inv->libros[indice].stock);
        while (getchar() != '\n'); // Limpiamos el buffer
        break;
    
        
    }
    printf("Libro actualizado exitosamente.\n");
}
