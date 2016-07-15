#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include "include\zlib.h"

FILE* CreateDirTree(char *name);
FILE* DecompressUMD(FILE *cumd);
unsigned long int GetMSB(unsigned long int x);
unsigned long int Decrypt(BYTE *DecTable, unsigned long int &index);
void UnpackType2(FILE *umd);

int main(int argc, char *argv[])
{
	FILE *umd,*ext;
	BYTE *buffer;
	unsigned long int i,toff,pointer,declen,complen,filesize;
	int len;
	short int num;
	char *name,head[5];
	bool CompFlag = false;
	printf ("I Am Alive PC Unpacker by Vash v0.5 -vash.romhacking.it-\n\n");
	if (argc < 2) 
	{
		printf("iaa_unpacker file.umd\n");
		return(0);
	}

	umd = fopen(argv[1],"rb");
	if (!umd)
	{
		printf("Can't open %s\n",argv[1]);
		return(0);
	}

	fread(head,4,1,umd);
	head[4]=0;
	if (strcmp(head,"EPCK") == 0)
	{
		printf("Compression found. Decompressing...\n");
		CompFlag = true;
		umd=DecompressUMD(umd);
		printf("Decompressed & Decrypted successfully. Now extracting...\n");
	}
	
	fseek(umd,-0x10,SEEK_END);
	fread(&toff,4,1,umd);
	//check the filesize to see which kind of archive is this
	fread(&filesize,4,1,umd);
	fseek(umd,0x00,SEEK_END);
	if (ftell(umd) != filesize)
	{
		UnpackType2(umd);
		return(1);
	}
	fseek(umd,toff,SEEK_SET);
	//Fuck, even the filenumber is encrypted...gotta do a workaround for this crap
	i=0;
	buffer=(BYTE*)malloc(4);
	fread(buffer,4,1,umd);
	num=Decrypt(buffer,i);
	fseek(umd,toff+i,SEEK_SET);
	free(buffer);
	printf("Detected %d files...\n",num);
	for (i=0;i<num;i++)
	{
		len=fgetc(umd);
		name=(char*)malloc(len);
		fread(name,len,1,umd);
		fread(&pointer,4,1,umd);
		fread(&declen,4,1,umd);
		fread(&complen,4,1,umd);
		if (complen != 0x00)
		{
			printf("The compsize of the file %s is not 0!\n",name);
			system("pause");
 		}
		toff=ftell(umd);
		printf("Extracting %s [%d on %d]\n",name,i+1,num);
		ext=CreateDirTree(name);
		free(name);
		fseek(umd,pointer,SEEK_SET);
		buffer=(BYTE*)malloc(declen);
		fread(buffer,declen,1,umd);
		fwrite(buffer,declen,1,ext);
		fclose(ext);
		free(buffer);
		fseek(umd,toff,SEEK_SET);
	}
	fclose(umd);
	if (CompFlag)
		remove("TempUmdDontTouchIt.umd");
}

