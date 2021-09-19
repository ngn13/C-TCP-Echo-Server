#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
/*
printf("Time: %02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
*/
#define PORT 8080
int main(int argc, char const *argv[])
{   time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int server_fd, valread;
    int new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
       
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        printf("\nSocket creation failed\n");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        printf("\nSocket creation failed(2)\n");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        printf("\nSocket binding failed\n");
        exit(EXIT_FAILURE);
    }
    printf("\nServer started at %02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("\n********************************");
    if (listen(server_fd, 3) < 0)
    {
        printf("\nSocket listening failed\n");
        exit(EXIT_FAILURE);
    }

    while (1){
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
        {
        	printf("Connection acception failed\n");
        	exit(EXIT_FAILURE);
        }
	else{
		printf("\nConnection with ->  %d at %02d:%02d:%02d\n", new_socket, tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf("-------------------------------------\n");
                while (1){
    			valread = read( new_socket, buffer, 1024);
			if (valread==0){break;}
			printf("Echo log: %s - %d / Connection: %d\n", buffer, valread, new_socket);
			send(new_socket, buffer , strlen(buffer) , 0 );
			memset(buffer, 0, 1024);
		}
	}
   }
}