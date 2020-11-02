#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "communication.h"
#include "connection.h"

void *recv_msg_handler_c1(void *arguments);
void *recv_msg_handler_c2(void *arguments);
void *recv_msg_handler_c3(void *arguments);
void *recv_msg_handler_c4(void *arguments);
void *recv_msg_handler_c5(void *arguments);
void *recv_msg_handler_c6(void *arguments);
void *recv_msg_handler_c7(void *arguments);
void *recv_msg_handler_c8(void *arguments);

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

  args.IP = IP;     //CAMBIAR POR ARGVS QUE RECIBE
  args.PORT = PORT; //CAMBIAR POR ARGVS QUE RECIBE
  args.sockets_clients = sockets_clients;
  args.playing = 0; //partida no se ha iniciado
  args.exit = 1;  //1 es que no se ha salido de la partida

  pthread_create(&thread_id, NULL, prepare_sockets_and_get_clients, (void *)&args);
  pthread_create(&thread_id_socket_c1, NULL, recv_msg_handler_c1, (void *)&args);
  pthread_create(&thread_id_socket_c2, NULL, recv_msg_handler_c2, (void *)&args);
  pthread_create(&thread_id_socket_c3, NULL, recv_msg_handler_c3, (void *)&args);
  pthread_create(&thread_id_socket_c4, NULL, recv_msg_handler_c4, (void *)&args);
  pthread_create(&thread_id_socket_c5, NULL, recv_msg_handler_c5, (void *)&args);
  pthread_create(&thread_id_socket_c6, NULL, recv_msg_handler_c6, (void *)&args);
  pthread_create(&thread_id_socket_c7, NULL, recv_msg_handler_c7, (void *)&args);
  pthread_create(&thread_id_socket_c8, NULL, recv_msg_handler_c8, (void *)&args);

  while (args.exit)
  {
    sleep(1);
  }

  printf("Se ha cerrado el juego.\n");
  free(sockets_clients);
  return 0;
}

void *recv_msg_handler_c1(void *arguments)
{
  struct arg_struct *args = (struct arg_struct *)arguments;
  while (1)
  {
    while (args->sockets_clients->socket[0] == 0)
    {
      //ARREGLAR BUSY WAITING X OTRO WAITING
      sleep(1);
    }
    //int msg_code = 1;
    while (1)
    {
      //FALTA: manejo cuando socket se cierra//
      int msg_code = server_receive_id(args->sockets_clients->socket[0]);
      if (msg_code == 0)
      {
        //Ejecutar exit
        break;
      }
      char *client_message = server_receive_payload(args->sockets_clients->socket[0]);
      printf("El cliente %d dice: %s\n", 1, client_message);
      free(client_message);
    }
    args->sockets_clients->socket[0] = 0;
    printf("Se desconecto 1\n");
    //Se seconexto cliente 1
  }
  return NULL;
}

void *recv_msg_handler_c2(void *arguments)
{
  struct arg_struct *args = (struct arg_struct *)arguments;
  while (1)
  {
    while (args->sockets_clients->socket[1] == 0)
    {
      //ARREGLAR BUSY WAITING X OTRO WAITING
      sleep(1);
    }
    //int msg_code = 1;
    while (1)
    {
      //FALTA: manejo cuando socket se cierra//
      int msg_code = server_receive_id(args->sockets_clients->socket[1]);
      if (msg_code == 0)
      {
        //Ejecutar exit
        break;
      }
      char *client_message = server_receive_payload(args->sockets_clients->socket[1]);
      printf("El cliente %d dice: %s\n", 2, client_message);
      free(client_message);
    }
    args->sockets_clients->socket[1] = 0;
    printf("Se desconecto 2\n");
    //Se seconexto cliente 1
  }
  return NULL;
}

void *recv_msg_handler_c3(void *arguments)
{
  struct arg_struct *args = (struct arg_struct *)arguments;
  while (1)
  {
    while (args->sockets_clients->socket[2] == 0)
    {
      //ARREGLAR BUSY WAITING X OTRO WAITING
      sleep(1);
    }
    //int msg_code = 1;
    while (1)
    {
      //FALTA: manejo cuando socket se cierra//
      int msg_code = server_receive_id(args->sockets_clients->socket[2]);
      if (msg_code == 0)
      {
        //Ejecutar exit
        break;
      }
      char *client_message = server_receive_payload(args->sockets_clients->socket[2]);
      printf("El cliente %d dice: %s\n", 3, client_message);
      free(client_message);
    }
    args->sockets_clients->socket[2] = 0;
    printf("Se desconecto 3\n");
    //Se seconexto cliente 1
  }
  return NULL;
}

