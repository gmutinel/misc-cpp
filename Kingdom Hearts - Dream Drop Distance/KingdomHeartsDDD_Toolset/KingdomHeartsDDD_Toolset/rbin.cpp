#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include <string.h>

char* GetAlias(char* extname);
void CreateDirTreeWithoutFile(char *name, bool GoBack);

int ExtractRbin(char *fname)
{
	BYTE *buffer;
	FILE *rbin, *ext, *tbl;
	char header[5] = { 'C', 'R', 'A', 'R','\0' };
	char *VarForChecks;
	char *extname,*alias;


	unsigned long int headsize, flags, npointer, fsize, fpointer, i;
	unsigned short int version,filenum;

	rbin = fopen(fname, "r+b");

	if (!(rbin))
	{
		printf("Cannot access the file %s\n", fname);
		return(0);
	}

	VarForChecks = (char*)malloc(5);
	fread(VarForChecks, 4, 1, rbin);
	VarForChecks[4] = 0;
	if (_strcmpi(VarForChecks, header) != 0)
	{
		printf("The file %s is not a valid/handled rbin file\n", fname);
		fclose(rbin);
		free(VarForChecks);
		return(0);
	}
	free(VarForChecks);

	fread(&version, 2, 1, rbin);
	if (version != 0x01)
	{
		printf("DEBUG: The version bytes are not what's expected, contact the coder please\n");
		system("pause");
		return(0);
	}

	fread(&filenum, 2, 1, rbin);
	fread(&headsize, 4, 1, rbin);

	extname = (char*)malloc(0x10);
	fseek(rbin, 0x10, SEEK_SET);
	fread(extname, 0x10, 1, rbin);


	/*_mkdir(extname);
	_chdir(extname);
	*/
	CreateDirTreeWithoutFile(extname, false);
	//specific for langs
	
	free(extname);
	for (i = 0; i < filenum; i++)
	{
		fseek(rbin, (i * 0x10) + 0x20, SEEK_SET);
		fread(&flags, 4, 1, rbin);
		fread(&npointer, 4, 1, rbin);
		//Purely northeastern italian , sorry but it's needed.... MA DIO CANE!!!
		if (npointer > 0x80000000)

			npointer = npointer - 0x80000000;

		if (npointer > 0x8000000)
			npointer = npointer - 0x8000000;

		if (npointer > 0x800000)
			npointer = npointer - 0x800000;

		if (npointer > 0x80000)
			npointer = npointer - 0x80000;
	    //************************************************end of DIO CANE FUCK YOU SQUENIX!
		fread(&fsize, 4, 1, rbin);
		//Apparently some files has, for some reason, the size plus start of RAM block (0x80000000)
		if (fsize > 0x80000000)
			fsize = fsize - 0x80000000;

		if (fsize > 0x8000000)
			fsize = fsize - 0x8000000;

		fread(&fpointer, 4, 1, rbin);
		fseek(rbin, npointer - 0x0C, SEEK_CUR); //for some strange reason the pointer to the name is the SEEK_SET of the pinter offset..
		//filename length is multiple of 4, remember to set the padding accordingly when packing back!		
		
		
		extname = (char*)malloc(headsize-ftell(rbin));		
		alias = (char*)malloc((headsize- ftell(rbin)) + 3);
		
		fread(extname, headsize - ftell(rbin), 1, rbin);
		
		alias = GetAlias(extname);
		ext = fopen(alias, "w+b");
		if (!(ext))
		{
			printf("Cannot write the file %s\n",  alias);
			system("pause");
		}
		else{
			printf("Extracting %s\nPOINTER OFFSET: %0X\nSIZE: %0X\n\n", alias, fpointer, fsize);
			fseek(rbin, fpointer, SEEK_SET);
			buffer = (BYTE*)malloc(fsize);
			fread(buffer, fsize, 1, rbin);
			fwrite(buffer, fsize, 1, ext);
			free(buffer);
			fclose(ext);
		}
		free(extname);
		//free(alias);
	}

	return(0);
}


int MakeRbin(char *DirName)
{
	printf("Not yet implemented");
	return(0);
}


char* GetAlias(char* extname)
{
	char* alias;
	//char* token;
	int index;
	unsigned int i;
	FILE *ext;

	alias = (char*)malloc(strlen(extname) + 3);
	index = 0;
	
	ext = fopen(extname, "r+b");
	if (ext)
	{ 
		while (ext)
		{
			fclose(ext);
			//token = strrchr(extname, '.');
			index = index + 1;
			sprintf(alias, "%02d_%s", index, extname);
			ext = fopen(alias, "r+b");
		}
	}else{		
		sprintf(alias,"%s\0",extname);
	}

	//some filenames has some unwritable characters on Windows (makes me think it's been coded on a unix system), since I use an alias anyway, I'll overwrite them with underscore
	for (i = 0; i < strlen(alias); i++)
		if ((alias[i] < 0x20 || alias[i] > 0x7F) || (alias[i] == 0x5C || alias[i] == 0x2F || alias[i] == 0x3A || alias[i] == 0x2A || alias[i] == 0x3F || alias[i] == 0x22 || alias[i] == 0x3C || alias[i] == 0x3E || alias[i] == 0x7C)) //ASCII limits and windows KeyChars, there are some exceptions but who cares			
				alias[i] = 0x5F; // 0x5F = _

	if (ext)
		fclose(ext);
	return (alias);
}

void CreateDirTreeWithoutFile(char *name, bool GoBack)
{	
	char *string;
	unsigned long int i, x, dirs;
	string = (char*)malloc(strlen(name) + 1);
	x = 0;
	dirs = 0;
	for (i = 0; i<strlen(name); i++)
	{
		if (name[i] != 0x2F)
		{
			string[x] = name[i];
			x = x + 1;
		}else{
			string[x] = 0;
			_mkdir(string);
			_chdir(string);
			x = 0;
			dirs = dirs + 1;
		}
	}
	
	/*string[x] = 0;
	sprintf(string, "%s\0", string);
	ext = fopen(string, "wb");*/
	string[x] = 0;
	_mkdir(string);
	_chdir(string);
	x = 0;
	dirs = dirs + 1;

	if (GoBack)
	{
		for (i = 0; i < dirs; i++)
		{
			_chdir("..");
		}
	}
		
}