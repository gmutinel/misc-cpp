#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include "MyFuncs.h"
#include "include\zlib.h"

int main(int argc, char *argv[])
{
	FILE *dcp,*ext;
	BYTE *compressed,*decompressed;
	unsigned long int num,tableOff,i,x,len,pointer,compsize,decsize;
	char *name;

	printf ("WinterMute Engine Unpacker by Vash v1.0.1 -vash.romhacking.it-\n\n");
	if (argc < 2) 
	{
		printf("DCP_Unpacker file.dcp\n");
		return(0);
	}

	dcp = fopen(argv[1],"rb");
	if (!dcp)
	{
		printf("Can't open %s\n",argv[1]);
		return(0);
	}

	fseek(dcp,0x80,SEEK_SET);
	fread(&tableOff,4,1,dcp);
	fseek(dcp,tableOff,SEEK_SET);
	len=fgetc(dcp);
	name=(char*)malloc(len);
	fread(name,len,1,dcp);
	_mkdir(name);
	_chdir(name);
	free(name);
	//if (ftell(dcp) % 2 != 0)
		fseek(dcp,0x01,SEEK_CUR);
	fread(&num,4,1,dcp);
	printf("Extracting %d files\n",num);
	printf("%X",ftell(dcp));
	for (i=0;i<num;i++)
	{
		len=fgetc(dcp);
		name=(char*)malloc(len);
		fread(name,len,1,dcp);
		for (x=0;x<len;x++)
		{
			name[x]=name[x]^0x44; //DirTree decrypted
		}
		ext=CreateDirTree(name);
		printf ("Extracing %s [%d on %d]\n",name,i+1,num);
		fread(&pointer,4,1,dcp);
		fread(&decsize,4,1,dcp);
		fread(&compsize,4,1,dcp);
		fseek(dcp,0x0C,SEEK_CUR); //gotta check this jump
		tableOff = ftell(dcp);
		fseek(dcp,pointer,SEEK_SET);
		if (compsize == 0x00) //not compressed
		{
			decompressed=(BYTE*)malloc(decsize);
			fread(decompressed,decsize,1,dcp);
			fwrite(decompressed,decsize,1,ext);
			free(decompressed);
		}else{
			decompressed=(BYTE*)malloc(decsize);
			compressed=(BYTE*)malloc(compsize);
			fread(compressed,compsize,1,dcp);
			uncompress(decompressed,&decsize,compressed,compsize);
			free(compressed);
			fwrite(decompressed,decsize,1,ext);
			free (decompressed);
		}
		free(name);
		fclose(ext);
		fseek(dcp,tableOff,SEEK_SET);
		//system("pause");
	}
}