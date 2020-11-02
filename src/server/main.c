#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "communication.h"
#include "connection.h"

void *recv_msg_handler(void *arguments);
int players_connected(struct arg_struct* arg_struct);
void message_handler(char* message, int socket_number, struct arg_struct* arg_struct);

int main(int argc, char *argv[])
{
  if (argc != 5)
  {
    printf("Uso: %s -i <ip_address> -p <tcp_port>\n", argv[0]);
    return EXIT_FAILURE;
  }
  signal(SIGPIPE, SIG_IGN); // que vola esta cosa
  char *IP = argv[2];
  int PORT = atoi(argv[4]);
  printf("hola, soy server\n");

  PlayersInfo *sockets_clients = malloc(sizeof(PlayersInfo));

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
  struct thread_struct args_th_1;
  struct thread_struct args_th_2;
  struct thread_struct args_th_3;
  struct thread_struct args_th_4;
  struct thread_struct args_th_5;
  struct thread_struct args_th_6;
  struct thread_struct args_th_7;
  struct thread_struct args_th_8;

  args.IP = IP;     //CAMBIAR POR ARGVS QUE RECIBE
  args.PORT = PORT; //CAMBIAR POR ARGVS QUE RECIBE
  args.sockets_clients = sockets_clients;
  args.playing = 0; //partida no se ha iniciado
  args.exit = 1;  //1 es que no se ha salido de la partida

  args_th_1.socket_number = 1;
  args_th_1.socket_id = &args.sockets_clients->socket[0];
  args_th_1.arg_pointer = &args;
  args_th_2.socket_number = 2;
  args_th_2.socket_id = &args.sockets_clients->socket[1];
  args_th_2.arg_pointer = &args;
  args_th_3.socket_number = 3;
  args_th_3.socket_id = &args.sockets_clients->socket[2];
  args_th_3.arg_pointer = &args;
  args_th_4.socket_number = 4;
  args_th_4.socket_id = &args.sockets_clients->socket[3];
  args_th_4.arg_pointer = &args;
  args_th_5.socket_number = 5;
  args_th_5.socket_id = &args.sockets_clients->socket[4];
  args_th_5.arg_pointer = &args;
  args_th_6.socket_number = 6;
  args_th_6.socket_id = &args.sockets_clients->socket[5];
  args_th_6.arg_pointer = &args;
  args_th_7.socket_number = 7;
  args_th_7.socket_id = &args.sockets_clients->socket[6];
  args_th_7.arg_pointer = &args;
  args_th_8.socket_number = 8;
  args_th_8.socket_id = &args.sockets_clients->socket[7];
  args_th_8.arg_pointer = &args;


  pthread_create(&thread_id, NULL, prepare_sockets_and_get_clients, (void *)&args);

  pthread_create(&thread_id_socket_c1, NULL, recv_msg_handler, (void *)&args_th_1);
  pthread_create(&thread_id_socket_c2, NULL, recv_msg_handler, (void *)&args_th_2);
  pthread_create(&thread_id_socket_c3, NULL, recv_msg_handler, (void *)&args_th_3);
  pthread_create(&thread_id_socket_c4, NULL, recv_msg_handler, (void *)&args_th_4);
  pthread_create(&thread_id_socket_c5, NULL, recv_msg_handler, (void *)&args_th_5);
  pthread_create(&thread_id_socket_c6, NULL, recv_msg_handler, (void *)&args_th_6);
  pthread_create(&thread_id_socket_c7, NULL, recv_msg_handler, (void *)&args_th_7);
  pthread_create(&thread_id_socket_c8, NULL, recv_msg_handler, (void *)&args_th_8);

  while (args.exit)
  {
    sleep(1);
  }

  printf("Se ha cerrado el juego.\n");
  free(sockets_clients);
  return 0;
}

void *recv_msg_handler(void *arguments)
{
  char colors[8][9] = { "rojo", "naranja", "amarillo", "verde", "celeste", "azul", "violeta", "rosado" };
  struct thread_struct *args = (struct thread_struct *)arguments;
  while (1)
  {
    while (*args->socket_id == 0)
    {
      //ARREGLAR BUSY WAITING X OTRO WAITING
      sleep(1);
    }
    //int msg_code = 1;
    while (1)
    {
      //FALTA: manejo cuando socket se cierra//
      int msg_code = server_receive_id(*args->socket_id);
      if (msg_code == 0)
      {
        //Ejecutar exit
        break;
      }
      char *client_message = server_receive_payload(*args->socket_id);
      printf("El cliente %d dice: %s\n", args->socket_number, client_message);
      message_handler(client_message, args->socket_number, args->arg_pointer);
      free(client_message);
    }
    *args->socket_id = 0;
    char message_string[36];
    char players_string[29];
    int number_players_connected = 0;
    for (int i = 0; i < 8; i++){
      if (args->arg_pointer->sockets_clients->socket[i] != 0){
        number_players_connected++;
      }
    }
    sprintf(message_string, "Se desconectó el jugador %s.", colors[args->socket_number-1]);
    sprintf(players_string, "Hay %i jugador/es en la sala.", number_players_connected);
    printf("%s\n", message_string);
    for (int i = 0; i < 8; i++){
      if (args->arg_pointer->sockets_clients->socket[i] != 0){
        server_send_message(args->arg_pointer->sockets_clients->socket[i], 1, message_string);
        server_send_message(args->arg_pointer->sockets_clients->socket[i], 1, players_string);
      }
    }
  }
  return NULL;
}

int players_connected(struct arg_struct* arg_struct){
  int number_players_connected = 0;
  for (int i = 0; i < 8; i++){
    if (arg_struct->sockets_clients->socket[i] != 0){
      number_players_connected++;
    }
  }
  return number_players_connected;
} 

void message_handler(char* message, int socket_number, struct arg_struct* arg_struct){
  char colors[8][9] = { "rojo", "naranja", "amarillo", "verde", "celeste", "azul", "violeta", "rosado" };
  if (message[0] == '\\'){
    if (strcmp(message, "\\start") == 0){
      int number_players_connected = players_connected(arg_struct);
      //manejo cantidad de impostores
      if (number_players_connected < 3){
        printf("No se puede\n");
        char* message_response = "Se requiere un minimo de 3 jugadores para jugar.";
        server_send_message(arg_struct->sockets_clients->socket[socket_number - 1], 1, message_response);
      }
      else {
        arg_struct->playing = 1;
      }
    }
    else if (strcmp(message, "\\exit") == 0){
      
    }
    else if (strcmp(message, "\\players") == 0){
      int number_players_connected = players_connected(arg_struct);
      
      
      
    }
    else if (strcmp(message, "\\vote") == 0){
      
    }
    else if (strcmp(message, "\\kill") == 0){
      
    }
    else if (strcmp(message, "\\spy") == 0){
      
    }
    else if (strcmp(message, "\\whisper") == 0){
      
    }
    else{
      // manejo de error
    }
  }
  else if (message[0] != '\\'){
    for (int i = 0; i < 8; i++){
      if (arg_struct->sockets_clients->socket[i] != 0){
        server_send_message(arg_struct->sockets_clients->socket[i], socket_number + 1, message);
      }
    }
  }
}
