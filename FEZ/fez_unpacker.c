#include <stdio.h>
#include <Windows.h>
#include <direct.h>

FILE* CreateDirTree(char *name);

int main(int argc, char *argv[])
{
BYTE *buffer;
FILE *pak, *ext;
unsigned long int i,num,size;
short int len;
unsigned char *name,*filename;

printf ("FEZ PAK Unpacker v1.0 by Vash -vash.romhacking.it-\n\n");

pak = fopen(argv[1],"rb");
filename=(char*)malloc(strlen(argv[1])+1);
sprintf(filename,"%s\0",argv[1]);
filename[strlen(filename)-4]=0;
mkdir(filename);
chdir(filename);
fread(&num,4,1,pak);
printf("There are %d files in this archive\n",num);
for (i=0;i<num;i++)
{
	len=fgetc(pak);
	name=(char*)malloc(len+1);
	fread(name,len,1,pak);
	name[len]=0;
	ext=CreateDirTree(name); //this function creates subdirs if necessary and gives back the pointer to the file
	printf("Extracting %s.xnb [%d on %d]\n",name,i+1,num);
   // system("pause");
    fread(&size,4,1,pak);
	buffer=(BYTE*)malloc(size);
	fread(buffer,size,1,pak);
    fwrite(buffer,size,1,ext);
	fclose(ext);
	free(buffer);
	free(name);
}
fclose(pak);
}

FILE* CreateDirTree(char *name)
{
FILE *ext;
char *string;
int i,x,dirs;
string=(char*)malloc(strlen(name)+6);
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
sprintf(string,"%s.xnb\0",string);
ext=fopen(string,"wb");

for (i=0;i<dirs;i++)
{
	chdir("..");
}
return(ext);
}
