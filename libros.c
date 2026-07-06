#include "libros.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
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

    // Nueva validación integrada
    int len = strlen(nuevo.codigo_libro);

    // 1. Validar longitud (1 a 15)
    if (len < 1 || len > 15) {
    printf("Error: El codigo debe tener entre 1 y 15 caracteres.\n");
    esCorrecto = 0;
    } 
    // 2. Validar alfanumérico (letras y números, sin espacios)
    else {
        for (int i = 0; i < len; i++) {
            if (!isalnum(nuevo.codigo_libro[i])) {
                printf("Error: El codigo solo permite letras y numeros (sin espacios).\n");
                esCorrecto = 0;
                break; 
            }
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
    char continuar;


    do {
        printf("\nQue campo desea modificar?\n");
        printf("1. Codigo\n2. Titulo\n3. Clasificacion\n4. Autor\n5. ISBN\n6. Stock\nOpcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n');

        switch (opcion) {
            case 1: // Codigo (con validación de duplicados)
                {
                    char nuevoCodigo[20];
                    int duplicado;
                    do {
                        duplicado = 0;
                        printf("Nuevo codigo: ");
                        scanf("%s", nuevoCodigo);
                        for(int i = 0; i < inv->total; i++) {
                            if(i != indice && strcmp(inv->libros[i].codigo_libro, nuevoCodigo) == 0) {
                                duplicado = 1;
                                break;
                            }
                        }
                        if(duplicado) printf("Error: Codigo duplicado.\n");
                        else strcpy(inv->libros[indice].codigo_libro, nuevoCodigo);
                    } while (duplicado == 1);
                }
                break;
            case 2: // Titulo
                printf("Nuevo titulo: ");
                fgets(inv->libros[indice].titulo, 100, stdin);
                inv->libros[indice].titulo[strcspn(inv->libros[indice].titulo, "\n")] = 0;
                break;
            case 3: // Clasificacion
                printf("Nueva clasificacion: ");
                fgets(inv->libros[indice].clasificacion, 50, stdin);
                inv->libros[indice].clasificacion[strcspn(inv->libros[indice].clasificacion, "\n")] = 0;
                break;
            case 4: // Autor
                printf("Nuevo autor: ");
                fgets(inv->libros[indice].autor_principal, 80, stdin);
                inv->libros[indice].autor_principal[strcspn(inv->libros[indice].autor_principal, "\n")] = 0;
                break;
            case 5: // ISBN (con validación de duplicados)
                {
                    char nuevoIsbn[20];
                    int duplicado;
                    do {
                        duplicado = 0;
                        printf("Nueva ISBN: ");
                        fgets(nuevoIsbn, 20, stdin);
                        nuevoIsbn[strcspn(nuevoIsbn, "\n")] = 0; // Limpiar el \n

                        // Verificamos si existe en otro libro
                        for(int i = 0; i < inv->total; i++) {
                            if(i != indice && strcmp(inv->libros[i].isbn, nuevoIsbn) == 0) {
                                duplicado = 1;
                                break;
                            }
                        }
                        if(duplicado) printf("Error: Este ISBN ya esta asignado a otro libro.\n");
                        else strcpy(inv->libros[indice].isbn, nuevoIsbn);
                    } while (duplicado == 1);
                }
                break;
            case 6: // Stock
                printf("Nuevo stock: ");
                scanf("%d", &inv->libros[indice].stock);
                while (getchar() != '\n');
                break;
            default:
                printf("Opcion no valida.\n");
        }

        printf("¿Desea modificar otro campo? (s/n): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n');

    } while (continuar == 's' || continuar == 'S');

    printf("Actualizacion finalizada.\n");
}

void eliminarLibro(struct Inventario *inv) {
    char codigoBusqueda[20];
    printf("\n--- Eliminar libro ---\n");
    printf("Ingrese el codigo del libro a eliminar: ");
    scanf("%s", codigoBusqueda);
    while (getchar() != '\n');

    int indice = -1;
    // 1. Buscamos el libro
    for (int i = 0; i < inv->total; i++) {
        if (strcmp(inv->libros[i].codigo_libro, codigoBusqueda) == 0) {
            indice = i;
            break;
        }
    }

    // 2. Si no lo encontramos
    if (indice == -1) {
        printf("Error: Libro no encontrado.\n");
        return;
    }

    // 3. Confirmación de seguridad
    char confirmar;
    printf("Esta seguro de eliminar el libro '%s'? (s/n): ", inv->libros[indice].titulo);
    scanf(" %c", &confirmar);
    while (getchar() != '\n');

    if (confirmar == 's' || confirmar == 'S') {
        // 4. La magia de la eliminación eficiente:
        // Movemos el último libro del arreglo a la posición que queremos borrar
        inv->libros[indice] = inv->libros[inv->total - 1];
        
        // 5. Reducimos el total de libros
        inv->total--;
        
        printf("El libro ha sido eliminado exitosamente.\n");
    } else {
        printf("Operacion cancelada.\n");
    }
}

void gestionarStock(struct Inventario *inv) {
    char cod[20];
    printf("\n--- Gestionar Stock ---\nIngrese el codigo del libro: ");
    scanf("%s", cod);
    while(getchar() != '\n');

    for (int i = 0; i < inv->total; i++) {
        if (strcmp(inv->libros[i].codigo_libro, cod) == 0) {
            int opcion, cantidad;
            printf("Libro: %s | Stock actual: %d\n", inv->libros[i].titulo, inv->libros[i].stock);
            printf("1. Incrementar | 2. Disminuir: ");
            scanf("%d", &opcion);
            printf("Cantidad: ");
            scanf("%d", &cantidad);
            
            if (opcion == 1) inv->libros[i].stock += cantidad;
            else if (opcion == 2 && inv->libros[i].stock >= cantidad) inv->libros[i].stock -= cantidad;
            else printf("Error: Operacion invalida.\n");
            
            printf("Nuevo stock: %d\n", inv->libros[i].stock);
            return;
        }
    }
    printf("Libro no encontrado.\n");
}

void identificarLibrosAgotados(struct Inventario *inv) {
    printf("\n--- Libros Agotados (Stock 0) ---\n");
    int encontrados = 0;
    for (int i = 0; i < inv->total; i++) {
        if (inv->libros[i].stock == 0) {
            printf("- %s (Cod: %s)\n", inv->libros[i].titulo, inv->libros[i].codigo_libro);
            encontrados = 1;
        }
    }
    if (!encontrados) printf("No hay libros agotados.\n");
}

void identificarLibrosStockBajo(struct Inventario *inv) {
    int limite;
    printf("\nIngrese el limite de stock para filtrar: ");
    scanf("%d", &limite);
    printf("\n--- Libros con Stock Bajo (menor a %d) ---\n", limite);
    for (int i = 0; i < inv->total; i++) {
        if (inv->libros[i].stock < limite) {
            printf("- %s: %d unidades\n", inv->libros[i].titulo, inv->libros[i].stock);
        }
    }
}
void reportePorClasificacion(struct Inventario *inv) {
    printf("\n--- Reporte por Clasificacion ---\n");
    
    // Creamos un arreglo temporal para llevar la cuenta
    char categorias[MAX_LIBROS][50];
    int conteos[MAX_LIBROS];
    int totalCategorias = 0;

    for (int i = 0; i < inv->total; i++) {
        int encontrada = 0;
        // Buscamos si ya registramos esta categoría en nuestro conteo
        for (int j = 0; j < totalCategorias; j++) {
            if (strcmp(inv->libros[i].clasificacion, categorias[j]) == 0) {
                conteos[j]++;
                encontrada = 1;
                break;
            }
        }
        // Si es una categoría nueva, la agregamos
        if (!encontrada) {
            strcpy(categorias[totalCategorias], inv->libros[i].clasificacion);
            conteos[totalCategorias] = 1;
            totalCategorias++;
        }
    }

    // Mostramos los resultados
    for (int i = 0; i < totalCategorias; i++) {
        printf("Categoria: %s | Libros: %d\n", categorias[i], conteos[i]);
    }
}


void guardarInventario(struct Inventario *inv) {
    // Abrimos el archivo como .csv para que Excel lo abra directamente
    FILE *archivo = fopen("inventario.csv", "w");

    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo para guardar.\n");
        return;
    }

    // 1. Escribimos el encabezado (esto le dice a Excel qué es cada columna)
    fprintf(archivo, "Codigo,Titulo,Clasificacion,Autor,ISBN,Stock\n");

    // 2. Recorremos el arreglo de libros y guardamos cada registro
    // Usamos comas (,) para separar los campos, que es lo que define al CSV
    for (int i = 0; i < inv->total; i++) {
        fprintf(archivo, "%s,%s,%s,%s,%s,%d\n", 
                inv->libros[i].codigo_libro,
                inv->libros[i].titulo,
                inv->libros[i].clasificacion,
                inv->libros[i].autor_principal,
                inv->libros[i].isbn,
                inv->libros[i].stock);
    }

    fclose(archivo);
    printf("Inventario guardado exitosamente en 'inventario.csv'.\n");
    printf("Puedes abrir este archivo directamente con Excel.\n");
}
void cargarInventario(struct Inventario *inv) {
    FILE *archivo = fopen("inventario.csv", "r");
    if (archivo == NULL) {
        printf("No se encontro archivo previo. Iniciando inventario vacio.\n");
        return;
    }

    // Saltamos el encabezado (la primera línea)
    char linea[200];
    fgets(linea, sizeof(linea), archivo); 

    inv->total = 0;
    // Leemos línea por línea hasta el final
    while (fscanf(archivo, "%[^,],%[^,],%[^,],%[^,],%[^,],%d\n", 
                  inv->libros[inv->total].codigo_libro,
                  inv->libros[inv->total].titulo,
                  inv->libros[inv->total].clasificacion,
                  inv->libros[inv->total].autor_principal,
                  inv->libros[inv->total].isbn,
                  &inv->libros[inv->total].stock) == 6) {
        inv->total++;
    }

    fclose(archivo);
    printf("Inventario cargado exitosamente. Total libros: %d\n", inv->total);
}

        
        
   

