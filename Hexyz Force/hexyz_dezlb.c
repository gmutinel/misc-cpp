//Hexyz Force ZLB Extractor

#include <stdio.h>
#include <windows.h>
#include <zlib.h>

BYTE buffer[10485760];
BYTE buffer2[5000000];
int main(int argc, char *argv[])
{
FILE *zlb, *ext;
unsigned long int declen,complen,err;
char name[0x14],head[4];

if (argc < 2) printf("Hexyz Force ZLB Extractor by Vash v0.9\n\n-MADE FOR ELDINEN-\nhexyz_dezlb file.zlb \n\n");
else{
printf("Hexyz Force ZLB Extractor by Vash v0.9\n\n-MADE FOR ELDINEN-\n\n");    
zlb=fopen(argv[1],"r+b");
//Should write some checks..
fread(head,4,1,zlb);
if (head[0] != 0x5A || head[1] != 0x4C || head[2] != 0x42 || head[3] != 0x00 )
{
printf("This isn't a zlb file\n");
return(0);    
}
fseek(zlb,0x0C,SEEK_SET);    
fread(name,0x14,1,zlb);    
fseek(zlb,0x28,SEEK_SET);
fread(&declen,4,1,zlb);
fread(&complen,4,1,zlb);
fseek(zlb,0x34,SEEK_SET);    
fread(buffer,complen,1,zlb);
err=uncompress(buffer2,&declen,buffer,complen);
if (err < 0)
{
printf("Error with decompression: %d. Report please!",err);
return(0);    
}
ext=fopen(name,"w+b");
fwrite(buffer2,declen,1,ext);
fclose(ext);
fclose(zlb);
}

}
