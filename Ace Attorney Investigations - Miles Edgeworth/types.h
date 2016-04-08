#ifndef __TYPES__
#define __TYPES__

typedef char s8;
typedef  short s16;
typedef  int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SWAP_ON_LITTLE_ENDIAN_32(x) (((x>>24)&0xFF)||((x>>8)&0xFF00)||((x<<8)&0xFF0000)||((x&0xFF)<<24))
#define SWAP_ON_BIG_ENDIAN_32(x) x

#endif
