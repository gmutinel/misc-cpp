//Disgaea 2 Dark Hero Days LZS Decompressor by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
BYTE recbuf[1000];
int main(int argc, char *argv[])
{
FILE *lzs,*dec;
unsigned long int ulen,clen,flag,lunghezza,i=0,jump,recover;
unsigned char stringa[256],head[4];

if (argc < 2) printf("Disgaea 2 Dark Hero Days LZS Decompressor by Vash v0.9 -www.romhacking.it-\n\nd2_unlzs file.lzs\n\n");
      else{

lzs=fopen(argv[1],"r+b");
lunghezza=strlen(argv[1]);
sprintf(stringa, "%s",argv[1]);
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.dec",stringa);
fread(&head,4,1,lzs);
if (strcmp(head,"dat") != 0)
{
printf("Not a valid LZS file.\n\n");
return(0);  
}
dec=fopen(stringa,"w+b");
fseek(lzs,4,SEEK_SET);
fread(&ulen,4,1,lzs);
fread(&clen,4,1,lzs);
fread(&flag,4,1,lzs);
fread(buffer,clen-0x0C,1,lzs);
while (ftell(dec) < ulen)
{
if (buffer[i] != flag)
{
fputc(buffer[i],dec);
i++;
}else{
jump=buffer[i+1];
recover=buffer[i+2];
//printf("%x : %x J:%x  R:%x\n",ftell(dec),i,jump,recover);
//system("pause");    

if (jump == flag)
{
if (recover == flag)
{
fputc(flag,dec);
i=i+2;
}else{                     
fputc(jump,dec);
fputc(recover,dec);
i=i+3;         
}}else{                  
if (jump > flag)
{
jump--;         
}
fseek(dec,-jump,SEEK_CUR);
fread(recbuf,recover,1,dec);
fseek(dec,0x00,SEEK_END);
fwrite(recbuf,recover,1,dec);
i=i+3;  }          
}      
}
}}
