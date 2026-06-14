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

    printf("Tipo 1=Info, 2=Advertencia, 3=Critico: ");
    scanf("%ld", &msg.mtype); getchar();

    printf("Descripcion: ");
    fgets(msg.texto, sizeof(msg.texto), stdin);

    if (msgsnd(id_cola, &msg, sizeof(msg.texto), 0) == -1) {
        perror("msgsnd"); exit(1);
    }
    printf("Evento enviado.\n");
    return 0;
}
