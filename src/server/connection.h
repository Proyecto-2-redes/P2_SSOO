#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "communication.h"


typedef struct players_info {
    int socket[8];
} PlayersInfo;

struct arg_struct {  ///struct_principal
    char* IP;
    int PORT;
    PlayersInfo* sockets_clients;
    int playing; //si se inicia o no la partida
    int exit; //si alguien hizo exit o no
};

struct thread_struct {
  int* socket_id;
  int socket_number;
  struct arg_struct* arg_pointer;
};


void* prepare_sockets_and_get_clients(void *arguments);

void message_initial(int player_number, struct arg_struct* arguments, char colors[8][9]);

int number_players_connected (struct arg_struct* arguments);
