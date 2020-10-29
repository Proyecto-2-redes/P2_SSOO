#include <unistd.h>
#include <stdio.h>
#include "conection.h"
#include "communication.h"

int main(int argc, char* argv[]) {
    printf("hola, soy client\n");
    char * IP = "0.0.0.0";
    int PORT = 8080;

    // Se prepara el socket
    int server_socket = prepare_socket(IP, PORT);


    while(1){
      int msg_code = client_receive_id(server_socket);

      if (msg_code == 1) { //Recibimos un mensaje del servidor
        char * message = client_receive_payload(server_socket);
        printf("[SERVIDOR] : %s\n", message);
        free(message);
      }
    }
    close(server_socket);
    free(IP);
    return 0;
}
