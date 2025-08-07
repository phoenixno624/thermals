#ifndef TYPES_H
#define TYPES_H

typedef unsigned char BYTE;
typedef unsigned short USHORT;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef unsigned char BOOL;

#define TRUE (BOOL)0x1
#define FALSE (BOOL)0x0

const BOOL starts_with(const char *, const char *);

#endif