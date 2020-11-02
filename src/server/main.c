#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "communication.h"
#include "connection.h"

void *recv_msg_handler(void *arguments);
void message_handler(char *message, int socket_number, struct arg_struct *arg_struct);
int players_connected(struct arg_struct *arg_struct);
int* random_numbers(int lower, int upper, int count);

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
  args.exit = 1;    //1 es que no se ha salido de la partida

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
  char colors[8][9] = {"rojo", "naranja", "amarillo", "verde", "celeste", "azul", "violeta", "rosado"};
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
    args->arg_pointer->players[args->socket_number-1].estado = 0;      // 1 = vivo | 2 = expulsado | 3 = eliminado
    args->arg_pointer->players[args->socket_number-1].player_type = 0; // 1 == ruzmate // 2 = impostor
    args->arg_pointer->players[args->socket_number-1].used_spy = 0;    //1 si no se ha usado el spy // 2 si se uso el spy
    args->arg_pointer->players[args->socket_number-1].voto = 0;
    char message_string[36];
    char players_string[29];
    int number_players_connected = players_connected(args->arg_pointer);
    sprintf(message_string, "Se desconectó el jugador %s.", colors[args->socket_number - 1]);
    sprintf(players_string, "Hay %i jugador/es en la sala.", number_players_connected);
    printf("%s\n", message_string);
    for (int i = 0; i < 8; i++)
    {
      if (args->arg_pointer->sockets_clients->socket[i] != 0)
      {
        server_send_message(args->arg_pointer->sockets_clients->socket[i], 1, message_string);
        server_send_message(args->arg_pointer->sockets_clients->socket[i], 1, players_string);
      }
    }
  }
  return NULL;
}

int players_connected(struct arg_struct *arg_struct)
{
  int number_players_connected = 0;
  for (int i = 0; i < 8; i++)
  {
    if (arg_struct->sockets_clients->socket[i] != 0)
    {
      number_players_connected++;
    }
  }
  return number_players_connected;
}

