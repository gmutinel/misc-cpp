//Arc Rise Fantasia CXD Decompressor by Vash

#include <windows.h>
#include <stdio.h>

BYTE buffer[1024];

int main(int argc, char *argv[])
{
    FILE *cxd,*vol;
    unsigned long int c,lunghezza,DecDim,end,off=0x00,flag,i,byte,recover,jump,nib1,nib2,x;
    unsigned short int bit[8];
    unsigned char stringa[500];
    if (argc < 2) printf("Arc Rise Fantasia CXD Decompressor by Vash v0.9 -www.romhacking.it-\nThanks Phoenix (www.sadnescity.it)\n\narf_cxd_dec file.cxd\n\n");
      else{

printf("Arc Rise Fantasia CXD Decompressor by Vash v0.9 -www.romhacking.it-\nThanks Phoenix (www.sadnescity.it)\n\n");
cxd=fopen(argv[1],"r+b");
lunghezza=strlen(argv[1]);
sprintf(stringa, "%s",argv[1]);
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.vol",stringa);
vol=fopen(stringa,"w+b");

fseek(cxd,1,SEEK_SET);
fread(&DecDim,3,1,cxd);
fseek(cxd,0x00,SEEK_END);
end=ftell(cxd);
fseek(cxd,4,SEEK_SET);
while (off < end)
{
flag=fgetc(cxd);    
for (i=0;i<8;i++)
{
bit[i]=(flag>>(7-i))&0x1;
}

for (i=0;i<8;i++)
{
    
if (bit[i] == 0)
{
byte=fgetc(cxd);
fputc(byte,vol);    
}

if (bit[i] == 1)
{
recover=fgetc(cxd);
nib1=recover/0x10;
nib2=recover-(nib1*0x10);
recover=nib1+3;
jump=fgetc(cxd);
jump=(nib2*0x100)+jump;
jump=jump+1;
if (jump >= recover)
{
fseek(vol,-jump,SEEK_CUR);
fread(buffer,recover,1,vol);
fseek(vol,0x00,SEEK_END);
fwrite(buffer,recover,1,vol);
}else{
fseek(vol,-jump,SEEK_CUR);
fread(buffer,jump,1,vol); 
fseek(vol,0x00,SEEK_END);
x=0; 
for (c=0;c<recover;c++)
{
//printf("JUMP: %x - X= %x - CHAR: %c\n",jump,x);     
fputc(buffer[x],vol);
x++;
if (x>=jump)
{x=0;}
 
}   
}
/*
if (ftell(vol) >= 0x1AC0)
{
printf("VOL OFF=0x%X\nFLAG= 0x%X\nRECOVER= 0x%X\nJUMP= 0x%X\nCXD OFF= 0x%X\n\n",ftell(vol),flag,recover,jump,ftell(cxd));    
system("pause");    
} */
}
    
}
off=ftell(cxd);   

}


}}
