#include "onz_lib.h"
#include <stdio.h>
#include <windows.h>
#include <unistd.h>

//BYTE buffer2[1048576];
//BYTE decompr[1048576];
BYTE buffer2[10000000];
int main(int argc, char *argv[])
{
FILE *bin,*ext;  
unsigned long int num=4534,pointin=0x00000000,i,n0=0,n1=0,n2=0,n3=1,declen,tmp,point[5000];
char name[9];
unsigned int len[50000];
u8* decompr=NULL;
u8* buffer=NULL;

printf("Ace Attorney Investigations - Miles Edgeworth Packer by Vash v0.9\n-www.romhacking.it-\n\n");
bin=fopen("romfile.bin","w+b");
/*if (strcmpi(argv[1], "-nd") != 0)
{*/
chdir("ROMFILE");
//system("cd ROMFILE");
/*}else{
chdir("ROMFILE(NotDec)");
//system("cd ROMFILE(NotDec)");
}
system("pause");
*/
tmp=(num+1)*4;
fwrite(&tmp,4,1,bin); //scrivo head
for (i=0;i<num+1;i++)  //pointer vuoti
{
fwrite(&pointin,4,1,bin);
}
//system("pause");
for (i=0;i<num;i++)  //file
{
sprintf(name,"%d%d%d%d.dat\0",n0,n1,n2,n3);
ext=fopen(name,"r+b");
if (ext)
{
//fclose(ext);    
//ext=fopen(name,"r+b");
if (!(ext))
{
 perror("si è verificato il seguente errore");
system("pause");
}
printf("%s  ",name);
fseek(ext,0,SEEK_END);
len[i]=ftell(ext);
printf("%x\n",len[i]);
if(len[i]==-1)
{
    perror("si è verificato il seguente errore");
fclose(ext);    
ext=fopen(name,"r+b");
printf("%s  ",name);
fseek(ext,0,SEEK_END);
len[i]=ftell(ext);
printf("%x\n",len[i]);
system("pause");
}

rewind(ext);
fread(buffer2,len[i],1,ext);
fwrite(&len[i],4,1,bin);
fwrite(buffer2,len[i],1,bin);
fclose(ext);
}else{
chdir("LZ77");    
ext=fopen(name,"r+b");
printf("%s\n",name);
fseek(ext,0,SEEK_END);    
declen=ftell(ext);
rewind(ext);
//buffer=new u8[declen];
buffer = (u8 *)malloc(declen);
if (!buffer) printf("malloc fail @ line %i\n", __LINE__);
fread(buffer,declen,1,ext);
//system("pause");
decompr=onz_compress(buffer,declen,&len[i],DS);
fwrite(&len[i],4,1,bin);
fwrite(decompr,len[i],1,bin);
fclose(ext);
free(buffer);
chdir("..");

//system("cd ..");
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
//aggiornare puntatori
fseek(bin,8,SEEK_SET);
point[0]=tmp+4;
for (i=1;i<num;i++)
{
fwrite(&point[i-1],4,1,bin);    
point[i]=point[i-1]+len[i-1]+4;    
}
}
