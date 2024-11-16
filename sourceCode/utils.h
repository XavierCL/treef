#ifndef UTILS_H
#define UTILS_H

#define true 0x1
#define false 0x0
#define null 0x0

typedef unsigned char bool;
typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef signed long long int64;
typedef unsigned long long uint64;

#define low16(value) (uint16)((value) & 0xFFFF)
#define high16(value) (uint16)(((value) >> 16) & 0xFFFF)

int32 abs(int32 a);

#endif
