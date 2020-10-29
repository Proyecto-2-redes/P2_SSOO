#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "communication.h"
#include "conection.h"

int main(int argc, char* argv[]) {
    printf("hola, soy server\n");
    char * IP = "0.0.0.0";
    int PORT = 8080;

    PlayersInfo * players_info = prepare_sockets_and_get_clients(IP, PORT);
    char * welcome = "Bienvenido Cliente 1!!";
    server_send_message(players_info->socket_c1, 1, welcome);


    int sockets_array[8] = {players_info->socket_c1, players_info->socket_c2,
                            players_info->socket_c3, players_info->socket_c4,
                            players_info->socket_c5, players_info->socket_c6,
                            players_info->socket_c7, players_info->socket_c8};
    int my_attention = 0;
    while (1){
      // Se obtiene el paquete del cliente 1
      int msg_code = server_receive_id(sockets_array[my_attention]);

      char * client_message = server_receive_payload(sockets_array[my_attention]);
      printf("El cliente %d dice: %s\n", my_attention+1, client_message);

      // Le enviaremos el mismo mensaje invertido jeje
      char * response = "El servidor recibio el mensaje.\n";

      // Le enviamos la respuesta
      server_send_message(sockets_array[my_attention], 1, response);
    }
    return 0;
}
