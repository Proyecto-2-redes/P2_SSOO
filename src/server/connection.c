#include "connection.h"

PlayersInfo* prepare_sockets_and_get_clients(char* IP, int port) {
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
    inet_aton(IP, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);

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
    PlayersInfo* sockets_clients = malloc(sizeof(PlayersInfo));

    // Se aceptan a los primeros 8 clientes que lleguen. "accept" retorna el n° de otro socket asignado para la comunicación
    sockets_clients->socket_c1 = accept(server_socket, (struct sockaddr*)&client1_addr, &addr_size);
    sockets_clients->socket_c2 = accept(server_socket, (struct sockaddr*)&client2_addr, &addr_size);
    sockets_clients->socket_c3 = accept(server_socket, (struct sockaddr*)&client3_addr, &addr_size);
    sockets_clients->socket_c4 = accept(server_socket, (struct sockaddr*)&client4_addr, &addr_size);
    sockets_clients->socket_c5 = accept(server_socket, (struct sockaddr*)&client5_addr, &addr_size);
    sockets_clients->socket_c6 = accept(server_socket, (struct sockaddr*)&client6_addr, &addr_size);
    sockets_clients->socket_c7 = accept(server_socket, (struct sockaddr*)&client7_addr, &addr_size);
    sockets_clients->socket_c8 = accept(server_socket, (struct sockaddr*)&client8_addr, &addr_size);

    return sockets_clients;
}