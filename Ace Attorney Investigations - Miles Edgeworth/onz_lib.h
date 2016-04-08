#ifndef __ONZ_LIB__
#define __ONZ_LIB__

#include "types.h"

typedef enum{
	WII=0,
	DS
} console_type;

#define GET_U32(type,val) ( type==WII?  SWAP_ON_LITTLE_ENDIAN_32(val) : SWAP_ON_BIG_ENDIAN_32(val) )

//decompresses source and sets the compressed buffer size to destSize
//returns NULL if an error occurred
u8* onz_decompress(u8* source,u32 sourceSize, u32 *destSize,console_type type);

//compresses source and sets the decompressed buffer size to destSize
//returns NULL if an error occurred
u8* onz_compress(u8* source,u32 sourceSize,u32* destSize,console_type type);;


#endif
