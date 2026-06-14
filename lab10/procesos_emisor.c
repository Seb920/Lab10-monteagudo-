#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje { long mtype; char texto[100]; };

int main() {
    key_t clave = 4444;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    struct mensaje msg;

    if (id_cola == -1) { perror("msgget"); exit(1); }

    msg.mtype = 1; strcpy(msg.texto, "Proceso Apache iniciado");
    msgsnd(id_cola, &msg, sizeof(msg.texto), 0);

    msg.mtype = 2; strcpy(msg.texto, "Proceso MySQL detenido");
    msgsnd(id_cola, &msg, sizeof(msg.texto), 0);

    msg.mtype = 3; strcpy(msg.texto, "Error en proceso de red");
    msgsnd(id_cola, &msg, sizeof(msg.texto), 0);

    printf("Eventos de proceso enviados.\n");
    return 0;
}
