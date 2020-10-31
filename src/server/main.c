#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "communication.h"
#include "conection.h"

void* recv_msg_handler_c1(void *arguments);
void* recv_msg_handler_c2(void *arguments);
void* recv_msg_handler_c3(void *arguments);
void* recv_msg_handler_c4(void *arguments);
void* recv_msg_handler_c5(void *arguments);
void* recv_msg_handler_c6(void *arguments);
void* recv_msg_handler_c7(void *arguments);
void* recv_msg_handler_c8(void *arguments);

int main(int argc, char* argv[]) {
    printf("hola, soy server\n");
    char * IP = "0.0.0.0"; //CAMBIAR POR ARGVS QUE RECIBE
    int PORT = 8080; //CAMBIAR POR ARGVS QUE RECIBE

    PlayersInfo* sockets_clients = malloc(sizeof(PlayersInfo));

    pthread_t thread_id;
    pthread_t thread_id_socket_c1;
    pthread_t thread_id_socket_c2;
    pthread_t thread_id_socket_c3;
    pthread_t thread_id_socket_c4;
    pthread_t thread_id_socket_c5;
    pthread_t thread_id_socket_c6;
    pthread_t thread_id_socket_c7;
    pthread_t thread_id_socket_c8;

    struct arg_struct args;

    args.IP = IP; //CAMBIAR POR ARGVS QUE RECIBE
    args.PORT = PORT; //CAMBIAR POR ARGVS QUE RECIBE
    args.sockets_clients = sockets_clients;
    args.start = 0; //partida no se ha iniciado
    args.exit = 1; //1 es que no se ha salido de la partida

    pthread_create(&thread_id, NULL, prepare_sockets_and_get_clients, (void *)&args);
    pthread_create(&thread_id_socket_c1, NULL, recv_msg_handler_c1, (void *)&args);
    pthread_create(&thread_id_socket_c2, NULL, recv_msg_handler_c2, (void *)&args);
    pthread_create(&thread_id_socket_c3, NULL, recv_msg_handler_c3, (void *)&args);
    pthread_create(&thread_id_socket_c4, NULL, recv_msg_handler_c4, (void *)&args);
    pthread_create(&thread_id_socket_c5, NULL, recv_msg_handler_c5, (void *)&args);
    pthread_create(&thread_id_socket_c6, NULL, recv_msg_handler_c6, (void *)&args);
    pthread_create(&thread_id_socket_c7, NULL, recv_msg_handler_c7, (void *)&args);
    pthread_create(&thread_id_socket_c8, NULL, recv_msg_handler_c8, (void *)&args);

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

void* recv_msg_handler_c2(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  while(args->sockets_clients->socket_c2 == 0){
    sleep(1);
  }
  while(1){
    int msg_code = server_receive_id(args->sockets_clients->socket_c2);
    char* client_message = server_receive_payload(args->sockets_clients->socket_c2);
    printf("El cliente %d dice: %s\n", 2, client_message);
  }
}

void* recv_msg_handler_c3(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  while(args->sockets_clients->socket_c3 == 0){
    sleep(1);
  }
  while(1){
    int msg_code = server_receive_id(args->sockets_clients->socket_c3);
    char* client_message = server_receive_payload(args->sockets_clients->socket_c3);
    printf("El cliente %d dice: %s\n", 3, client_message);
  }
}

void* recv_msg_handler_c4(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  while(args->sockets_clients->socket_c4 == 0){
    sleep(1);
  }
  while(1){
    int msg_code = server_receive_id(args->sockets_clients->socket_c4);
    char* client_message = server_receive_payload(args->sockets_clients->socket_c4);
    printf("El cliente %d dice: %s\n", 4, client_message);
  }
}

void* recv_msg_handler_c5(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  while(args->sockets_clients->socket_c5 == 0){
    sleep(1);
  }
  while(1){
    int msg_code = server_receive_id(args->sockets_clients->socket_c5);
    char* client_message = server_receive_payload(args->sockets_clients->socket_c5);
    printf("El cliente %d dice: %s\n", 5, client_message);
  }
}

void* recv_msg_handler_c6(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  while(args->sockets_clients->socket_c6 == 0){
    sleep(1);
  }
  while(1){
    int msg_code = server_receive_id(args->sockets_clients->socket_c6);
    char* client_message = server_receive_payload(args->sockets_clients->socket_c6);
    printf("El cliente %d dice: %s\n", 6, client_message);
  }
}

void* recv_msg_handler_c7(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  while(args->sockets_clients->socket_c7 == 0){
    sleep(1);
  }
  while(1){
    int msg_code = server_receive_id(args->sockets_clients->socket_c7);
    char* client_message = server_receive_payload(args->sockets_clients->socket_c7);
    printf("El cliente %d dice: %s\n", 7, client_message);
  }
}

void* recv_msg_handler_c8(void *arguments){
  struct arg_struct *args = (struct arg_struct *)arguments;
  while(args->sockets_clients->socket_c8 == 0){
    sleep(1);
  }
  while(1){
    int msg_code = server_receive_id(args->sockets_clients->socket_c8);
    char* client_message = server_receive_payload(args->sockets_clients->socket_c8);
    printf("El cliente %d dice: %s\n", 8, client_message);
  }
}
