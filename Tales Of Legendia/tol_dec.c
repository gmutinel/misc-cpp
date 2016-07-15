#include <stdio.h>
#include <windows.h>
#include "unlzss.h"

BYTE buffer[52000000];
BYTE buffer2[52000000];

int main(int argc, char *argv[])
{
FILE *lzss,*dec;
unsigned long int decsize,compsize;
lzss=fopen(argv[1],"r+b");
dec=fopen(argv[2],"w+b");
fseek(lzss,0x04,SEEK_SET);
fread(&compsize,4,1,lzss);
fread(&decsize,4,1,lzss);
if (compsize == decsize+0x10)
{
fseek(lzss,0x10,SEEK_SET);
fread(buffer,decsize,1,lzss);
fwrite(buffer,decsize,1,dec);    
}else{
compsize-=0x10;
fseek(lzss,0x10,SEEK_SET);
fread(buffer,compsize,1,lzss);
unlzss (buffer2,decsize,buffer,compsize);
fwrite(buffer2,decsize,1,dec);
}
}
