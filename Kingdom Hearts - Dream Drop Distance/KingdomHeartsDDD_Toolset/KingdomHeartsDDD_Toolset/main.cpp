//Kingdom Hearts Dream Drop Distance Toolset by Vash
#define  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include "main.h"

void ShowARGS(void)
{
	printf("Kingdom Hearts Dream Drop Distance Toolset by Vash v0.01 -vash.romhacking.it-\n\n");

	printf("KingdomHeartsDDD_toolset <switch> <file OR dir>\n\n");

	printf("switch:\n");
	printf("-xrbin (File) [extract RBIN]\n");
	printf("-mrbin (Dir) [make RBIN]\n");
	printf("-dumpctd (File) [Dump CTD]\n");
	printf("-insertctd (File) [Insert CTD]\n");
}

int main(int argc, char *argv[])
{

int xrbin = 0, mrbin = 0, dumpctd = 0, insertctd = 0;

if (argc < 3) ShowARGS();
else{

		if (_strcmpi(argv[1], "-xrbin") == 0) //Handle extraction for RBIN files
			xrbin = 1;

		if (_strcmpi(argv[1], "-mrbin") == 0) //Handle creation of RBIN files
			mrbin = 1;

		if (_strcmpi(argv[1], "-dumpctd") == 0) //Handle dump of CTD files
			dumpctd = 1;

		if (_strcmpi(argv[1], "-insertctd") == 0) //Handle creation of CTD files
			insertctd = 1;


		if (xrbin == 0 && mrbin == 0 && dumpctd == 0 && insertctd == 0)
			{
				ShowARGS();
				return(0);
			}
	

		if (xrbin == 1)
		{
			ExtractRbin(argv[2]);
			return(0);
		}

		if (mrbin == 1)
		{
			MakeRbin(argv[2]);
			return(0);
		}

		if (dumpctd == 1)
		{
			DumpCtd(argv[2]);
			return(0);
		}

		if (insertctd == 1)
		{
			MakeCtd(argv[2]);
			return(0);
		}

	}
}