void UnpackType2(FILE *umd)
{

	printf("Arhive type not yet implemented\n");
	system("pause");
}
FILE *DecompressUMD(FILE *cumd)
{
	FILE *decumd;
	BYTE *CompTable,*DecTable,*CompChunk,*DecChunk;
	unsigned long int ChunckMaxSize,DecSize,SizeTableStart,TotalTableSize,DecTableSize,CompTableSize,num,i,index,*ChunkSizes,ChunkDecSize;

	fseek(cumd,0x04,SEEK_SET);
	fread(&ChunckMaxSize,4,1,cumd);
	fread(&DecSize,4,1,cumd);
	fread(&SizeTableStart,4,1,cumd);
	fseek(cumd,SizeTableStart,SEEK_SET);
	fread(&TotalTableSize,4,1,cumd);
	fread(&DecTableSize,4,1,cumd);
	fread(&CompTableSize,4,1,cumd);
	DecTable=(BYTE*)malloc(DecTableSize);
	if (CompTableSize != 0x00) //the table itself is compressed
	{
		CompTable=(BYTE*)malloc(CompTableSize);
		fread(CompTable,CompTableSize,1,cumd);
		uncompress(DecTable,&DecTableSize,CompTable,CompTableSize);
		free(CompTable);
	}else{
		fread(DecTable,DecTableSize,1,cumd);
	}
	//now inside DecTable I have the encrypted chunk size table. Let's decode the bitch
	index=0;
	num = Decrypt(DecTable,index);
	//printf("%X\n",num);
	ChunkSizes=(unsigned long int*)malloc(num*sizeof(unsigned long int));
	i=0;
	while (index < DecTableSize)
	{
		ChunkSizes[i]=Decrypt(DecTable,index);
		if (Decrypt(DecTable,index) != 1) 
		{
			/*printf ("Flag different from 1!!\n");
			system("pause");*/
		}
	//	printf("%X\n",ChunkSizes[i]);
		i=i+1;
	}
	free(DecTable);
	decumd = fopen("TempUmdDontTouchIt.umd","wb");
	index=0; //recycle this variable, lazyass :D
	for (i=0;i<num;i++)
	{
		CompChunk=(BYTE*)malloc(ChunkSizes[i]);
		fread(CompChunk,ChunkSizes[i],1,cumd);
		if (ftell(decumd) < (DecSize - ChunckMaxSize))
		{
			ChunkDecSize = ChunckMaxSize;
		}else{
			ChunkDecSize = DecSize - ftell(decumd);
		}
		DecChunk=(BYTE*)malloc(ChunkDecSize);
		uncompress(DecChunk,&ChunkDecSize,CompChunk,ChunkSizes[i]);
		fwrite(DecChunk,ChunkDecSize,1,decumd);
		free(DecChunk);
		free(CompChunk);
	}
	fclose(cumd);
	fclose(decumd);
	decumd = fopen("TempUmdDontTouchIt.umd","rb");
	return(decumd);
}

unsigned long int Decrypt(BYTE *DecTable, unsigned long int &index)
{
	unsigned long int num;

	num = 0;
	if (GetMSB(DecTable[index] & 0x40) == 0) 
	{
		 num = (num << 6) + (DecTable[index] & 0x3F);
	}else{
		index+=1;
		if (GetMSB(DecTable[index] & 0x80) == 0) 
		{
			num = (num << 7) + (DecTable[index] & 0x7F);
			num = (num << 6) + (DecTable[index-1] & 0x3F);
		}else{
			index+=1;
			if (GetMSB(DecTable[index] & 0x80) == 0) 
			{
				num = (num << 7) + (DecTable[index] & 0x7F);
				num = (num << 7) + (DecTable[index-1] & 0x7F);
				num = (num << 6) + (DecTable[index-2] & 0x3F);
			}else{
				index+=1;
				if (GetMSB(DecTable[index] & 0x80) == 0) 
				{
					num = (num << 7) + (DecTable[index] & 0x7F);
					num = (num << 7) + (DecTable[index-1] & 0x7F);
					num = (num << 7) + (DecTable[index-2] & 0x7F);
					num = (num << 6) + (DecTable[index-3] & 0x3F);
				}
			}
		}
	}
	index+=1;
	return(num);
}

FILE* CreateDirTree(char *name)
{
FILE *ext;
char *string;
int i,x,dirs;
string=(char*)malloc(strlen(name)+1);
x=0;
dirs=0;
for (i=0;i<strlen(name);i++)
{
	if (name[i] != 0x5C)
	{
		string[x]=name[i];
		x=x+1;
	}else{
		string[x]=0;
		mkdir(string);
		chdir(string);
		x=0;
		dirs=dirs+1;
	}
}
string[x]=0;
sprintf(string,"%s\0",string);
ext=fopen(string,"wb");

for (i=0;i<dirs;i++)
{
	chdir("..");
}
return(ext);
}

unsigned long int GetMSB(unsigned long int x)
{
x |= (x >> 1);
x |= (x >> 2);
x |= (x >> 4);
x |= (x >> 8);
x |= (x >> 16);
return x - (x >> 1);
}