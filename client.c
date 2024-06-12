#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "base.h"


int main(void)
{
    // memcmp - сравнивает значения. 
    char * code;
    size_t size = 0;
    int s;
    uint8_t buf[5];
    int size_of_code = sizeof(code);
    unsigned short port;
    struct sockaddr_in server;
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket()");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_port = ntohs(3590);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    //memset(code, 0, 6);
    size_t n = getline(&code, &size, stdin);
    struct packet * outpacket = (struct packet *)(buf);
    outpacket->num = 1;
    memcpy(outpacket->msg, code, 4);
    printf("%s", outpacket->msg);
    if (sendto(s, buf, (strlen(buf)+1), 0,(struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("sendto()");
        exit(2);
    }
    close(s);
}