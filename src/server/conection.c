#include "conection.h"
#include "communication.h"

void prepare_sockets_and_get_clients(void *arguments) {
    struct arg_struct *args = (struct arg_struct *)arguments;
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

    // Se inicializa una estructura propia para guardar los n°s de sockets de los clientes.
    // Se aceptan a los primeros 8 clientes que lleguen. "accept" retorna el n° de otro socket asignado para la comunicación
    char * welcome = "Bienvenido a Among RUZ!!";
    char* numb_players;

    args->sockets_clients->socket_c1 = accept(server_socket, (struct sockaddr*)&client1_addr, &addr_size);
    args->sockets_clients->num_players++;
    printf("Entro 1\n");
    numb_players = "Hay 1 jugador en la sala.";
    server_send_message(args->sockets_clients->socket_c1, 1, welcome);
    server_send_message(args->sockets_clients->socket_c1, 1, numb_players);

    args->sockets_clients->socket_c2 = accept(server_socket, (struct sockaddr*)&client2_addr, &addr_size);
    args->sockets_clients->num_players++;
    printf("Entro 2\n");
    numb_players = "Hay 2 jugadores en la sala.";
    server_send_message(args->sockets_clients->socket_c2, 1, welcome);
    server_send_message(args->sockets_clients->socket_c2, 1, numb_players);

    args->sockets_clients->socket_c3 = accept(server_socket, (struct sockaddr*)&client3_addr, &addr_size);
    args->sockets_clients->num_players++;
    printf("Entro 3\n");
    numb_players = "Hay 3 jugadores en la sala.";
    server_send_message(args->sockets_clients->socket_c3, 1, welcome);
    server_send_message(args->sockets_clients->socket_c3, 1, numb_players);


    args->sockets_clients->socket_c4 = accept(server_socket, (struct sockaddr*)&client4_addr, &addr_size);
    args->sockets_clients->num_players++;
    printf("Entro 4\n");
    numb_players = "Hay 4 jugadores en la sala.";
    server_send_message(args->sockets_clients->socket_c4, 1, welcome);
    server_send_message(args->sockets_clients->socket_c4, 1, numb_players);

    args->sockets_clients->socket_c5 = accept(server_socket, (struct sockaddr*)&client5_addr, &addr_size);
    args->sockets_clients->num_players++;
    printf("Entro 5\n");
    numb_players = "Hay 5 jugadores en la sala.";
    server_send_message(args->sockets_clients->socket_c5, 1, welcome);
    server_send_message(args->sockets_clients->socket_c5, 1, numb_players);

    args->sockets_clients->socket_c6 = accept(server_socket, (struct sockaddr*)&client6_addr, &addr_size);
    args->sockets_clients->num_players++;
    printf("Entro 6\n");
    numb_players = "Hay 6 jugadores en la sala.";
    server_send_message(args->sockets_clients->socket_c6, 1, welcome);
    server_send_message(args->sockets_clients->socket_c6, 1, numb_players);

    args->sockets_clients->socket_c7 = accept(server_socket, (struct sockaddr*)&client7_addr, &addr_size);
    args->sockets_clients->num_players++;
    printf("Entro 7\n");
    numb_players = "Hay 7 jugadores en la sala.";
    server_send_message(args->sockets_clients->socket_c7, 1, welcome);
    server_send_message(args->sockets_clients->socket_c7, 1, numb_players);

    args->sockets_clients->socket_c8 = accept(server_socket, (struct sockaddr*)&client8_addr, &addr_size);
    args->sockets_clients->num_players++;
    printf("Entro 8\n");
    numb_players = "Hay 8 jugadores en la sala.";
    server_send_message(args->sockets_clients->socket_c8, 1, welcome);
    server_send_message(args->sockets_clients->socket_c8, 1, numb_players);
}
