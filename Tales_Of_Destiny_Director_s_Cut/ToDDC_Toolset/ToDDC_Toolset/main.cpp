//Tales Of Destiny Director's Cut Toolset by Vash
#define  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include "main.h"
#include "complib.h"

void ShowARGS(void)
{
	printf("Tales Of Destiny Director's Cut Toolset by Vash v0.01 -www.romhacking.it-\n\n");

	printf("ToDDC_Toolset <switch> <File>");

	printf("switch:\n");
	printf("-x (File) [extract BIN]\n");
}
int main(int argc, char *argv[])
{

int extract=0;


	if (argc < 3) 
		ShowARGS();
	else{

		if(_strcmpi(argv[1], "-x")==0) //Handle Extraction
		{
			extract=1;
		}




		if(extract==0) //Exception for wrong switch
		{
			ShowARGS();
			return(0);
		}

		if (extract==1)
		{
		ExtractBin(argv[2]);
		}


	}
	  
}