#ifndef BASEH 
#define BASEH
#include <inttypes.h>

#define PACKET_SIZE 5
#define MESSAGE_SIZE 3


struct packet
{
    uint8_t num;
    uint8_t data_byte; 
    uint8_t msg[3];
};

#endif