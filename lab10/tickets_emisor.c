#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct mensaje { long mtype; char texto[150]; };

int main() {
    key_t clave = 3333;
    int id_cola = msgget(clave, 0666 | IPC_CREAT);
    struct mensaje msg;

    if (id_cola == -1) { perror("msgget"); exit(1); }

    char *tickets[] = {
        "ID Usuario: 15 - Problema: No puede acceder al sistema",
        "ID Usuario: 22 - Problema: Contrasena olvidada",
        "ID Usuario: 37 - Problema: Error al cargar pagina",
        "ID Usuario: 41 - Problema: Impresora no responde",
        "ID Usuario: 58 - Problema: Correo no llega",
    };

    for (int i = 0; i < 5; i++) {
        msg.mtype = 1;
        strcpy(msg.texto, tickets[i]);
        msgsnd(id_cola, &msg, sizeof(msg.texto), 0);
        printf("Ticket enviado: %s\n", msg.texto);
    }
    return 0;
}
