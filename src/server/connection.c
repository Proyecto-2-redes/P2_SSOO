#include "connection.h"
#include "communication.h"

void* prepare_sockets_and_get_clients(void* arguments) {
  struct arg_struct* args = (struct arg_struct*)arguments;
  // Se define la estructura para almacenar info del socket del servidor al momento de su creación
  struct sockaddr_in server_addr;

  // Se solicita un socket al SO, que se usará para escuchar conexiones entrantes
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Se configura el socket a gusto (recomiendo fuertemente el REUSEPORT!)
  int opt = 1;
  int ret = setsockopt(server_socket, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

  // Se guardan el puerto e IP en la estructura antes definida
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  inet_aton(args->IP, &server_addr.sin_addr);
  server_addr.sin_port = htons(args->PORT);

  // Se le asigna al socket del servidor un puerto y una IP donde escuchar
  int ret2 = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

  // Se coloca el socket en modo listening
  int ret3 = listen(server_socket, 1);

  // Se definen las estructuras para almacenar info sobre los sockets de los clientes
  struct sockaddr_in client1_addr;
  struct sockaddr_in client2_addr;
  struct sockaddr_in client3_addr;
  struct sockaddr_in client4_addr;
  struct sockaddr_in client5_addr;
  struct sockaddr_in client6_addr;
  struct sockaddr_in client7_addr;
  struct sockaddr_in client8_addr;
  socklen_t addr_size = sizeof(client1_addr);

  int sockets_array[8];

  char colors[8][9] = { "rojo", "naranja", "amarillo", "verde", "celeste", "azul", "violeta", "rosado" };

  while (args->exit) {
    if (args->sockets_clients->socket_c1 == 0) {
      args->sockets_clients->socket_c1 = accept(server_socket, (struct sockaddr*)&client1_addr, &addr_size);
      sockets_array[0] = args->sockets_clients->socket_c1;
      message_initial(1, sockets_array, colors); //ARREGLAR  UANCOD SE CONECTA OTRO DENUEVO CONEXIION Y DESCONEXXION
      printf("Entro jugador 1\n");
    }

    //if socket == 0 and start == 0//
    if (args->sockets_clients->socket_c2 == 0) {
      args->sockets_clients->socket_c2 = accept(server_socket, (struct sockaddr*)&client2_addr, &addr_size);
      sockets_array[1] = args->sockets_clients->socket_c2;
      message_initial(2, sockets_array, colors);
      printf("Entro jugador 2\n");
    }

    if (args->sockets_clients->socket_c3 == 0) {
      args->sockets_clients->socket_c3 = accept(server_socket, (struct sockaddr*)&client3_addr, &addr_size);
      sockets_array[2] = args->sockets_clients->socket_c3;
      message_initial(3, sockets_array, colors);
      printf("Entro jugador 3\n");
    }

    if (args->sockets_clients->socket_c4 == 0) {
      args->sockets_clients->socket_c4 = accept(server_socket, (struct sockaddr*)&client4_addr, &addr_size);
      sockets_array[3] = args->sockets_clients->socket_c4;
      message_initial(4, sockets_array, colors);
      printf("Entro jugador 4\n");
    }

    if (args->sockets_clients->socket_c5 == 0) {
      args->sockets_clients->socket_c5 = accept(server_socket, (struct sockaddr*)&client5_addr, &addr_size);
      sockets_array[4] = args->sockets_clients->socket_c5;
      message_initial(5, sockets_array, colors);
      printf("Entro jugador 5\n");
    }

    if (args->sockets_clients->socket_c6 == 0) {
      args->sockets_clients->socket_c6 = accept(server_socket, (struct sockaddr*)&client6_addr, &addr_size);
      sockets_array[5] = args->sockets_clients->socket_c6;
      message_initial(6, sockets_array, colors);
      printf("Entro jugador 6\n");
    }

    if (args->sockets_clients->socket_c7 == 0) {
      args->sockets_clients->socket_c7 = accept(server_socket, (struct sockaddr*)&client7_addr, &addr_size);
      sockets_array[6] = args->sockets_clients->socket_c7;
      message_initial(7, sockets_array, colors);
      printf("Entro jugador 7\n");
    }

    if (args->sockets_clients->socket_c8 == 0) {
      args->sockets_clients->socket_c8 = accept(server_socket, (struct sockaddr*)&client8_addr, &addr_size);
      sockets_array[7] = args->sockets_clients->socket_c8;
      message_initial(8, sockets_array, colors);
      printf("Entro jugador 8\n");
    }
  }
  // Se inicializa una estructura propia para guardar los n°s de sockets de los clientes.
  // Se aceptan a los primeros 8 clientes que lleguen. "accept" retorna el n° de otro socket asignado para la comunicación
  return NULL;
}

void message_initial(int player_number, int sockets_array[8], char colors[8][9]) {
  char* welcome = "Bienvenido a Among RUZ!!";
  char color_string[34];
  char message_string[34];
  char players_string[28];
  sprintf(color_string, "Se te asigno el color %s.", colors[player_number - 1]);
  sprintf(message_string, "Se ha unido el jugador %s.", colors[player_number - 1]);
  sprintf(players_string, "Hay %i jugadores en la sala.", player_number); //ASOCIADO AL ELEMNTOS NO 0 SOCKETS_ARRAY;

  server_send_message(sockets_array[player_number - 1], 1, welcome);
  server_send_message(sockets_array[player_number - 1], 1, color_string);
  server_send_message(sockets_array[player_number - 1], 1, players_string);
  for (int i = 0; i < 8; i++) {
    if (sockets_array[i] && i != player_number - 1) {
      server_send_message(sockets_array[i], 1, message_string);
      server_send_message(sockets_array[i], 1, players_string);
    }
  }
}
