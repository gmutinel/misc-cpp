//ToD2 file.fpb Offsets file Revealer

#include <stdio.h>
#include <windows.h>

BYTE buffer[1048576];

main()
{

FILE *fpb;
unsigned long int end,off=0x00,i=1,byte=0x00,dim;

fpb=fopen("file.fpb","r+b");
fseek(fpb,0x00,SEEK_END);
end=ftell(fpb);
rewind(fpb);
while (off < end)
{
   
   byte=0x00; 
   off=ftell(fpb);
   fseek(fpb,1,SEEK_CUR);
   fread(&dim,4,1,fpb);
   printf("%d\t0x%x\t0x%x\n",i,off,dim);
   fseek(fpb,4,SEEK_CUR);
   fseek(fpb,dim,SEEK_CUR);
   i++;
 while (byte==0x00 && off < end)
   {
      byte=fgetc(fpb);
      if (byte!=0x00)
      {
         fseek(fpb,-1,SEEK_CUR);
         }                     
    } 
}
}
