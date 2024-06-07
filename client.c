#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>

char sendMessage(char* code[6]){
    char buf[100]; 
    char message[6];
    //Копируем code в buf
    //strcpy(buf, code);
    // разбиваем код на части по 5 символов
    for (int i = 0; i < sizeof(code) - 2; i++) {
        printf("Вошли в цикл %d\n", i);
        strncpy(message, code, 5);
        //printf("%s\n", message);
        message[5] = '\0';
        if (rand() % 2 == 0){
            strcpy(buf, message);
            return buf;
        } else{
            continue;
        }
        memset(&message[0], 0, sizeof(message));
    }
    //strcpy(buf, message);
    //sleep(3600);
}


int main(void)
{
    char code[6];
    int s;
    char buf;
    unsigned short port;
    struct sockaddr_in server;
    // проверка на создание сокета 
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket()");
        exit(1);
    }
    // выбор протокала, порта и адроеса
    server.sin_family = AF_INET;
    server.sin_port = ntohs(3590);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    // ввод строки кода
    //code[strcspn(code, "\n")] = 0; 
    fgets(code, sizeof(code)+1, stdin);
    //printf("Введенное сообщение: %s\n", &buf);
    buf = sendMessage(code);
    // отправка сообщения
    if (sendto(s, buf, (strlen(buf)+1), 0,(struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("sendto()");
        exit(2);
    }
    close(s);
}


