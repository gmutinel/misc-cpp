#include <stdio.h>
#include <windows.h>
#include <direct.h>

FILE* CreateDirTree(char *name);

int main(int argc, char *argv[])
{

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