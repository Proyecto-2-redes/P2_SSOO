#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "conection.h"
#include "communication.h"

void* recv_msg_handler(void *arguments);

int main(int argc, char* argv[]) {
    printf("hola, soy client\n");
    char * IP = "0.0.0.0";
    int PORT = 8080;

    // Se prepara el socket
    int server_socket = prepare_socket(IP, PORT);

    struct arg_struct args;
    args.server_socket = server_socket;

    pthread_t recv_msg_thread;
    pthread_t send_msg_thread;

    pthread_create(&recv_msg_thread, NULL, recv_msg_handler, (void *)&args);
    pthread_create(&send_msg_thread, NULL, send_msg_handler, (void *)&args);

    close(server_socket);
    free(IP);
    return 0;
}


void* recv_msg_handler(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  char* message = NULL;
  while(1){
    int msg_code = client_receive_id(args->server_socket);
    message = client_receive_payload(args->server_socket);
    if (msg_code == 1) { //Recibimos un mensaje del servidor
      printf("[SERVIDOR] : %s\n", message);
    }
    else if (msg_code == 2){
      printf("[ROJO]: %s\n", message);
    }
    else if (msg_code == 3){
      printf("[NARANJA]: %s\n", message);
    }
    else if (msg_code == 4){
      printf("[AMARILLO]: %s\n", message);
    }
    else if (msg_code == 5){
      printf("[VERDE]: %s\n", message);
    }
    else if (msg_code == 6){
      printf("[CELESTE]: %s\n", message);
    }
    else if (msg_code == 7){
      printf("[AZUL]: %s\n", message);
    }
    else if (msg_code == 8){
      printf("[VIOLETA]: %s\n", message);
    }
    else if (msg_code == 9){
      printf("[ROSADO]: %s\n", message);
    }
  }
  free(message);
}

void* send_msg_handler(void* arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  char* message = NULL;
  while(1){
    ///Guardar lo que hay en consola y mandarlo//
    //Asignar que color es client//
    client_send_message(args->server_socket, int pkg_id, message)
  }
}
