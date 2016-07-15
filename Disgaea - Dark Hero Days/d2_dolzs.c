//Disgaea 2 Dark Hero Days LZS Compressor by Vash (compression 0, I'm lazy)

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
BYTE recbuf[1000];
BYTE newfile[10485760];

int main(int argc, char *argv[])
{
FILE *lzs,*dec;
unsigned long int ulen,clen,flag=0xFF,lunghezza,i=0,c=0,jump,recover,end;
unsigned char stringa[256],head[4]={0x64,0x61,0x74,0x00};

if (argc < 2) printf("Disgaea 2 Dark Hero Days LZS Compressor by Vash v0.9 -www.romhacking.it-\n\nd2_dolzs file.dec\n\n");
      else{

dec=fopen(argv[1],"r+b");
lunghezza=strlen(argv[1]);
sprintf(stringa, "%s",argv[1]);
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.LZS",stringa);
lzs=fopen(stringa,"w+b");
fseek(dec,0x00,SEEK_END);
end=ftell(dec);
rewind(dec);
fwrite(&head,4,1,lzs);
fwrite(&end,4,1,lzs); 
fputc(0x00,lzs);
fputc(0x00,lzs);
fputc(0x00,lzs);
fputc(0x00,lzs);
fwrite(&flag,4,1,lzs);//header creato, dimensione compressa a 0x00 per ora
fread(buffer,end,1,dec); //metto il file decompresso nel buffer
while (i < end)
{
newfile[c]=buffer[i];      
if (buffer[i] == flag)
{
newfile[c+1]=0xFF;           
c=c+1;              
}
i=i+1;
c=c+1;
}
fwrite(newfile,c,1,lzs);
fseek(lzs,8,SEEK_SET);
c=c+0x0C;
fwrite(&c,4,1,lzs);      
}}
