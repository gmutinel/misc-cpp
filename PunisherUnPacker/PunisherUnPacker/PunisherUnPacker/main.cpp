//The Punisher *.VPP Un/Packer by Vash
#define  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include "main.h"

void ShowARGS(void)
{
	printf("The Punisher *.VPP Un/Packer by Vash v1.00 -vash.romhacking.it-\n\n");

	printf("Punisher_Vpp_UnPacker <switch> <File>");

	printf("switch:\n");
	printf("-x (File) [extract VPP]\n");
	printf("-m (File) [make VPP]\n");

}
int main(int argc, char *argv[])
{

	int extract = 0;
	int make = 0;

	if (argc < 3)
		ShowARGS();
	else{

		if (_strcmpi(argv[1], "-x") == 0) //Handle Extraction
		{
			extract = 1;
		}

		if (_strcmpi(argv[1], "-m") == 0) //Handle Packing
		{
			make = 1;
		}



		if ((extract+make) == 0) //Exception for wrong switch
		{
			ShowARGS();
			return(0);
		}

		if (extract == 1)
		{
			ExtractVPP(argv[2]);
		}

		if (make == 1)
		{
			MakeVPP(argv[2]);
		}

	}

}