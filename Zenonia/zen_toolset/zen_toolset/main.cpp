//Zenonia Android Toolset by Vash
#define  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include "main.h"


void ShowARGS(void)
{
printf("Zenonia Games Toolset by Vash v0.01 -vash.romhacking.it-\n\n");

printf("zen_toolset <switch> <file>\n\n");

printf("SWITCH:\n");
printf("-dzt -> Decompress zt1 files\n");
}


int main(int argc, char *argv[])
{


if (argc < 3) 
{
	ShowARGS();
	return(0);
}

if (strcmp(argv[1],"-dzt") == 0) //extract MB files
{
	DecompressZT1(argv[2]);
} 

return(0);
}