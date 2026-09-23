#ifndef NET_DATA_H
#define NET_DATA_H

#include <stdio.h>

typedef struct {
    long longArr[7];
    int intArr[7]; 
} LabPacket;

void printLabPacket(const char* prefix, LabPacket* packet) {
    printf("%s:\n", prefix);
    printf("LabDTO{longNums=[%ld, %ld, %ld, %ld, %ld, %ld, %ld], ",
        packet->longArr[0], packet->longArr[1], packet->longArr[2],
        packet->longArr[3], packet->longArr[4], packet->longArr[5], packet->longArr[6]);
    printf("intNums=[%d, %d, %d, %d, %d, %d, %d]}\n",
        packet->intArr[0], packet->intArr[1], packet->intArr[2],
        packet->intArr[3], packet->intArr[4], packet->intArr[5], packet->intArr[6]);
}

#endif