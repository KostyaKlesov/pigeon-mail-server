/**
 * @file client.h
 * @brief Содержит основной код клиента для обработки пакетов данных
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <base.h>


/**
 * @brief Упаковывает значения первого и последнего индекса сообщения в восьмибитное число
 * @param firstValue Указатель на переменную для хранения первого значения
 * @param secondValue Указатель на переменную для хранения второго значения
 * @return Упакованный байт
 */
uint8_t packTwoValues(int firstValue, int secondValue);

#endif 
