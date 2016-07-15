#include <stdio.h>
#include <windows.h>
#include <direct.h>
//#include <unistd.h>
#include "include\zlib.h"
# include <io.h>

/**************************************************************************
***Monopoly DS VRES Packer V1.0 by Vash -vash.romhacking.it-		  *****
***																	  *****
***STRUCTURE:														  *****
***																	  *****	
***0x04: "VRES"     -> Magic Word									  *****
***0x04: 0x00000100 -> Version Number v 1.00 (guess)				  *****
***0x04: File Number											      *****
***0x04: Archive Size												  *****
***0x04: 0x05EDD8   -> Unknown (timestamp?)							  *****
***0x04: 0x05EDD8   -> Unknown (timestamp?)							  *****
***Cycle for number of files										  *****			
***																	  *****
***0x04: Pointer SEEK_SET                                             *****
***0x04: File dimension												  *****
***0x04: Uncompressed dimension (ZLIB, can be equal if not compressed)*****
***0x04: Compression flag -> 0x00 not compressed, 0x01 compressed**********
***************************************************************************/

int main(int argc, char *argv[])
{
FILE *vres,*ext,*tbl;
BYTE **DecBuf,**CompBuf,*Filler;
char head[4] = {'V','R','E','S'},name[9];
unsigned char version[4]={0x00,0x00,0x01,0x00};
unsigned char unk[4] = {0x00,0x05,0xED,0xD8};
unsigned long int num,arch_size,i,pointer,*decsize,*compsize, test;
int *IsCompressed,n0=0,n1=0,n2=0,n3=1;
char *filename;

printf ("Monopoly DS VRES Packer V1.0 by Vash -vash.romhacking.it-\n\n");
	if (argc < 2) 
	{
		printf("Monopoly_DS_VRES_Packer Directory\n\n ex.\n Monopoly_DS_VRES_Packer res_befp\n");
		return(0);
	}


filename = (char*)malloc(strlen(argv[1])+5);
sprintf(filename,"%s.vrb\0",argv[1]);
vres = fopen(filename,"wb");
	if (!vres)
	{
		printf("Cannot create %s",filename);
		return(0);
	}

if (_chdir(argv[1]) != 0)
{
	printf("Cannot open the directory %s",argv[1]);
	return(0);
}

sprintf(filename,"%s.tbl\0",argv[1]);
tbl = fopen(filename,"rb");
	if (!tbl)
	{
		printf("Cannot find or open %s",filename);
		fclose(vres);
		return(0);
	}

//I have all the needed files, let's go

fwrite(head,4,1,vres); //header
fwrite(version,4,1,vres); //version number
//get the number of files, each file in the table file occupies 0x0A bytes, 0x09 for the name and 0x01 for the compression flag
fseek(tbl,0x00,SEEK_END);
num = ftell(tbl) / 0xA;
rewind(tbl); //back to the beginning
fwrite(&num,4,1,vres); //number of files
fwrite(unk,4,1,vres); //full dimension of the archive, we'll get back here later. Just a placeholder atm
fwrite(unk,4,1,vres); //unkown byte string as-is
fwrite(unk,4,1,vres); //unkown byte string as-is

compsize = (unsigned long int *)malloc(num*sizeof(unsigned long int));
decsize = (unsigned long int *)malloc(num*sizeof(unsigned long int));
IsCompressed = (int *)malloc(num*sizeof(int));

DecBuf = (BYTE**)malloc(num*1024*1024*1024);

CompBuf = (BYTE**)malloc(num*1024*1024*1024);

compsize[0] = (num*0x10)+0x18; //first pointer
pointer=0;
//now I cycle the files and write all the info
for (i=0;i<num;i++)
{
	pointer=pointer+compsize[i];
	//fseek(vres,(i*0x10)+0x18,SEEK_SET); //pointer table, starts at 0x18 and it's long 0x10 * numfiles
	
	fread(name,9,1,tbl); //get the filename from the table...
	IsCompressed[i]=fgetc(tbl); //...and the compression flag
	ext=fopen(name,"rb");
	fseek(ext,0x00,SEEK_END);
	decsize[i]=ftell(ext);
	rewind(ext);
	
	DecBuf[i]=(BYTE*)malloc(decsize[i]);
	fread(DecBuf[i],decsize[i],1,ext);
	if (IsCompressed[i] == 0x01) //previously compressed
	{
		CompBuf[i] =(BYTE*)malloc(decsize[i]*2); //exaggerated size malloc for the compression buffer, I can't know the precise size before but I know that WON'T be double te decompression size
		test=compress(CompBuf[i],&compsize[i],DecBuf[i],decsize[i]); //compress, the compsize var gets populated by itslef
	}else{
		compsize[i]=decsize[i];
	}
	//I got the info, I write them and then I go down to write the file
	fwrite(&pointer,4,1,vres);
	fwrite(&decsize[i],4,1,vres);
	fwrite(&compsize[i],4,1,vres);
	fwrite(&IsCompressed[i],4,1,vres);

	
	//fsync(fileno(vres));
	
	//fflush(vres);
	
	//fseek(vres,_filelength(fileno(vres)),SEEK_SET);
	
	/*if (IsCompressed == 0x01)
	{
		fwrite(CompBuf,compsize,1,vres);
		free(CompBuf);
	}else{
		fwrite(DecBuf,decsize,1,vres);
	}*/
	//printf("%X\n",_filelength(fileno(vres)));
	//fflush(vres);
	//printf("%X\n\n",_filelength(fileno(vres)));
	//free(DecBuf);
	fclose(ext);
}
//now back to writing the archive size
fseek(vres,_filelength(fileno(vres)),SEEK_SET); //I should already be at the end but better safe than sorry 
for (i=0;i<num;i++)
{
	if (IsCompressed[i] == 0x01) //Compressed	
		fwrite(CompBuf[i],compsize[i],1,vres);
	else
		fwrite(DecBuf[i],compsize[i],1,vres);

}
arch_size = ftell(vres);
fseek(vres,0x0C,SEEK_SET);
fwrite(&arch_size,4,1,vres); // write it and...done
//last cleanup
fclose(tbl);
fclose(vres);

printf("Packing complete! Enjoy\n");
}