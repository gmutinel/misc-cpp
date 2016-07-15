//Dissidia Final Fantasy Pak Extractor
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

unsigned short int Endian_Short_Conversion(unsigned short int word) 
{ 
      return ((word>>8)&0x00FF) | ((word<<8)&0xFF00) ; 
}

main()
{
FILE *dat, *txt;
unsigned long int pointers[1000],byte,i=0,c,tmplen;


printf("Phantom Brave: We Meet Again StringDatTbl Dumper by Vash v0.9 -www.romhacking.it-\n");

dat=fopen("StringDatTbl.dat","r+b");
byte=0x01;
while (byte != 0x00)
{
fseek(dat,2,SEEK_CUR);
fread(&byte,2,1,dat);
pointers[i]=Endian_Short_Conversion(byte);
//printf("%x - %x\n",pointers[i],byte);
//system("pause");
i++;      
}      
      
txt=fopen("StringDatTbl.txt","w+b");
for (c=0;c<i-1;c++)
{
fseek(dat,pointers[c],SEEK_SET);

fread(buffer,0x100,1,dat);
tmplen=strlen(buffer);
fwrite(buffer,tmplen,1,txt);
fprintf(txt,"\n");    
}          
}
