#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje { long mtype; char texto[150]; };

int main() {
    key_t clave = 9000;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    struct mensaje msg;

    if (id_cola == -1) { perror("msgget"); exit(1); }

    printf("=== Monitor del Sistema Operativo ===\n");

    while (1) {
        if (msgrcv(id_cola, &msg, sizeof(msg.texto), 0, 0) == -1) {
            perror("msgrcv"); exit(1);
        }
        if (msg.mtype == 1)      printf("[INFO] %s", msg.texto);
        else if (msg.mtype == 2) printf("[ADVERTENCIA] %s", msg.texto);
        else if (msg.mtype == 3) printf("[CRITICO] %s", msg.texto);
        else                     printf("[DESCONOCIDO] %s", msg.texto);
    }
}
