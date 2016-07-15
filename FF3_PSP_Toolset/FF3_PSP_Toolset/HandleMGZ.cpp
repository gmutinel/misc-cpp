#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include "include\zlib.h"

int DecompressMGZ(char* filename)
{
FILE *mgz, *ext;
BYTE *compress,*decompress;
unsigned long int dsize,csize;
char *newname;

mgz=fopen(filename,"rb");
if (!mgz)
{
	printf("Can't find or open %s\n", filename);
	return(1);
}
newname=(char*)malloc(strlen(filename)-4+1);
filename[strlen(filename)-4]=0;
sprintf(newname,"%s\0",filename);
ext=fopen(newname,"wb");

fseek(mgz,0x04,SEEK_SET);
fread(&dsize,4,1,mgz);
fseek(mgz,0x00,SEEK_END);
csize=ftell(mgz)-8;
fseek(mgz,0x08,SEEK_SET);
compress=(BYTE*)malloc(csize);
decompress=(BYTE*)malloc(dsize);
fread(compress,csize,1,mgz);
uncompress(decompress,&dsize,compress,csize);
fwrite(decompress,dsize,1,ext);

fclose(ext);
fclose(mgz);
free(compress);
free(decompress);
printf("Decompressed successfully\n");
return(0);
}

int CompressMGZ(char* filename)
{
FILE *mgz, *ext;
BYTE *compressed,*decompressed;
unsigned long int dsize,csize;
char *newname;

ext=fopen(filename,"rb");
if (!ext)
{
	printf("Can't find or open %s\n", filename);
	return(1);
}
newname=(char*)malloc(strlen(filename)+4+1);
sprintf(newname,"%s.mgz\0",filename);
mgz=fopen(newname,"wb");

fseek(ext,0x00,SEEK_END);
dsize=ftell(ext);
rewind(ext);
decompressed=(BYTE*)malloc(dsize);
fread(decompressed,dsize,1,ext);
fclose(ext);
fprintf(mgz,"SIZE");
fwrite(&dsize,4,1,mgz);
compressed=(BYTE*)malloc(dsize*2);
csize=dsize*2;
compress(compressed,&csize,decompressed,dsize);
fwrite(compressed,csize,1,mgz);
fclose(mgz);
free(compressed);
free(decompressed);
printf("Compressed successfully into %s\n",newname);
return(0);

}