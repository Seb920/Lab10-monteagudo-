#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje { long mtype; char texto[100]; };

int main() {
    key_t clave = 1234;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    struct mensaje msg;

    if (id_cola == -1) { perror("msgget"); exit(1); }

    if (msgrcv(id_cola, &msg, sizeof(msg.texto), 1, 0) == -1) {
        perror("msgrcv"); exit(1);
    }
    printf("Mensaje recibido: %s\n", msg.texto);
    return 0;
}
