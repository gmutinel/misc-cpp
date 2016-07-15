#define  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include "zlib.h"

int DumpText(FILE *dez, FILE *txt);
int DecompressZT1(char *filename)
{
FILE *zt1,*txt,*ext;
BYTE *comp,*decomp;
unsigned long int declen,complen;

zt1=fopen(filename,"rb");
filename[strlen(filename)-4]=0;
sprintf(filename,"%s.txt",filename);
txt=fopen(filename,"wb");

fread(&complen,4,1,zt1);
complen=complen-8;
fread(&declen,4,1,zt1);

decomp=(BYTE*)malloc(declen);
comp=(BYTE*)malloc(complen);

fread(comp,complen,1,zt1);

uncompress(decomp,&declen,comp,complen);

sprintf(filename,"temp.dez");
ext=fopen(filename,"w+b");
fwrite(decomp,declen,1,ext);
fclose(zt1);

DumpText(ext,txt);

fclose(ext);
fclose(txt);
//remove(filename);
return(0);
}

int DumpText(FILE *dlg, FILE *txt)
{
BYTE *sentence;
unsigned long int num,pointer,i,end;

fseek(dlg,0x00,SEEK_END);
end=ftell(dlg);
rewind(dlg);
fread(&num,4,1,dlg);
sentence=(BYTE*)malloc(end);

for (i=0;i<num;i++)
{
	fseek(dlg,(i*4)+4,SEEK_SET);
	fread(&pointer,4,1,dlg);
	fseek(dlg,pointer,SEEK_SET);
	fread(sentence,end-pointer,1,dlg);
	fprintf(txt,"[START]\n");
	fwrite(sentence,strlen((char*)sentence),1,txt);
	fprintf(txt,"\n[END]\n\n");
}

free(sentence);
return(0);
}
