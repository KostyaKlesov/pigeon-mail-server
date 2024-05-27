#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>



int main(void)
{
   
    int s;
    unsigned short port;
    struct sockaddr_in server;
    char buf[5];
    char message[5];
    ///memset(buf, '\0', sizeof(buf));
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket()");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = ntohs(3590);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    for (size_t i = 0; i < sizeof(message); i++)
    {
        scanf("%s", &message[i]);
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