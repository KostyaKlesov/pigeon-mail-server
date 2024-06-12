#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "base.h"


int main(){
    
    int s, namelen, client_address_size;
    struct sockaddr_in client, server;
    char buf[32];
    s = socket(AF_INET, SOCK_DGRAM, 0);
    char message[5];


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

    printf("Используется порт %d\n", ntohs(server.sin_port));

    client_address_size = sizeof(client);

    if(recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &client,
            &client_address_size) <0)
    {
       perror("recvfrom()");
       exit(4);
    }
    // почитать про структуры и посмотреть файл packetizer_linux.cpp (create_packet, recv)
    // и про пакеты
    struct packet *recvpacket = (struct packet*)(buf);
    char sms [4];
    memcpy(sms, recvpacket->msg, 4);
    printf("%s\n", buf);
    //printf("%s", recvpacket->msg);
    printf("Получено сообщение номер %u %s\n", recvpacket->num,sms,(client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),ntohs(client.sin_port),inet_ntoa(client.sin_addr));
    close(s);
}
