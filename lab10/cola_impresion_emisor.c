#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje { long mtype; char texto[150]; };

int main() {
    key_t clave = 2222;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    struct mensaje msg;

    if (id_cola == -1) { perror("msgget"); exit(1); }

    char *solicitudes[] = {
        "Documento: informe.pdf - Paginas: 10",
        "Documento: tesis.pdf - Paginas: 85",
        "Documento: carta.pdf - Paginas: 2",
    };

    for (int i = 0; i < 3; i++) {
        msg.mtype = 1;
        strcpy(msg.texto, solicitudes[i]);
        msgsnd(id_cola, &msg, sizeof(msg.texto), 0);
        printf("Enviado: %s\n", msg.texto);
    }
    return 0;
}
