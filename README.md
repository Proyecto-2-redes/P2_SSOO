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
- <sys/socket.h>:  

- <sys/types.h>:  

- <sys/un.h>:  

- <netinet/in.h>:  

- <arpa/init.h>:  

- <netdb.h>:  


## Cuáles fueron las principales decisiones de diseño para construir el programa
- El chat fantasma es sólo para expulsados, no para eliminados.

## Cuáles son las principales funciones del programa
### Client - communication.h
-
-
-
-
-
-
### Client - connection.h
-
-
-
-
-
-
### Client - main.c
-
-
-
-
-
-

### Server - communication.h
-
-
-
-
-
-
### Server - connection.h
-
-
-
-
-
-
### Server - main.c
-
-
-
-
-
-



## Qué supuestos adicionales ocuparon

## Cualquier información que consideren necesaria para facilitar la corrección de su tarea
