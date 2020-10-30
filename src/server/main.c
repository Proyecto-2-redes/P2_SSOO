#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "communication.h"
#include "conection.h"


int main(int argc, char* argv[]) {
    printf("hola, soy server\n");
    char * IP = "0.0.0.0"; //CAMBIAR POR ARGVS QUE RECIBE
    int PORT = 8080; //CAMBIAR POR ARGVS QUE RECIBE

    PlayersInfo* sockets_clients = malloc(sizeof(PlayersInfo));

    pthread_t thread_id;

    struct arg_struct args;
    args.IP = IP; //CAMBIAR POR ARGVS QUE RECIBE
    args.PORT = PORT; //CAMBIAR POR ARGVS QUE RECIBE
    args.sockets_clients = sockets_clients;

    pthread_create(&thread_id, NULL, prepare_sockets_and_get_clients, (void *)&args);

    while (1){
      // Se obtiene el paquete del cliente 1
      //int msg_code = server_receive_id(sockets_array[my_attention]);

      //char * client_message = server_receive_payload(sockets_array[my_attention]);
      //printf("El cliente %d dice: %s\n", my_attention+1, client_message);

      // Le enviaremos el mismo mensaje invertido jeje
      //char * response = "El servidor recibio el mensaje.\n";

      // Le enviamos la respuesta
      //server_send_message(sockets_array[my_attention], 1, response);
    }
    free(sockets_clients);
    return 0;
}
