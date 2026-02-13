#include <stdio.h>
#include <stdlib.h>

int main() {
        printf("\033[1;32mMONITOR DE PROCESOS\033[0m\n");
        printf("\033[1;32m====================\033[0m\n\n");

        printf("\033[1;34m>> Top 10 - Uso de CPU:\033[0m\n");
        printf("\033[1;36m"); // 36 es Cyan
        // Vamos a mostrar solo: User, PID, %CPU, %MEM, Start, Time 
        system("ps -eo user:10,pid,%cpu,%mem,start,time,comm --sort=-%cpu | head -11");
        printf("\033[0m"); // 0 es Blanco (Reset)

        printf("\n\033[1;35m>> Top 10: Uso de Memoria:\033[0m\n");
        printf("\033[1;36m"); // 36 es Cyan
        system("ps -eo user:10,pid,%cpu,%mem,start,time,comm --sort=-%mem | head -11");
        printf("\033[0m"); // 0 es Blanco (Reset)

    return 0;
}