void *recv_msg_handler_c4(void *arguments)
{
  struct arg_struct *args = (struct arg_struct *)arguments;
  while (1)
  {
    while (args->sockets_clients->socket[3] == 0)
    {
      //ARREGLAR BUSY WAITING X OTRO WAITING
      sleep(1);
    }
    //int msg_code = 1;
    while (1)
    {
      //FALTA: manejo cuando socket se cierra//
      int msg_code = server_receive_id(args->sockets_clients->socket[3]);
      if (msg_code == 0)
      {
        //Ejecutar exit
        break;
      }
      char *client_message = server_receive_payload(args->sockets_clients->socket[3]);
      printf("El cliente %d dice: %s\n", 4, client_message);
      free(client_message);
    }
    args->sockets_clients->socket[3] = 0;
    printf("Se desconecto 4\n");
    //Se seconexto cliente 1
  }
  return NULL;
}

void *recv_msg_handler_c5(void *arguments)
{
  struct arg_struct *args = (struct arg_struct *)arguments;
  while (1)
  {
    while (args->sockets_clients->socket[4] == 0)
    {
      //ARREGLAR BUSY WAITING X OTRO WAITING
      sleep(1);
    }
    //int msg_code = 1;
    while (1)
    {
      //FALTA: manejo cuando socket se cierra//
      int msg_code = server_receive_id(args->sockets_clients->socket[4]);
      if (msg_code == 0)
      {
        //Ejecutar exit
        break;
      }
      char *client_message = server_receive_payload(args->sockets_clients->socket[4]);
      printf("El cliente %d dice: %s\n", 5, client_message);
      free(client_message);
    }
    args->sockets_clients->socket[4] = 0;
    printf("Se desconecto 5\n");
    //Se seconexto cliente 1
  }
  return NULL;
}

void *recv_msg_handler_c6(void *arguments)
{
  struct arg_struct *args = (struct arg_struct *)arguments;
  while (1)
  {
    while (args->sockets_clients->socket[5] == 0)
    {
      //ARREGLAR BUSY WAITING X OTRO WAITING
      sleep(1);
    }
    //int msg_code = 1;
    while (1)
    {
      //FALTA: manejo cuando socket se cierra//
      int msg_code = server_receive_id(args->sockets_clients->socket[5]);
      if (msg_code == 0)
      {
        //Ejecutar exit
        break;
      }
      char *client_message = server_receive_payload(args->sockets_clients->socket[5]);
      printf("El cliente %d dice: %s\n", 6, client_message);
      free(client_message);
    }
    args->sockets_clients->socket[5] = 0;
    printf("Se desconecto 6\n");
    //Se seconexto cliente 1
  }
  return NULL;
}

void *recv_msg_handler_c7(void *arguments)
{
  struct arg_struct *args = (struct arg_struct *)arguments;
  while (1)
  {
    while (args->sockets_clients->socket[6] == 0)
    {
      //ARREGLAR BUSY WAITING X OTRO WAITING
      sleep(1);
    }
    //int msg_code = 1;
    while (1)
    {
      //FALTA: manejo cuando socket se cierra//
      int msg_code = server_receive_id(args->sockets_clients->socket[6]);
      if (msg_code == 0)
      {
        //Ejecutar exit
        break;
      }
      char *client_message = server_receive_payload(args->sockets_clients->socket[6]);
      printf("El cliente %d dice: %s\n", 7, client_message);
      free(client_message);
    }
    args->sockets_clients->socket[6] = 0;
    printf("Se desconecto 7\n");
    //Se seconexto cliente 1
  }
  return NULL;
}

void *recv_msg_handler_c8(void *arguments)
{
  struct arg_struct *args = (struct arg_struct *)arguments;
  while (1)
  {
    while (args->sockets_clients->socket[7] == 0)
    {
      //ARREGLAR BUSY WAITING X OTRO WAITING
      sleep(1);
    }
    //int msg_code = 1;
    while (1)
    {
      //FALTA: manejo cuando socket se cierra//
      int msg_code = server_receive_id(args->sockets_clients->socket[7]);
      if (msg_code == 0)
      {
        //Ejecutar exit
        break;
      }
      char *client_message = server_receive_payload(args->sockets_clients->socket[7]);
      printf("El cliente %d dice: %s\n", 8, client_message);
      free(client_message);
    }
    args->sockets_clients->socket[7] = 0;
    printf("Se desconecto 8\n");
    //Se seconexto cliente 1
  }
  return NULL;
}
