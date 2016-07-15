#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
BYTE buffer2[10485760];

unsigned long int Endian_Int_Conversion(unsigned long int dword)
{
   return ((dword>>24)&0x000000FF) | ((dword>>8)&0x0000FF00) | ((dword<<8)&0x00FF0000) | ((dword<<24)&0xFF000000);
}


main()
{
FILE *bin,*tbl,*ext;
unsigned long int num,i,x,c,times,rest,pointer[5000],size[5000],realsize[5000];
unsigned char file[5000][0x80];
char * dirs;
printf("Recettear An Item Shops Tale Data.bin Unpacker by Vash v0.9 -www.romhacking.it-\n\n");
if (fopen("lnkdatas.bin","r+b") == 0)
{
printf("Can't find lnkdatas.bin\n");    
return(0);
}
if (fopen("data.bin","r+b") == 0)
{
system("copy /b data000.bin + data001.bin + data002.bin + data003.bin + data004.bin + data005.bin + data006.bin + data007.bin + data008.bin + data009.bin + data010.bin + data011.bin data.bin");     
}
bin=fopen("data.bin","r+b");
tbl=fopen("lnkdatas.bin","r+b");
mkdir("Data");
chdir("Data");
fread(&num,4,1,tbl);
num=Endian_Int_Conversion(num);
for (i=0;i<num;i++)
{
fread(file[i],0x80,1,tbl);
fread(&realsize[i],4,1,tbl);  
fread(&pointer[i],4,1,tbl);    
fread(&size[i],4,1,tbl);      
realsize[i]=Endian_Int_Conversion(realsize[i]);
pointer[i]=Endian_Int_Conversion(pointer[i]);
size[i]=Endian_Int_Conversion(size[i]);
}

for (i=0;i<num;i++)
{
printf("Extracting %s\n[%d bytes] [%d\\%d]\n\n",file[i],size[i],i+1,num);     
//count number of \ (subdirs)
x=0;
for (c=0;c<strlen(file[i]);c++)
{
if  (file[i][c] == 0x2F)
x++;   
}
//create subdirs
if (x>0)
{
dirs=strtok(file[i],"/");
mkdir(dirs);
chdir(dirs);
for (c=1;c<x;c++)
{
dirs=strtok(NULL,"/");
mkdir(dirs);
chdir(dirs);
}
dirs=strtok(NULL,"/");
ext=fopen(dirs,"w+b");
}else{
ext=fopen(file[i],"w+b");    
}

//create the file
fseek(bin,pointer[i],SEEK_SET);
times=size[i]/10485760;
rest=size[i]%10485760;
for (c=0;c<times;c++)
{
fread(buffer,10485760,1,bin); 
fwrite(buffer,10485760,1,ext);   
}
fread(buffer,rest,1,bin);
fwrite(buffer,rest,1,ext);
fclose(ext);
for (c=0;c<x;c++)
{
chdir("..");    
}    
}
}
