#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <direct.h>

int ExtractVPP(char *filename);
int MakeVPP(char *filename);
FILE* CreateDirTree(char *name);

int ExtractVPP(char *filename)
{
	BYTE *buffer;
	FILE *vpp, *ext, *tbl;
	char tmp[5],head[5] = { 206, 10, 137, 81, 00 };
	char *dirname;
	char **fname;
	unsigned long int num, asize, headstart,i;
	unsigned long int *pointer, *fsize;

	
	vpp = fopen(filename, "rb");
	if (!vpp)
	{
		printf("Can't find or open %s", filename);
		return(0);
	}

	fread(tmp, 4, 1, vpp);
	tmp[4] = 0;
	if (strcmp(tmp, head) != 0)
	{
		printf("The header doesn't correspond to a VPP file\n");
		return(0);
	}

	dirname = (char*)malloc(strlen(filename));

	sprintf(dirname, "%s", filename);
	dirname[strlen(dirname) - 4] = 0;
	_mkdir(dirname);
	_chdir(dirname);
	sprintf(dirname, "%s.bin\0", dirname);
	tbl = fopen(dirname, "w+b");

	fseek(vpp, 8, SEEK_SET);
	fread(&num, 4, 1, vpp);
	fread(&asize, 4, 1, vpp);
	fread(&headstart, 4, 1, vpp);

	fseek(vpp, headstart, SEEK_SET);

	pointer = (unsigned long int*)malloc(sizeof(pointer)*num);
	fsize = (unsigned long int*)malloc(sizeof(fsize)*num);
	fname = (char**)malloc(num);
	for (i = 0; i < num; i++);
	{
		fname[i] = (char*)malloc(0x18);
		fread(fname[i], 0x18, 1, vpp);
		fwrite(fname[i], 0x18, 1, tbl);
		fread(&fsize[i], 4, 1, vpp);
		fseek(vpp, 0x04, SEEK_CUR);
	}
	
	
	fseek(vpp, ((ftell(vpp) / 0x800) + 1) * 0x800, SEEK_SET);
	
	for (i = 0; i < num; i++);
	{
		ext = CreateDirTree(fname[i]);
		buffer = (BYTE*)malloc(fsize[i]);
		fread(buffer, fsize[i], 1, vpp);
		fwrite(buffer, fsize[i], 1, ext);
		fclose(ext);
		free(buffer);
	}
	fclose(vpp);
	fclose(tbl);
	return(0);
}

int MakeVPP(char *filename)
{

	return(0);
}


FILE* CreateDirTree(char *name)
{
	FILE *ext;
	char *string;
	unsigned long int i, x, dirs;
	string = (char*)malloc(strlen(name) + 1);
	x = 0;
	dirs = 0;
	for (i = 0; i<strlen(name); i++)
	{
		if (name[i] != 0x5C)
		{
			string[x] = name[i];
			x = x + 1;
		}
		else{
			string[x] = 0;
			_mkdir(string);
			_chdir(string);
			x = 0;
			dirs = dirs + 1;
		}
	}
	string[x] = 0;
	sprintf(string, "%s\0", string);
	ext = fopen(string, "wb");

	for (i = 0; i<dirs; i++)
	{
		_chdir("..");
	}
	return(ext);
}