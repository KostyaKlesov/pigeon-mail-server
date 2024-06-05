#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

void sendMessage(char* message){
    sleep(3600);
    if (rand() % 2 == 0) {
        printf("Голубь успешно доставил сообщение: %s\n", message);
    } else {
        printf("К сожалению, голубь потерялся по пути.\n");
    }
}


int main(void)
{
   
    int s;
    unsigned short port;
    struct sockaddr_in server;
    char buf[5]; 
    char code[6];
    //char message[5];
    char message[6];
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket()");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = ntohs(3590);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    fgets(code, sizeof(code), stdin);
    code[strcspn(code, "\n")] = 0; 
    strcpy(buf, code);
    for (int i = 0; i < strlen(code); i += 5) {
        strncpy(message, code + i, 5);
        message[5] = '\0';
        sendOverPigeon(message);
    }
    strcpy(buf, message);
    printf("Введенное сообщение: %s\n", &buf);
    if (sendto(s, buf, (strlen(buf)+1), 0,(struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("sendto()");
        exit(2);
    }
    close(s);
}


