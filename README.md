# Readme Proyecto 2

|       Nombre integrante       | Número de alumno |
| :---------------------------: | :--------------: |
|      FELIPE BARRÍA MORA       |     15637298     |
|  JUAN PABLO GONZÁLEZ ARAVENA  |     1461913J     |
| IRINA ANDREA SALAZAR GRONDONA |     14203944     |
|    LUCAS ZALAQUETT MC KAY     |     15635031     |


## Instrucciones para ejecutar el programa
Hay un archivo Makefile para compilar los archivos del servidor y el cliente. Para ejecutar el programa mediante el terminal, ubicarse en la carpeta principal, ejecutar el comando make y luego escribir:  

$ ./server -i <ip_address> -p <tcp_port>  
$ ./client -i <ip_address> -p <tcp_port>  

donde ip_address corresponde a la dirección IP del servidor en formato human-readable y tcp_port corresponde al puerto a través del cual se recibirán nuevas conexiones.  
Este trabajo se realizó haciendo pruebas en la dirección IP 0.0.0.0 y en el puerto 8080.


## Descripción de los paquetes utilizados en la comunicación entre cliente y servidor
-
-
-
-

## Cuáles fueron las principales decisiones de diseño para construir el programa
- El chat fantasma es sólo para expulsados, no para eliminados.

## Cuáles son las principales funciones del programa
### Client - communication.h
- void client_send_message(int client_socket, int pkg_id, char * message): recibe como argumentos un int que representa el socket del cliente, otro int que representa el id del paquete y un puntero a un char del mensaje. Retorna vacío.  
- int client_receive_id(int client_socket): recibe como argumento un int que representa el socket del cliente. Retorna un int que representa el ID del mensaje.  
- char * client_receive_payload(int client_socket): recibe como argumento un int que representa el socket del cliente. Retorna un puntero a un char que representa el payload.  

### Client - connection.h
- int prepare_socket(char *IP, int PORT): recibe como argumentos un puntero a un char de la dirección IP y un int que representa el puerto. Retorna un int que representa el socket del cliente.  

### Client - main.c
- void * recv_msg_handler(void *arguments): recibe como argumento un puntero a argumentos necesarios para crear un struct arg_struct. Retorna un puntero vacío.   
- void * send_msg_handler(void *arguments): recibe como argumento un puntero a argumentos necesarios para crear un struct arg_struct. Retorna un puntero vacío.   
- void str_trim_lf(char *arr, int length): recibe como argumentos un puntero a un arreglo de chars y un int. Retorna vacío.  
- int main(int argc, char *argv[]): función que maneja el programa principal.  

### Server - communication.h
- int server_receive_id(int client_socket): recibe como argumento un int del socket del cliente. Retorna un int que representa el ID del mensaje.  
- char * server_receive_payload(int client_socket): recibe como argumento un int que representa el socket del cliente. Retorna un puntero a un char que representa el payload.  
- void server_send_message(int client_socket, int pkg_id, char *message): recibe como argumentos un int que representa el socket del cliente, otro int que representa el id del paquete y un puntero a un char del mensaje. Retorna vacío.  

### Server - connection.h
- void * prepare_sockets_and_get_clients(void *arguments): recibe como argumento un puntero a argumentos necesarios para crear un struct arg_struct. Retorna un puntero vacío.  
- void message_initial(int player_number, struct arg_struct *arguments, char colors[8][9]): recibe como argumentos un int que representa el numero del jugador, un puntero a un struct arg_struct y un vector de chars. Retorna vacío.  
- int number_players_connected(struct arg_struct *arguments): recibe como argumento un puntero a un struct arg_struct. Retorna un int

### Server - main.c
- void * recv_msg_handler(void *arguments):  
- void message_handler(char* message, int socket_number, struct arg_struct *arg_struct):  
- int players_connected(struct arg_struct *arg_struct):  
- int *random_numbers(int lower, int upper, int count):  
- int check_game(struct arg_struct *arg_struct):  
- void check_votation(struct arg_struct *arg_struct):  
- int main(int argc, char *argv[]):  

## Qué supuestos adicionales ocuparon

## Cualquier información que consideren necesaria para facilitar la corrección de su tarea
