#include <stdio.h>

unsigned long int Endian_Int_Conversion(unsigned long int dword)
{
   return ((dword>>24)&0x000000FF) | ((dword>>8)&0x0000FF00) | ((dword<<8)&0x00FF0000) | ((dword<<24)&0xFF000000);
}

int main(int argc, char *argv[])
{

FILE *bin;
unsigned long int byte[9000],i,num,temp;

bin=fopen(argv[1],"r+b");
fseek(bin,0x00,SEEK_END);
num=ftell(bin)/4;
rewind(bin);
for (i=0;i<num;i++)
{
    fread(&byte[i],4,1,bin);
    
    
}
fclose(bin);
bin=fopen(argv[1],"w+b");
for (i=0;i<num;i++)
{
  temp=Endian_Int_Conversion(byte[i]);
  fwrite(&temp,4,1,bin);  
}
    
}
