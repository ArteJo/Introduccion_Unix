#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *meminfo;
    char line[256];
    
    printf("=== INFORMACIÓN DEL SISTEMA ===\n\n");
    
    printf("Usuario actual:\n");
    system("whoami");
    
    printf("\nDirectorio actual:\n");
    system("pwd");
    
    printf("\nEspacio en disco:\n");
    system("df -h / | tail -1");
    
    printf("\nMemoria:\n");
    meminfo = fopen("/proc/meminfo", "r");
    if (meminfo != NULL) {
        int count = 0;
        // Esto lee las primeras 3 líneas (MemTotal, MemFree, MemAvailable)
        while (fgets(line, sizeof(line), meminfo) && count < 3) {
            printf("%s", line);
            count++;
        }
        fclose(meminfo);
    } else {
        printf("Error al leer /proc/meminfo\n");
    }
    
    printf("\nProcesador:\n");
    system("grep 'model name' /proc/cpuinfo | head -1 | cut -d':' -f2");
    
    return 0;
}