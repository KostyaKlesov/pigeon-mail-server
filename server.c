#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(){
    
    int s, namelen, client_address_size;
    struct sockaddr_in client, server;
    char buf[32];
    s = socket(AF_INET, SOCK_DGRAM, 0);


    if (s< 0){
        perror("socket()\n");
        exit(1);
    }


    server.sin_family      = AF_INET;
    server.sin_port        = ntohs(3590);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");


    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("bind()");
        exit(2);
    }
    namelen = sizeof(server);
    if (getsockname(s, (struct sockaddr *) &server, &namelen) < 0)
    {
       perror("getsockname()");
       exit(3);
    }

    printf("Port assigned is %d\n", ntohs(server.sin_port));

    client_address_size = sizeof(client);

    if(recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &client,
            &client_address_size) <0)
    {
       perror("recvfrom()");
       exit(4);
    }

    printf("Received message %s from domain %s port %d internet\
        address %s\n",
       buf,
       (client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),
       ntohs(client.sin_port),
       inet_ntoa(client.sin_addr));

    close(s);
}
