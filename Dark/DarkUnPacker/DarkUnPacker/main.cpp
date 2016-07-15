#define  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <direct.h>
#include "Myfuncs.h"
#include "main.h"
#include "SimpleIni.h"

int Unpack(char *filename);
int Pack(char* filename);

int main(int argc, char *argv[])
{
	

printf ("Dark Un\\Packer by Vash v1.0 - vash.romhacking.it -\n\n");
if (argc < 3 || (strcmp(argv[1],"-x") != 0 && strcmp(argv[1],"-m") != 0 ) )
{
	printf("DarkUnPacker option file.darkpack\n\n");
	printf("-x Extract\n");
	printf("-m Pack\n\n");
	printf("Example:\n\n");
	printf("DarkUnPack -x LocText_en.darkpack\n");
	printf("DarkUnPack -m LocText_en.darkpack\n");
	return (0);
}

if (strcmp(argv[1],"-x") == 0)
{
	Unpack(argv[2]);
	return(0);
}

if (strcmp(argv[1],"-m") == 0)
{
	Pack(argv[2]);
	return(0);
}

}


int Unpack(char* filename)
{

FILE *pack,*ext,*tbl;
BYTE *buffer;
unsigned long int i,num,headsize;
char head[9];
DarkHead *headerInfo;
//CSimpleIniA ini;

pack = fopen(filename,"r+b");

if (!pack)
{
	printf("Cannot open or find %s\n",filename);
	return(0);
}

fread(head,8,1,pack);
head[8] = 0;

if (strcmp(head,"DARKPACK") != 0)
{
	printf("%s is not a valid DarkPack file\n",filename);
	return(0);
}

filename[strlen(filename)-9]=0;
_mkdir(filename);
_chdir(filename);
//open the INI file with the info
sprintf(filename,"%s.tbl",filename);
tbl=fopen(filename,"wb");
//fprintf(tbl,"#File created by DarkUnPacker, DO NOT change\n\n");
//ini.SetUnicode();
//ini.LoadFile(filename);

fread(&headsize,4,1,pack);
fread(&num,4,1,pack);
headerInfo =(DarkHead*)malloc(num*sizeof(DarkHead));

fwrite(&num,4,1,tbl);
//get the info
for (i=0;i<num;i++)
{
	fread(&headerInfo[i].pointer,4,1,pack);
	fread(&headerInfo[i].nulled1,4,1,pack);
	fread(&headerInfo[i].unk1,4,1,pack);
	fread(&headerInfo[i].nulled2,4,1,pack);
	fread(&headerInfo[i].size,4,1,pack);
	fread(&headerInfo[i].NameLen,4,1,pack);
	headerInfo[i].filename = (char*)malloc(headerInfo[i].NameLen);
	fread(headerInfo[i].filename,headerInfo[i].NameLen,1,pack);
//	ini.SetValue(headerInfo[i].filename,"Hash?",(const char*)headerInfo[i].unk1,NULL,TRUE);
	fwrite(headerInfo[i].unk1,4,1,tbl);
	fwrite(&headerInfo[i].NameLen,4,1,tbl);
	fwrite(headerInfo[i].filename,headerInfo[i].NameLen,1,tbl); 
}
//ini.SaveFile(tbl);
fclose(tbl);
//extract
for (i=0;i<num;i++)
{
	fseek(pack,headerInfo[i].pointer,SEEK_SET);
	buffer=(BYTE*)malloc(headerInfo[i].size);
	fread(buffer,headerInfo[i].size,1,pack);
	ext = CreateDirTree(headerInfo[i].filename);
	printf("Extracting %s [%d of %d]\n",headerInfo[i].filename,i+1,num);
	fwrite(buffer,headerInfo[i].size,1,ext);
	fclose(ext);
	free(buffer);
}
printf("Extracton complete!\n");

return(0);
}


