#ifndef LIBROS_H
#define LIBROS_H

#define MAX_LIBROS 100

struct Libro {
    char codigo_libro[20];
    char titulo[100];
    char clasificacion[50];
    char autor_principal[80];
    char isbn[20];
    int stock;
};

struct Inventario {
    struct Libro libros[MAX_LIBROS];
    int total;
};

int mostrarmenu();
void registrolibro(struct Inventario *inv);
void listarlibros(struct Inventario *inv);
void buscarLibro(struct Inventario *inv); 
void actualizarLibro(struct Inventario *inv);

#endif