#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje { long mtype; char texto[100]; };

int main() {
    key_t clave = 5555;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    struct mensaje msg;

    if (id_cola == -1) { perror("msgget"); exit(1); }

    msg.mtype = 1; strcpy(msg.texto, "Info: sistema estable");
    msgsnd(id_cola, &msg, sizeof(msg.texto), 0);

    msg.mtype = 2; strcpy(msg.texto, "Advertencia: disco al 75%");
    msgsnd(id_cola, &msg, sizeof(msg.texto), 0);

    msg.mtype = 3; strcpy(msg.texto, "CRITICO: fallo en kernel");
    msgsnd(id_cola, &msg, sizeof(msg.texto), 0);

    printf("Mensajes tipo 1, 2 y 3 enviados.\n");
    return 0;
}
