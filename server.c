#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "base.h"

void unpackTwoValues(uint8_t packedValue, int *firstValue, int *secondValue) {
    *firstValue = (packedValue >> 4) & 0xF;
    *secondValue = packedValue & 0xF;
}

int main(){
    
    int s, namelen, client_address_size;
    struct sockaddr_in client, server;
    char buf[PACKET_SIZE];
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
    char * code; 
    int start_index;
    int end_index;
    char msg_buff[4];
    msg_buff[3] = 0;
    int temp_index = 2;
    char message[6];
    for(size_t i = 0; i < 6; i++){
        if(recvfrom(s, buf, PACKET_SIZE, 0, (struct sockaddr *) &client,&client_address_size) <0)
        {
            perror("recvfrom()");
            exit(4);
        }
        struct packet *recvpacket = (struct packet*)(buf);
        unpackTwoValues(recvpacket->data_byte, &start_index, &end_index);
        memset(msg_buff, 0, MESSAGE_SIZE + 1);
        memcpy(msg_buff, recvpacket->msg, MESSAGE_SIZE);
        printf("Получено сообщение номер %u %s, start=%u, end=%u\n", recvpacket->num + 1, msg_buff, start_index, end_index, (client.sin_family == AF_INET?"AF_INET":"UNKNOWN"),ntohs(client.sin_port),inet_ntoa(client.sin_addr));
        /*if (i == 0)
        {
            for (int j = 0; j < 3; j++){
                message[j] += msg_buff[j];
            }
        }*/
        //else{
        for (size_t j = strlen(message); j < 6; j++)
        {
            //printf("Зашли сюда\n");
            //printf("%d\n", j);
            message[j] = msg_buff[j - start_index];
        }
        
            
        //}
        //memset(buf, 0, PACKET_SIZE);
    }
    message[6] = '\0';
    printf("Получено сообщение :%s\n", message);
    close(s);
}
