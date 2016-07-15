//Tales Of Legendia MCD Maker by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    
 FILE *mcd,*cps;
 unsigned long int dim,i,c,newdim;
 unsigned char comp[200];
 
 if (argc < 2) printf("Tales Of Legendia MCD Compressor by Vash v1.0 -www.romhacking.it-\n\ntol_mcdmkr dir\n\n");    
      else{   

printf("Tales Of Legendia MCD Compressor by Vash v1.0 -www.romhacking.it-\n\n");   
mcd=fopen(argv[1],"r+b");
sprintf(comp,"%s.cps\0",argv[1]);
cps=fopen(comp,"w+b");
fseek(mcd,0x00,SEEK_END);
dim=ftell(mcd);
rewind(mcd);
fread(buffer,dim,1,mcd);
//scrivo l'header del cps e uso la compressione 0
fputc(0x43,cps);
fputc(0x50,cps);
fputc(0x53,cps);
fputc(0x00,cps);
newdim=dim+0x10;
fwrite(&newdim,4,1,cps);
fwrite(&dim,4,1,cps);
fputc(0x00,cps);
fputc(0x00,cps);
fputc(0x00,cps);
fputc(0x00,cps);
//scrivo il file
fwrite(buffer,dim,1,cps);
fclose(cps);
}
}


