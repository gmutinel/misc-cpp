#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include "include\zlib.h"

/**************************************************************************
***Monopoly DS VRES Unpacker V1.02 by Vash -vash.romhacking.it-		  *****
***																	  *****
***STRUCTURE:														  *****
***																	  *****	
***0x04: "VRES"     -> Magic Word									  *****
***0x04: 0x00000100 -> Version Number v 1.00 (guess)				  *****
***0x04: File Number											      *****
***0x04: Archive Size												  *****
***0x04: 0x05EDD8   -> Unknown (timestamp?)							  *****
***0x04: 0x05EDD8   -> Unknown (timestamp?)							  *****
***Cycle for number of files										  *****			
***																	  *****
***0x04: Pointer SEEK_SET                                             *****
***0x04: File dimension												  *****
***0x04: Uncompressed dimension (ZLIB, can be equal if not compressed)*****
***0x04: Compression flag -> 0x00 not compressed, 0x01 compressed**********
***************************************************************************/

/* Changelog:
1.03 15/03/2014
[+] Added dbug strings

1.02 14/03/2014
[*] Fixed a stupid, studpid bug. Fuck VB6!

1.01 13/03/2014
[*] Added compression byte to table file for future packer

1.00 12/03/2014
[*] Initial Release
*/

int main(int argc, char *argv[])
{
FILE *vres,*ext,*tbl;
BYTE *DecBuf,*CompBuf;
char head[5],name[9];
unsigned long int num,arch_size,i,pointer,decsize,compsize;
int IsCompressed,n0=0,n1=0,n2=0,n3=1;
char *filename;

	printf ("Monopoly DS VRES Unpacker V1.03 by Vash -vash.romhacking.it-\n\n");
	if (argc < 2) 
	{
		printf("Monopoly_DS_VRES_Unpacker file.vrb\n");
		return(0);
	}

	vres = fopen(argv[1],"rb");
	if (!vres)
	{
		printf("Cannot find or open %s",argv[1]);
		return(0);
	}

	fread(head,4,1,vres);
	head[4]=0;
	if (strcmp(head,"VRES") != 0)
	{
		printf("%s is not a valid VRES file.",argv[1]);
		fclose(vres);
		return(0);
	}

	filename = (char*)malloc(strlen(argv[1]));
	strcpy(filename,argv[1]);
	filename[strlen(filename)-4] = 0;
	_mkdir(filename);
	_chdir(filename);
	//open the INI file with the info
	sprintf(filename,"%s.tbl",filename);
	tbl=fopen(filename,"wb");
	if (!tbl)
	{
		printf("Cannot create %s",filename);
		fclose(vres);
		return(0);
	}
	fseek(vres,0x08,SEEK_SET);
	fread(&num,4,1,vres); //number of files
	fread(&arch_size,4,1,vres); //archive filesize (useless for the extraction, but might come in handy for testing purposes)


	for (i=0;i<num;i++)
	{
		printf("Extraction file %d -> %d%d%d%d.dat\n",i+1,n0,n1,n2,n3);
		fseek(vres,(i*0x10)+0x18,SEEK_SET); //pointer table, starts at 0x18 and it's long 0x10 * numfiles
		printf("Info table offset --> 0x%X\n",ftell(vres));
		fread(&pointer,4,1,vres);
		printf("Pointer --> 0x%X\n",pointer);
		fread(&compsize,4,1,vres);
		printf("Compressed size --> 0x%X\n",compsize);
		fread(&decsize,4,1,vres);
		printf("Decompressed size --> 0x%X\n",decsize);
		fread(&IsCompressed,4,1,vres);
		printf("Compression flag --> %d\n\n",IsCompressed);
		//got the info I need, go to extraction and decompression (if necessary)
		fseek(vres,pointer,SEEK_SET);
		sprintf(name,"%d%d%d%d.dat\0",n0,n1,n2,n3);  
		ext = fopen(name,"wb");
		CompBuf = (BYTE*)malloc(compsize);
		fread(CompBuf,compsize,1,vres);
		if (IsCompressed == 1)
		{
			DecBuf = (BYTE*)malloc(decsize);
			uncompress(DecBuf,&decsize,CompBuf,compsize);
			fwrite(DecBuf,decsize,1,ext);
			free(DecBuf);
			free(CompBuf);
		}else{ //not compressed
			fwrite(CompBuf,compsize,1,ext);
			free(CompBuf);
		}
		fwrite(name,9,1,tbl);
		fwrite(&IsCompressed,1,1,tbl);
		fclose(ext);
		
		//name enumerator +1, up to 9999.dat (should be way more than enough)
		if (n3==9)
		{
			n3=0;
			n2=n2+1;
		}else{
			n3=n3+1;
		}
		if (n2==10)
		{
			n2=0;
			n1=n1+1;
		}
		if (n1==10)
		{
			n1=0;
			n0=n0+1;
		}
	}
	fclose(tbl);
	fclose(vres);
	printf("Extraction Complete. Enjoy\n\n");
}