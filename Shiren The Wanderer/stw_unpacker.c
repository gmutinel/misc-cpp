//Shiren The Wonderer Unpacker

#include <stdio.h>
#include <windows.h>

unsigned long int Endian_Int_Conversion(unsigned long int dword)
{
   return ((dword>>24)&0x000000FF) | ((dword>>8)&0x0000FF00) | ((dword<<8)&0x00FF0000) | ((dword<<24)&0xFF000000);
}
BYTE buffer[10485760];
main()
{
FILE *body,*direntry,*ext;    
unsigned long int num,i,point[2500],check;
unsigned char name[2500][29],byte;
unsigned short int parlen;   

printf("Shiren The Wonderer Body.dat Unpacker by Vash v0.9 -www.romhacking.it-\n\n");    
if (fopen("body.dat","r+b") == 0)
{
printf("Body.dat not found or in use by another program\n");
system("pause");
return(0);    
}    
body=fopen("body.dat","r+b");
if (fopen("direntry.dat","r+b") == 0)
{
printf("Direntry.dat not found or in use by another program\n");
system("pause");
return(0);    
}    
direntry=fopen("direntry.dat","r+b");
fread(&num,4,1,direntry);
num=Endian_Int_Conversion(num);
fseek(direntry,0x20,SEEK_SET);
for (i=0;i<num;i++)
{
fread(name[i],0x1C,1,direntry);   
name[i][0x1C]=0; 
fread(&point[i],4,1,direntry);
point[i]=Endian_Int_Conversion(point[i]);   
//printf("%d:%x\n",i,point[i]); 
//system("pause");
}
//printf("%s\n",name[0]); 
//system("pause");
fclose(direntry);
mkdir("Body");
chdir("Body");
//comincio estrazione
 
    
for (i=0;i<num;i++)
{
fseek(body,point[i],SEEK_SET);   
fseek(body,4,SEEK_CUR);
byte=fgetc(body);      
fread(&parlen,2,1,body);
if (byte==0x58)
{
parlen=parlen-0x10;
} 
fseek(body,9,SEEK_CUR);
printf("%s\n",name[i]);
ext=fopen(name[i],"w+b");
fread(buffer,parlen,1,body);
fwrite(buffer,parlen,1,ext);    
check=0;
while (check != 1)
{
fread(buffer,5,1,body);
//printf("%x (%x)- %x%x%x%x%x\n",ftell(body),parlen,buffer[0],buffer[1],buffer[2],buffer[3],buffer[4]);
//system("pause");
if (buffer[0] == 0x41 && buffer[1] == 0x54 && buffer[2] == 0x33 && buffer[3] == 0x50 && buffer[4] == 0x45)
{
check=1;
fclose(ext);        
}else{
fread(&parlen,2,1,body);
if (buffer[4]==0x58)
{
parlen=parlen-0x10;
} 
fseek(body,9,SEEK_CUR);
fread(buffer,parlen,1,body);
fwrite(buffer,parlen,1,ext);   

    
}           
}    
}    
}    
