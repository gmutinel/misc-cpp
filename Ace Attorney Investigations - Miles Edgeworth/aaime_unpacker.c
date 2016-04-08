//Ace Attorney Investigations - Miles Edgeworth Unpacker by Vash

#include <stdio.h>
#include <windows.h>
#include "nintendo.h" //<-----thanks aluigi


BYTE buffer[1048576];
BYTE decompr[1048576];

int main(int argc, char *argv[])
{
FILE *bin,*ext;    
unsigned long int num,point[5000],len,n0=0,n1=0,n2=0,n3=1,i,comp,declen,complen;
unsigned char name[10],byte;
printf("Ace Attorney Investigations - Miles Edgeworth Unpacker by Vash v0.98a\n-www.romhacking.it-\n\n");
if (fopen("romfile.bin","r+b") == 0)
{
printf("Impossible to find/open 'romfile.bin'\n");    
return(0);    
}
if (argv[1] == NULL)
{
mkdir("ROMFILE");
}else{
if (strcmpi(argv[1], "-nd") == 0)
{
mkdir("ROMFILE(NotDec)");
printf("You chose to extract files without decompression. Your loss bro..\n");
}else{
printf("You entered an invalid parameter.\n");
return(0);
}    
}    
bin=fopen("romfile.bin","r+b");
if (argv[1] == NULL)
{    
chdir("ROMFILE");   
mkdir("LZ77");
}else{
chdir("ROMFILE(NotDec)");    
}    
fread(&num,4,1,bin);
num=(num/4)-1;    
fseek(bin,8,SEEK_SET);  
for (i=0;i<num;i++)
{
fread(&point[i],4,1,bin);    
}
fseek(bin,0x00,SEEK_END);
point[i]=ftell(bin);
for (i=0;i<num;i++)
{
fseek(bin,point[i],SEEK_SET);
fread(&len,4,1,bin);
sprintf(name,"%d%d%d%d.dat\0",n0,n1,n2,n3);
printf("\rExtracting file %d on %d (%d byte)      ",i+1,num,len);
//controllo compressione
if (argv[1] == NULL)
{   
byte=fgetc(bin);
fseek(bin,point[i]+5,SEEK_SET); 
fread(&declen,3,1,bin);
if (byte == 0x11)
{
chdir("LZ77");
fseek(bin,point[i]+8,SEEK_SET);
fread(buffer,len-4,1,bin);
fseek(bin,point[i]+8,SEEK_SET);   
//unlz77wii_raw11(compressed_data, compressed_size, uncompressed_data, uncompressed_size);
declen=unlz77wii_raw11(buffer,len,decompr,declen);
if (declen == 0 || declen == -1)
{
chdir(".."); 
ext=fopen(name,"w+b");
fseek(bin,point[i]+4,SEEK_SET); 
fread(buffer,len,1,bin);
fwrite(buffer,len,1,ext);
}else{
ext=fopen(name,"w+b");    
fwrite(decompr,declen,1,ext);  
chdir(".."); 
}
//printf("%x",declen);
}else{    
ext=fopen(name,"w+b");
fseek(bin,-4,SEEK_CUR);    // <--- Thanks Cid
fread(buffer,len,1,bin);
fwrite(buffer,len,1,ext);
}
}else{
ext=fopen(name,"w+b");
fread(buffer,len,1,bin);
fwrite(buffer,len,1,ext);    
}    
fclose(ext);

//aumento variabili del nome
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
printf("\rDone, enjoy it Sadnes!                                       \n");
system("pause");                                          
}    