int Pack(char* filename)
{
FILE *pack,*ext,*tbl;
BYTE *buffer;
unsigned long int i,num,headsize,tmpoff;
DarkHead *headerInfo;
//CSimpleIni ini;
//CSimpleIni::TNamesDepend files;
//const TCHAR *pszSection = 0;

//char path[1024];

filename[strlen(filename)-9]=0;
if (_chdir(filename) != 0)
{
	printf("Cannot find the directory %s",filename);
	return(0);
}
//getcwd(path,1024);
_chdir("..");
sprintf(filename,"%s.darkpack",filename);
pack = fopen(filename,"w+b");
if (!pack)
{
	printf("Cannot create the file %s",filename);
	return(0);
}
filename[strlen(filename)-9]=0;
_chdir(filename);

sprintf(filename,"%s.tbl",filename);
tbl=fopen(filename,"r+b");
if (!tbl)
{
	printf("Cannot open the file %s",filename);
	return(0);
}
//ini.SetUnicode();
//ini.LoadFile(tbl);

//ini.GetAllSections(files);
//CSimpleIni::TNamesDepend::const_iterator iSection = files.begin();

fread(&num,4,1,tbl);

/*for ( ; iSection != files.end(); ++iSection )
{
	 num++;
}*/


//iSection = files.begin();
headerInfo =(DarkHead*)malloc(num*sizeof(DarkHead));

headsize = 0;
for (i=0;i<num;i++)
{
	fread(headerInfo[i].unk1,4,1,tbl);
	fread(&headerInfo[i].NameLen,4,1,tbl);
	headerInfo[i].filename = (char*)malloc(headerInfo[i].NameLen);
	fread(headerInfo[i].filename,headerInfo[i].NameLen,1,tbl);
	headerInfo[i].nulled1 = 0;
	headerInfo[i].nulled2 = 0;
	ext=fopen(headerInfo[i].filename,"r+b");
	fseek(ext,0x00,SEEK_END);
	headerInfo[i].size=ftell(ext);
	headsize = headsize + 0x18 + headerInfo[i].NameLen;
	fclose(ext);
}

/*for ( ; iSection != files.end(); ++iSection )
{
	 
	headerInfo[i].NameLen = strlen((char*)&iSection->pItem);
	while (((headerInfo[i].NameLen+ 0x18) % 16) != 0)
		headerInfo[i].NameLen++;

	printf("%x\n",headerInfo[i].NameLen);
	pszSection = iSection->pItem;

	headerInfo[i].filename = (char*)malloc(headerInfo[i].NameLen);
	sprintf(headerInfo[i].filename,"%s",&iSection->pItem);
	printf("%s - %s\n",headerInfo[i].filename,&iSection->pItem);
	sprintf((char*)headerInfo[i].unk1, "%s",ini.GetValue(iSection->pItem,(wchar_t*)"Hash?",0,FALSE));
	headerInfo[i].nulled1 = 0;
	headerInfo[i].nulled2 = 0;
	ext=fopen(headerInfo[i].filename,"r+b");
	fseek(ext,0x00,SEEK_END);
	headerInfo[i].size=ftell(ext);	
	i++;
	headsize = headsize + 0x18 + headerInfo[i].NameLen;
}*/

fprintf(pack,"DARKPACK");
fwrite(&headsize,4,1,pack);
fwrite(&num,4,1,pack);
tmpoff=headsize+0x10;
for (i=0;i<num;i++)
{
	fwrite(&tmpoff,4,1,pack); //new pointer
	fwrite(&headerInfo[i].nulled1,1,4,pack);
	fwrite(headerInfo[i].unk1,4,1,pack);
	fwrite(&headerInfo[i].nulled2,1,4,pack);
	fwrite(&headerInfo[i].size,4,1,pack);
	fwrite(&headerInfo[i].NameLen,4,1,pack);
	fwrite(headerInfo[i].filename,headerInfo[i].NameLen,1,pack);
	tmpoff = tmpoff+headerInfo[i].size;
}
	
for (i=0;i<num;i++)
{ 
	ext=fopen(headerInfo[i].filename,"r+b");
	buffer = (BYTE*)malloc(headerInfo[i].size);
	fread(buffer,headerInfo[i].size,1,ext);
	fclose(ext);
	printf("Packing %s [%d of %d]\n",headerInfo[i].filename,i+1,num);
	fwrite(buffer,headerInfo[i].size,1,pack);
	free(buffer);
}

printf("Pack complete!\n");
fclose(tbl);
fclose(pack);
return(0);
}


