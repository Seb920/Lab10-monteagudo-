#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje {
    long mtype;
    char texto[100];
};

int main() {
    key_t clave = 1234;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    if (id_cola == -1) {
        perror("Error al crear u obtener la cola");
        exit(1);
    }
    printf("Cola creada con ID: %d\n", id_cola);

    struct mensaje msg;

    msg.mtype = 1;
    strcpy(msg.texto, "Hola, soy un mensaje de informacion");
    msgsnd(id_cola, &msg, sizeof(msg.texto), 0);
    printf("Enviado [tipo 1]: %s\n", msg.texto);

    msg.mtype = 2;
    strcpy(msg.texto, "Atencion, uso de memoria alto");
    msgsnd(id_cola, &msg, sizeof(msg.texto), 0);
    printf("Enviado [tipo 2]: %s\n", msg.texto);

    msg.mtype = 3;
    strcpy(msg.texto, "Error critico en el sistema");
    msgsnd(id_cola, &msg, sizeof(msg.texto), 0);
    printf("Enviado [tipo 3]: %s\n", msg.texto);

    printf("\n--- Recibiendo mensajes ---\n");

    msgrcv(id_cola, &msg, sizeof(msg.texto), 1, 0);
    printf("[INFO] %s\n", msg.texto);

    msgrcv(id_cola, &msg, sizeof(msg.texto), 2, 0);
    printf("[ADVERTENCIA] %s\n", msg.texto);

    msgrcv(id_cola, &msg, sizeof(msg.texto), 3, 0);
    printf("[CRITICO] %s\n", msg.texto);

    msgctl(id_cola, IPC_RMID, NULL);
    printf("\nCola eliminada correctamente.\n");

    return 0;
}