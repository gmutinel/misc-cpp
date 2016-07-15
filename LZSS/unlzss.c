#include <stdio.h>
#include <windows.h>
#include "unlzss.h"

BYTE buffer[520000];
BYTE buffer2[520000];
int main(int argc, char *argv[])
{
    
    FILE *lzss,*newone;
    unsigned long int end,size;
    lzss=fopen(argv[1],"r+b");
    newone=fopen(argv[2],"w+b");
    fseek(lzss,0x00,SEEK_END);
    end=ftell(lzss);
    fseek(lzss,4,SEEK_SET);
    fread(&size,4,1,lzss);
    fseek(lzss,0x10,SEEK_SET);
    fread(buffer,end-0x10,1,lzss);
    unlzss (buffer2,size,buffer,end-0x10);
    fwrite(buffer2,size,1,newone);
}
