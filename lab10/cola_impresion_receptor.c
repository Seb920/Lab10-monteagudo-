#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje { long mtype; char texto[150]; };

int main() {
    key_t clave = 2222;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    struct mensaje msg;

    if (id_cola == -1) { perror("msgget"); exit(1); }

    printf("=== Cola de Impresion ===\n");
    while (1) {
        if (msgrcv(id_cola, &msg, sizeof(msg.texto), 0, IPC_NOWAIT) == -1) {
            printf("No hay mas solicitudes en cola.\n");
            break;
        }
        printf("Imprimiendo: %s\n", msg.texto);
    }
    return 0;
}
