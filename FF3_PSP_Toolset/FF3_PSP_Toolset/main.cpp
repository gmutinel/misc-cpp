#define  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include "main.h"

void ShowARGS(void)
{
printf("Final Fantasy III PSP Toolset by Vash v0.99 -www.romhacking.it-\n\n");

printf("FF3_PSP_Toolset <switch> <file OR dir>\n\n");

printf("switch:\n");
printf("-dmgz (File) [Decompress MGZ files]\n");
printf("-cmgz (File) [Compress a file into MGZ]\n");
}

int main(int argc, char *argv[])
{
	int decompressmgz=0, compressmgz=0;

	if (argc < 3) ShowARGS();
	else
	{
		if(_strcmpi(argv[1], "-dmgz")==0) //Decompress MGZ Files
			{
				decompressmgz=1;
			}

		if(_strcmpi(argv[1], "-cmgz")==0) //Decompress MGZ Files
			{
				compressmgz=1;
			}
	}

	if (decompressmgz == 0 && compressmgz == 0)
	{
		ShowARGS();
		return(0);
	}

	if (decompressmgz == 1)
	{
		DecompressMGZ(argv[2]);
	}

	if (compressmgz == 1)
	{
		CompressMGZ(argv[2]);
	}
	return(0);
}