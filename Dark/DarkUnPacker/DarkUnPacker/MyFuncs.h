

FILE* CreateDirTree(char *name)
{
FILE *ext;
char *string;
unsigned long int i,x,dirs;
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
		_mkdir(string);
		_chdir(string);
		x=0;
		dirs=dirs+1;
	}
}
string[x]=0;
sprintf(string,"%s\0",string);
ext=fopen(string,"wb");

for (i=0;i<dirs;i++)
{
	_chdir("..");
}
return(ext);
}