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
    struct packet *recvpacket = (struct packet*)(buf);
    char * code;
    unsigned char data_byte = 0;
    int start_index = 0;
    int end_index = 4; // Отправляем первые пять символов в цикле
    data_byte |= (start_index << 4); // Сохраняем индекс первого символа в старшие 4 бита
    data_byte |= end_index; // Сохраняем индекс последнего символа в младшие 4 бита

    for(size_t i = 0; i < 6; i++){
        if(recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &client,&client_address_size) <0)
        {
            perror("recvfrom()");
            exit(4);
        }
            recvpacket->num = i + 1;
            strncpy(recvpacket->msg, buf + 1, 4);  
            printf("Получено сообщение номер %u %s\n", recvpacket->num,recvpacket->msg,(client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),ntohs(client.sin_port),inet_ntoa(client.sin_addr));
    }
    close(s);
}
