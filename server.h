/**
 * @file server.h
 * @brief Содержит основной код сервера для обработки пакетов данных
 */

#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <base.h>

/**
 * @brief Распаковывает упакованное значение на два отдельных значения
 * @param packedValue Упакованное значение для распаковки
 * @param firstValue Указатель на переменную для хранения первого значения
 * @param secondValue Указатель на переменную для хранения второго значения
 */
void unpackTwoValues(uint8_t packedValue, int *firstValue, int *secondValue) {
    *firstValue = (packedValue >> 4) & 0xF; 
    *secondValue = packedValue & 0xF; 
}

#endif