#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PALABRAS 100
#define MAX_LONGITUD 20
#define TAMANO_SOPA 10

char sopa[TAMANO_SOPA][TAMANO_SOPA];
char palabras[MAX_PALABRAS][MAX_LONGITUD];
int numPalabras = 0;

void menu();
void crearSopa();
void imprimirSopa();
void agregarPalabra();
void insertarPalabraEnSopa(char *palabra);
int puedeInsertarse(int fila, int col, char *palabra, int dx, int dy);
void insertar(int fila, int col, char *palabra, int dx, int dy);

int main() {
    srand((unsigned int)time(NULL));
    menu();
    return 0;
}

void menu() {
    int opcion;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Agregar palabra\n");
        printf("2. Crear sopa de letras\n");
        printf("3. Imprimir sopa\n");
        printf("4. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);
        getchar();  // Limpiar el buffer del teclado

        switch (opcion) {
            case 1:
                agregarPalabra();
                break;
            case 2:
                crearSopa();
                break;
            case 3:
                imprimirSopa();
                break;
            case 4:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida\n");
        }
    } while (opcion != 4);
}

void agregarPalabra() {
    if (numPalabras >= MAX_PALABRAS) {
        printf("No se pueden agregar mas palabras.\n");
        return;
    }

    char palabra[MAX_LONGITUD];
    int i;

    printf("Introduce la palabra a agregar (sin espacios): ");
    scanf("%s", palabra);

    if (strlen(palabra) >= MAX_LONGITUD) {
        printf("La palabra es demasiado larga (maximo %d caracteres).\n", MAX_LONGITUD - 1);
        return;
    }

    for (i = 0; i < numPalabras; i++) {
        if (strcmp(palabras[i], palabra) == 0) {
            printf("La palabra ya existe en la lista.\n");
            return;
        }
    }

    strcpy(palabras[numPalabras], palabra);
    numPalabras++;
    printf("Palabra agregada correctamente.\n");
}

void crearSopa() {
    int i, j;

    for (i = 0; i < TAMANO_SOPA; i++) {
        for (j = 0; j < TAMANO_SOPA; j++) {
            sopa[i][j] = 'A' + rand() % 26;
        }
    }

    for (i = 0; i < numPalabras; i++) {
        insertarPalabraEnSopa(palabras[i]);
    }

    printf("Sopa de letras generada.\n");
}

void imprimirSopa() {
    int i, j;

    printf("\nSOPA DE LETRAS:\n");
    for (i = 0; i < TAMANO_SOPA; i++) {
        for (j = 0; j < TAMANO_SOPA; j++) {
            printf("%c ", sopa[i][j]);
        }
        printf("\n");
    }

    printf("\nPalabras:\n");
    for (i = 0; i < numPalabras; i++) {
        printf("%s\n", palabras[i]);
    }
}

void insertarPalabraEnSopa(char *palabra) {
    int len = strlen(palabra);
    int intentos = 100;
    int fila, col, dx, dy;

    while (intentos--) {
        fila = rand() % TAMANO_SOPA;
        col = rand() % TAMANO_SOPA;
        dx = rand() % 3 - 1;
        dy = rand() % 3 - 1;

        if (dx == 0 && dy == 0) continue;

        if (puedeInsertarse(fila, col, palabra, dx, dy)) {
            insertar(fila, col, palabra, dx, dy);
            return;
        }
    }
    printf("No se pudo insertar la palabra: %s\n", palabra);
}

int puedeInsertarse(int fila, int col, char *palabra, int dx, int dy) {
    int i, x, y;
    int len = strlen(palabra);

    for (i = 0; i < len; i++) {
        x = fila + i * dx;
        y = col + i * dy;
        if (x < 0 || x >= TAMANO_SOPA || y < 0 || y >= TAMANO_SOPA) return 0;
    }
    return 1;
}

void insertar(int fila, int col, char *palabra, int dx, int dy) {
    int i, x, y;
    int len = strlen(palabra);

    for (i = 0; i < len; i++) {
        x = fila + i * dx;
        y = col + i * dy;
        sopa[x][y] = palabra[i];
    }
}
