#include <stdio.h>
#include <ctype.h>
#include <string.h> // Necesaria para manejar cadenas de texto

int main() {
    FILE *archivo;
    char nombre_archivo[100];
    char ruta_completa[256];
    
    // 1. Definimos la ruta base de donde se encuentran los documentos
    // Podemos cambiar la ruta si lo deseamos para que busque en otro lugar.
    char *ruta_base = "/home/artejo/Documents/Autonomo1/";
    
    int c, anterior = '\n';
    long caracteres = 0, palabras = 0, lineas = 0, parrafos = 0;
    int en_palabra = 0;

    printf("Escribe el nombre del archivo (debe ser en formato .txt): ");
    scanf("%s", nombre_archivo);

    // 2. Validamos que el archivo termine en .txt
    char *extension = strrchr(nombre_archivo, '.');
    if (extension == NULL || strcmp(extension, ".txt") != 0) {
        printf("Error: Solo se permiten archivos con extensión .txt\n");
        return 1;
    }

    // 3. Unimos la ruta base con el nombre del archivo
    strcpy(ruta_completa, ruta_base);
    strcat(ruta_completa, nombre_archivo);

    archivo = fopen(ruta_completa, "r");
    if (archivo == NULL) {
        printf("Error: No se encontró '%s' en la carpeta.\n", nombre_archivo);
        return 1;
    }

    // ... (El resto del bucle while para contar se mantiene igual que el anterior)
    while ((c = fgetc(archivo)) != EOF) {
        caracteres++;
        if (c == '\n') lineas++;
        if (isspace(c)) {
            en_palabra = 0;
        } else if (en_palabra == 0) {
            en_palabra = 1;
            palabras++;
        }
        if (c == '\n' && anterior == '\n') parrafos++;
        anterior = c;
    }

    if (caracteres > 0) { if (lineas == 0) lineas = 1; parrafos++; }

    fclose(archivo);
    printf("\nSe ha analizado: %s\n", ruta_completa);
    printf("Palabras: %ld | Líneas: %ld | Párrafos: %ld\n", palabras, lineas, parrafos);

    return 0;
}