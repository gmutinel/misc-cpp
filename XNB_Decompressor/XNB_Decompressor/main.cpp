#include <stdio.h>
#include <direct.h>
#include <Windows.h>
#include "unlzx.c"

int DecompressXNB(char *filename);

int main(int argc, char *argv[])
{
FILE *xnb;

	printf("Microsoft XNB Decompressor by Vash v1.0 -vash.romhacking.it\n\n");
	if (argc<2) {printf("XNB_Decompressor file.xnb\n"); return(0);}
	
	
	DecompressXNB(argv[1]);
	
	printf("Done. Enjoy!\n");
}

int DecompressXNB(char *filename)
{
FILE *xnb,*test;
BYTE *compressed,*decompressed;
unsigned long int  compsize,decsize;
unsigned char byte,head[4],platform;
int version;
bool IsCompressed;
//int decodedBytes, pos;

xnb=fopen(filename,"rb");
	
    if (!xnb)
		{
			printf("Cannot open or read the file %s\n",filename);
			return(3); //file I/O failed	
	}

fread(head,3,1,xnb);
head[3]=0;
if (strcmp((char*)head,"XNB") != 0)
	return (1); //magic word not recognized

platform = fgetc(xnb);
switch (platform) {
	case (0x78):
	printf("Detected XBOX360 file\n");
	break;
	
	case (0x77):
	printf("Detected Windows file\n");
	break;
	
	default:
	printf("Unknown platform detected, please contact the author of this tool. A correct decompression can't be assured\n");
	break;
}
byte = fgetc(xnb);
version = byte+(fgetc(xnb)*0x100);
//fread(&version,2,1,xnb);
if (version != 0x8004 && version != 0x8005)
{
	printf("This file doesn't look compressed or it's an uknown format/version. Please contact the author.\n");
	return (2); //Unrecognized format/version or simply not compressed
}

fread(&compsize,4,1,xnb);
compsize-=14;
fread(&decsize,4,1,xnb);


decompressed = (BYTE*)malloc(decsize);
compressed = (BYTE*)malloc(compsize);
/*test=fopen("test.xnb","wb");
int decodedBytes = 0;
int pos = 0;
int hi, lo;
int block_size = 0;
while(pos < compsize)
{
	fseek(xnb,pos+14,SEEK_SET);
	hi = fgetc(xnb);
	lo=fgetc(xnb);
	block_size=0;
	block_size = (hi << 8) | lo;
	int frame_size = 0x8000;
	if(hi == 0xFF)
	{
		hi = lo;
		lo = fgetc(xnb);
		frame_size = (hi << 8) | lo;
		hi = fgetc(xnb);
		lo = fgetc(xnb);
		block_size = (hi << 8) | lo;
		pos+=5;
	}else
		pos+=2;
	
	if(block_size == 0 || frame_size == 0)
		break;

	decompressed = (BYTE*)malloc(frame_size);
	compressed = (BYTE*)malloc(block_size);
	fread(compressed,block_size,1,xnb);
	unlzx(compressed,block_size,decompressed,frame_size);
	fwrite(decompressed,frame_size,1,test);
	free(decompressed);
	free(compressed);
	pos += block_size;
	decodedBytes += frame_size;
}

fclose(test);*/
fread(compressed,compsize,1,xnb);
unlzx(compressed,compsize,decompressed,decsize);
fclose(xnb);
xnb=fopen("test.xnb","wb");
fputs("XNB",xnb);
fputc(platform,xnb);
fputc(0x05,xnb);
fputc(0x80,xnb);
decsize+=10;
fwrite(&decsize,4,1,xnb);
fwrite(decompressed,decsize,1,xnb);
free(decompressed);
free(compressed);
fclose(xnb);
}





















