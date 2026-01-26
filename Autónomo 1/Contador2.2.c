#include <stdio.h>
#include <ctype.h>
#include <string.h> // Necesaria para manejar cadenas de texto
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // 1. Verificamos si se pasó el nombre del archivo como argumento
    if (argc < 2) {
        printf("Uso: analiza <nombre_del_archivo.txt>\n");
        return 1;
    }

    char *nombre_archivo = argv[1];
    char ruta_completa[512];

    // 2. Obtenemos la ruta personal del usuario (Home) dinámicamente
    char *home = getenv("HOME");
    if (home == NULL) {
        printf("Error: No se pudo determinar la ruta del sistema.\n");
        return 1;
    }

    // 3. Validamos la extensión .txt
    char *extension = strrchr(nombre_archivo, '.');
    if (extension == NULL || strcmp(extension, ".txt") != 0) {
        printf("Error: El archivo '%s' debe tener extensión .txt\n", nombre_archivo);
        return 1;
    }

    // 4. Construimos la ruta hacia la carpeta específica
    // snprintf une: /home/usuario + /Documents/Autonomo1/ + archivo.txt
    snprintf(ruta_completa, sizeof(ruta_completa), "%s/Documents/Autonomo1/%s", home, nombre_archivo);

    FILE *archivo = fopen(ruta_completa, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir '%s'.\nVerifica que el archivo esté en: %s/Documents/Autonomo1/\n", nombre_archivo, home);
        return 1;
    }

    // 5. Variables de conteo
    int c, anterior = '\n';
    long caracteres = 0, palabras = 0, lineas = 0, parrafos = 0;
    int en_palabra = 0;

    // 6. Bucle de análisis carácter por carácter
    while ((c = fgetc(archivo)) != EOF) {
        caracteres++;

        // Contar líneas
        if (c == '\n') lineas++;

        // Contar palabras (máquina de estados simple)
        if (isspace(c)) {
            en_palabra = 0;
        } else if (en_palabra == 0) {
            en_palabra = 1;
            palabras++;
        }

        // Contar párrafos (detectar doble salto de línea)
        if (c == '\n' && anterior == '\n') {
            parrafos++;
        }

        anterior = c;
    }

    // Si hay texto, hay al menos un párrafo y una línea
    // Segun la RAE, no hay un minimo de lineas establecido por lo que un párrafo puede tener incluso 1 sola linea.
    if (caracteres > 0) {
        if (lineas == 0) lineas = 1;
        parrafos++;
    }

    fclose(archivo);

    // 7. Mostrar resultados estilizados
    printf("   RESULTADOS DEL ANÁLISIS\n");
    printf("==========================================\n");
    printf(" Archivo:    %s\n", nombre_archivo);
    printf(" Ruta:       %s\n", ruta_completa);
    printf("------------------------------------------\n");
    printf(" Caracteres: %ld\n", caracteres);
    printf(" Palabras:   %ld\n", palabras);
    printf(" Líneas:     %ld\n", lineas);
    printf(" Párrafos:   %ld\n", parrafos);

    return 0;
}