#include "client.h"


uint8_t packTwoValues(int firstValue, int secondValue) {
    return ((firstValue & 0xF) << 4) | (secondValue & 0xF);
}
int main(void)
{
    char * code; 
    size_t size = 0;
    int s; 
    uint8_t buf[5];
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket()");
        exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET; 
    server.sin_port = ntohs(3590);     
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    size_t n = getline(&code, &size, stdin);
    if (n == -1) {
        perror("getline");
        exit(1);
    }
    int start_index = 0;
    int end_index = 2;
    struct packet * outpacket = (struct packet *)(buf); 
    for (size_t i = 0; i < strlen(code) - 1; i++){
        outpacket->num = i; 
        outpacket->data_byte = packTwoValues(start_index, end_index); 
        memcpy(outpacket->msg, code + i, MESSAGE_SIZE); 

        if (sendto(s, buf, PACKET_SIZE, 0,(struct sockaddr *)&server, sizeof(server)) < 0)
        {
            perror("sendto()");
            exit(2);
        }
        if (i <= 2)
        {
            start_index += 1;
            end_index += 1;
        }
        else{
            start_index += 1;
        }
    }
    close(s);
}