#include "libros.h"
int main (){
    int opcion = mostrarmenu();
    
    switch (opcion){
        case 1:
        registrolibro();
        break;
    default:
        printf ("Opcion invalida.\n");
    
    }
    return 0;
}