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
void registrolibro(){
    struct Libro nuevolibro;
    printf ("\n-----Registro de libros-----\n");
    printf ("Ingrese el codigo del libro: ");
    fgets (nuevolibro.codigo_libro,20,stdin);
    printf ("Ingrese el titulo del libro: ");
    fgets (nuevolibro.titulo,100,stdin);
    printf ("Ingrese la clasificacion correspondiente al libro: ");
    fgets (nuevolibro.clasificacion,50,stdin);
    printf("Ingrese el autor del libro: ");
    fgets (nuevolibro.autor_principal,80,stdin);
    printf ("Ingrese el isbn correspondiente al libro: ");
    fgets (nuevolibro.isbn,20,stdin);
    printf ("Ingrese el stock del libro: ");
    scanf ("%d", nuevolibro.stock);
    printf ("\nEl libro %s ha sido resgistrado exitosamente\n", nuevolibro.titulo);
}