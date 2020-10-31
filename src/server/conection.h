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
    int socket_c1;
    int socket_c2;
    int socket_c3;
    int socket_c4;
    int socket_c5;
    int socket_c6;
    int socket_c7;
    int socket_c8;
} PlayersInfo;

struct arg_struct {
    char* IP;
    int PORT;
    PlayersInfo* sockets_clients;
    int start; //si se inicia o no la partida
    int exit; //si alguien hizo exit o no
};


void* prepare_sockets_and_get_clients(void *arguments);

void message_initial(int player_number, int sockets_array[8], char colors[8][9]);
