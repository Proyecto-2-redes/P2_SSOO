#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "communication.h"
#include "conection.h"

void* recv_msg_handler_c1(void *arguments);

int main(int argc, char* argv[]) {
    printf("hola, soy server\n");
    char * IP = "0.0.0.0"; //CAMBIAR POR ARGVS QUE RECIBE
    int PORT = 8080; //CAMBIAR POR ARGVS QUE RECIBE

    PlayersInfo* sockets_clients = malloc(sizeof(PlayersInfo));

    pthread_t thread_id;
    pthread_t thread_id_socket_c1;
    pthread_t thread_id_socket_c2;
    pthread_t thread_id_socket_c3;

    struct arg_struct args;
    args.IP = IP; //CAMBIAR POR ARGVS QUE RECIBE
    args.PORT = PORT; //CAMBIAR POR ARGVS QUE RECIBE
    args.sockets_clients = sockets_clients;

    pthread_create(&thread_id, NULL, prepare_sockets_and_get_clients, (void *)&args);
    pthread_create(&thread_id_socket_c1, NULL, recv_msg_handler_c1, (void *)&args);
    while(1){
      sleep(1);
    }

    free(sockets_clients);
    return 0;
}


void* recv_msg_handler_c1(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  while(args->sockets_clients->socket_c1 == 0){
    sleep(1);
  }
  while(1){
    int msg_code = server_receive_id(args->sockets_clients->socket_c1);
    char* client_message = server_receive_payload(args->sockets_clients->socket_c1);
    printf("El cliente %d dice: %s\n", 1, client_message);
  }
}
