#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje { long mtype; char texto[100]; };

int main() {
    key_t clave = 1234;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    struct mensaje msg;

    if (id_cola == -1) { perror("msgget"); exit(1); }

    msg.mtype = 1;
    printf("Ingrese un mensaje: ");
    fgets(msg.texto, sizeof(msg.texto), stdin);

    if (msgsnd(id_cola, &msg, sizeof(msg.texto), 0) == -1) {
        perror("msgsnd"); exit(1);
    }
    printf("Mensaje enviado correctamente.\n");
    return 0;
}
