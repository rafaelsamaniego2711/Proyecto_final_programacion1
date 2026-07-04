#include "libros.h"
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
    
    printf("Ingrese el titulo del libro: ");
    fgets(nuevo.titulo, 100, stdin);
    
    printf("Ingrese la clasificacion: ");
    fgets(nuevo.clasificacion, 50, stdin);
    
    printf("Ingrese el autor del libro: ");
    fgets(nuevo.autor_principal, 80, stdin);
    
    printf("Ingrese el isbn: ");
    fgets(nuevo.isbn, 20, stdin);
    
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
    for (int i = 0; i < inv->total; i++) {
        printf("Libro %d: %s | Titulo: %s | Autor: %s | Stock: %d\n", 
               i + 1, inv->libros[i].codigo_libro, inv->libros[i].titulo, 
               inv->libros[i].autor_principal, inv->libros[i].stock);
    }
}