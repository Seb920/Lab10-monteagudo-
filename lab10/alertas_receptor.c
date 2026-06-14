#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje { long mtype; char texto[100]; };

int main() {
    key_t clave = 5555;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    struct mensaje msg;

    if (id_cola == -1) { perror("msgget"); exit(1); }

    printf("=== Receptor solo atiende tipo 3 ===\n");
    if (msgrcv(id_cola, &msg, sizeof(msg.texto), 3, 0) == -1) {
        perror("msgrcv"); exit(1);
    }
    printf("[CRITICO] %s\n", msg.texto);
    printf("Los mensajes tipo 1 y 2 quedan en cola sin ser leidos.\n");
    return 0;
}
