#include <stdio.h>

int main() {
    int inicio, fin, incremento;

    // Datos del usuario
    printf("Ingrese el numero inicial: ");
    scanf("%d", &inicio);

    printf("Ingrese el numero final: ");
    scanf("%d", &fin);

    printf("Ingrese el incremento: ");
    scanf("%d", &incremento);

    // incremento invalido
    if (incremento == 0) {
        printf("El incremento no puede ser 0.\n");
        return 0;
    }

    printf("Numeros generados:\n");

    // Uso de for
    for (int i = inicio; 
         (incremento > 0) ? i <= fin : i >= fin; 
         i += incremento) {
        printf("%d\n", i);
    }

    return 0;
}