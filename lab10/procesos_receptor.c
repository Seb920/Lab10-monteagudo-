#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje { long mtype; char texto[100]; };

int main() {
    key_t clave = 4444;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    struct mensaje msg;

    if (id_cola == -1) { perror("msgget"); exit(1); }

    printf("=== Clasificador de Procesos ===\n");
    while (1) {
        if (msgrcv(id_cola, &msg, sizeof(msg.texto), 0, IPC_NOWAIT) == -1) break;

        if (msg.mtype == 1)      printf("[INICIO]    %s\n", msg.texto);
        else if (msg.mtype == 2) printf("[DETENIDO]  %s\n", msg.texto);
        else if (msg.mtype == 3) printf("[ERROR]     %s\n", msg.texto);
    }
    return 0;
}
