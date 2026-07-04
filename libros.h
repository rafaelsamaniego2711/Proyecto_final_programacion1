#ifndef LIBROS_H
#define LIBROS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct Libro { 
    char codigo_libro [20];
    char titulo [100];
    char clasificacion [50];
    char autor_principal [80];
    char isbn [20];
    int stock;

};

int mostrarmenu ();
void registrolibro();
#endif