void message_handler(char *message, int socket_number, struct arg_struct *arg_struct)
{
  char colors[8][9] = {"rojo", "naranja", "amarillo", "verde", "celeste", "azul", "violeta", "rosado"};
  char chars_colors[8][9] = {"rojo     ", "naranja  ", "amarillo ", "verde    ", "celeste  ", "azul     ", "violeta  ", "rosado   "};
  if (message[0] == '\\')
  {
    char *message_split = strtok(message, " ");
    if (strcmp(message_split, "\\start") == 0)
    {
      int number_players_connected = players_connected(arg_struct);
      message_split = strtok(NULL, " ");
      if (strcmp(message_split, "1") == 0)
      {
        if (number_players_connected < 3)
        {
          printf("No se puede\n");
          char *message_response = "Se requiere un minimo de 3 jugadores para jugar.";
          server_send_message(arg_struct->sockets_clients->socket[socket_number - 1], 1, message_response);
        }
        else
        {
          arg_struct->playing = 1;
<<<<<<< Updated upstream
          for (int i = 0; i < 8; i++)
          {
            if (arg_struct->sockets_clients->socket[i] != 0)
            {
          char* start_message = "El juego ha comenzado.";
          char* ruzmate_message = "Se te ha asignado ser Ruzmate.";
          char* impostor_message = "Se te ha asignado ser impostor.";
          int* result = random_numbers(1, number_players_connected, 1);
          int count = 0;
          for (int i = 0; i < 8; i++){
            if(arg_struct->sockets_clients->socket[i] != 0){
              count++;
>>>>>>> Stashed changes
              arg_struct->players[i].estado = 1;
              if (result[0] == count){
                arg_struct->players[i].player_type = 2; //o impostor
              }
              else{
                arg_struct->players[i].player_type = 1; //o impostor
              }
              arg_struct->players[i].used_spy = 1;
              arg_struct->players[i].voto = 1;
              server_send_message(arg_struct->sockets_clients->socket[i], 1, start_message);
              if (arg_struct->players[i].player_type == 1){
                server_send_message(arg_struct->sockets_clients->socket[i], 1, ruzmate_message);
              }
              else if (arg_struct->players[i].player_type == 2){
                server_send_message(arg_struct->sockets_clients->socket[i], 1, impostor_message);
              }
            }
          }
          free(result);
        }
      }
      else if (strcmp(message_split, "2") == 0)
      {
        if (number_players_connected < 5)
        {
          printf("No se puede\n");
          char *message_response = "Se requiere un minimo de 5 jugadores para jugar.";
          server_send_message(arg_struct->sockets_clients->socket[socket_number - 1], 1, message_response);
        }
        else
        {
          arg_struct->playing = 1;
<<<<<<< Updated upstream
          for (int i = 0; i < 8; i++)
          {
            if (arg_struct->sockets_clients->socket[i] != 0)
            {
          char* start_message = "El juego ha comenzado.";
          char* ruzmate_message = "Se te ha asignado ser Ruzmate.";
          char* impostor_message = "Se te ha asignado ser impostor.";
          int* result = random_numbers(1, number_players_connected, 2);
          int count = 0;
          int count_2 = 0;
          for (int i = 0; i < 8; i++){
            if(arg_struct->sockets_clients->socket[i] != 0){
              count++;
>>>>>>> Stashed changes
              arg_struct->players[i].estado = 1;
              if (result[count_2] == count){
                arg_struct->players[i].player_type = 2; //o impostor
                count_2++;
              }
              else{
                arg_struct->players[i].player_type = 1; //o impostor
              }
              arg_struct->players[i].used_spy = 1;
              arg_struct->players[i].voto = 1;
              server_send_message(arg_struct->sockets_clients->socket[i], 1, start_message);
              if (arg_struct->players[i].player_type == 1){
                server_send_message(arg_struct->sockets_clients->socket[i], 1, ruzmate_message);
              }
              else if (arg_struct->players[i].player_type == 2){
                server_send_message(arg_struct->sockets_clients->socket[i], 1, impostor_message);
              }
            }
          }
          free(result);
        }
      }
    }
    else if (strcmp(message, "\\exit") == 0)
    {
      close(arg_struct->sockets_clients->socket[socket_number - 1]);
      arg_struct->sockets_clients->socket[socket_number - 1] = 0;
      // FALTA:  Verificar si se logran los objetivos
    }
    else if (strcmp(message, "\\players") == 0)
    {
      //int number_players_connected = players_connected(arg_struct);
      //char * tabla[11 + 15*number_players_connected];
      //tabla = }
      char *header = "TABLA JUGADORES:";
      server_send_message(arg_struct->sockets_clients->socket[socket_number - 1], 1, header);
      char jugador[45];
      char *color;
      for (int i = 0; i < 8; i++)
      {

        if (arg_struct->sockets_clients->socket[i] != 0)
        {
          jugador[44] = '\0';
          jugador[0] = chars_colors[i][0];
          jugador[1] = chars_colors[i][1];
          jugador[2] = chars_colors[i][2];
          jugador[3] = chars_colors[i][3];
          jugador[4] = chars_colors[i][4];
          jugador[5] = chars_colors[i][5];
          jugador[6] = chars_colors[i][6];
          jugador[7] = chars_colors[i][7];
          jugador[8] = chars_colors[i][8];
          jugador[9] = ' ';

          color = colors[i];

          printf("color: %s\n", jugador);

          jugador[10] = 'e';
          jugador[11] = 's';
          jugador[12] = 't';
          jugador[13] = 'a';
          jugador[14] = 'd';
          jugador[15] = 'o';
          jugador[16] = ':';
          jugador[17] = ' ';

          char *estado = "estado: ";
          // para saber el estado
          arg_struct->players[i].estado = 1;
          if (arg_struct->players[i].estado == 0) // Vivo
          {
            jugador[18] = 'V';
            jugador[19] = 'I';
            jugador[20] = 'V';
            jugador[21] = 'O';
            jugador[22] = ' ';
            jugador[23] = ' ';
            jugador[24] = ' ';
            jugador[25] = ' ';
            jugador[26] = ' ';
            jugador[27] = ' ';

            char *vivo = "VIVO";
            char *loquequeda;
            //printf("####estado: %s, %p\n", estado, &estado);
            //printf("####vivo: %s, %p\n", vivo, &vivo);
            //loquequeda = strcat(estado, vivo);
            //printf("loquequeda: %s\n", loquequeda);
          }
          else if (arg_struct->players[i].estado == 1) // expulsado
          {
            jugador[18] = 'E';
            jugador[19] = 'X';
            jugador[20] = 'P';
            jugador[21] = 'U';
            jugador[22] = 'L';
            jugador[23] = 'S';
            jugador[24] = 'A';
            jugador[25] = 'D';
            jugador[26] = 'O';
            jugador[27] = ' ';

            char *expulsado = "EXPULSADO";
            //strcat(estado, expulsado);
          }
          else if (arg_struct->players[i].estado == 1) // eLIMINADO
          {
            jugador[18] = 'E';
            jugador[19] = 'L';
            jugador[20] = 'I';
            jugador[21] = 'M';
            jugador[22] = 'I';
            jugador[23] = 'N';
            jugador[24] = 'A';
            jugador[25] = 'D';
            jugador[26] = 'O';
            jugador[27] = ' ';

            //strcat(estado, "ELIMINADO");
          }
          // voto
          jugador[28] = 'v';
          jugador[29] = 'o';
          jugador[30] = 't';
          jugador[31] = 'o';
          jugador[32] = ':';
          jugador[33] = ' ';

          char *voto = "voto:";

          // si está vivo
          arg_struct->players[i]
              .voto = 2;
          if (arg_struct->players[i].estado == 0)
          {
            // el jugador por el que votó va a estar guardado como int en el struct players
            jugador[34] = chars_colors[arg_struct->players[i].voto][0];
            jugador[35] = chars_colors[arg_struct->players[i].voto][1];
            jugador[36] = chars_colors[arg_struct->players[i].voto][2];
            jugador[37] = chars_colors[arg_struct->players[i].voto][3];
            jugador[38] = chars_colors[arg_struct->players[i].voto][4];
            jugador[39] = chars_colors[arg_struct->players[i].voto][5];
            jugador[40] = chars_colors[arg_struct->players[i].voto][6];
            jugador[41] = chars_colors[arg_struct->players[i].voto][7];
            jugador[42] = chars_colors[arg_struct->players[i].voto][8];
            jugador[43] = ' ';

            //strcat(voto, colors[i]);
          }
          // si ya no sigue jugando:
          else if (arg_struct->players[i].estado != 0)
          {
            jugador[34] = '-';
            jugador[35] = '-';
            jugador[36] = '-';
            jugador[37] = '-';
            jugador[38] = '-';
            jugador[39] = '-';
            jugador[40] = '-';
            jugador[41] = '-';
            jugador[42] = '-';
            jugador[43] = ' ';

            //strcat(voto, "---------");
          }
          for (int i = 0; i < 45; i++)
          {
            printf("%c", jugador[i]);
          }
          printf("\n");
          printf("%s\n", jugador);
          //printf('jugador completo: %s\n', jugador);
          //char *jugador2 = " ";
          //strcat(jugador2, color);
          //strcat(jugador2, estado);
          //strcat(jugador2, voto);
          server_send_message(arg_struct->sockets_clients->socket[socket_number - 1], 1, jugador);
        }
      }
    }
    else if (strcmp(message_split, "\\vote") == 0)
    {
      message_split = strtok(NULL, " ");
    }
    else if (strcmp(message_split, "\\kill") == 0)
    {
      message_split = strtok(NULL, " ");
    }
    else if (strcmp(message_split, "\\spy") == 0)
    {
      printf("Entro SPY\n");
      message_split = strtok(NULL, " ");
      int result = 0;
      for (int i = 0; i < 8; i++)
      {
        if (message_split != NULL)
        {
          if (strcmp(colors[i], message_split) == 0)
          {
            result++;
          }
        }
      }
      if (result == 0)
      {
        char *response = "El jugador indicado no existe.";
        server_send_message(arg_struct->sockets_clients->socket[socket_number - 1], 1, response);
      }
      printf("Se desea espiar al jugador %i\n", result);
    }

    else if (strcmp(message_split, "\\whisper") == 0)
    {
      printf("Entro whisper\n");
      message_split = strtok(NULL, " ");
      int result = 0;
      for (int i = 0; i < 8; i++)
      {
        if (message_split != NULL)
        {
          if (strcmp(colors[i], message_split) == 0)
          {
            result++;
            message_split = strtok(NULL, "\0");
            if (message_split == NULL)
            {
              char *warning = "WARNING: Tiene que escribir un mensaje para realizar el comando WHISPER";
              server_send_message(arg_struct->sockets_clients->socket[socket_number - 1], 1, warning);
            }
            else
            {
              server_send_message(arg_struct->sockets_clients->socket[socket_number - 1], 1, message_split);
              server_send_message(arg_struct->sockets_clients->socket[i], socket_number + 1, message_split);
            }
          }
        }
      }
      if (result == 0)
      {
        char *response = "El jugador indicado no existe.";
        server_send_message(arg_struct->sockets_clients->socket[socket_number - 1], 1, response);
      }
    }
    else
    {
      // manejo de error
    }
  }
  else if (message[0] != '\\')
  {
    for (int i = 0; i < 8; i++)
    {
      if (arg_struct->sockets_clients->socket[i] != 0)
      {
        server_send_message(arg_struct->sockets_clients->socket[i], socket_number + 1, message);
      }
    }
  }
}

int* random_numbers(int lower, int upper, int count){
  int* result = malloc(count*sizeof(int));
  int contador = 0;
  for (int i = 0; i < count; i++) {
    int num = (rand() % (upper - lower + 1)) + lower;
    result[i] = num;
  }
  return result;
}
