#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include "communication.h"

struct arg_struct
{
    int server_socket;
    int flag;
};

int prepare_socket(char *IP, int PORT);
