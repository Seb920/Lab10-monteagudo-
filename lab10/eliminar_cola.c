#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    key_t clave;
    printf("Ingrese la clave IPC de la cola a eliminar: ");
    scanf("%d", &clave);

    int id_cola = msgget(clave, 0666);
    if (id_cola == -1) {
        perror("msgget: cola no encontrada");
        exit(1);
    }

    printf("Cola encontrada con ID: %d\n", id_cola);

    if (msgctl(id_cola, IPC_RMID, NULL) == -1) {
        perror("msgctl: error al eliminar");
        exit(1);
    }

    printf("Cola eliminada correctamente.\n");
    return 0;
}
