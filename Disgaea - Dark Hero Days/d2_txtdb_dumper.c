//Disgaea 2 Dark Hero Days InProgramTxtDB.dat Dumper by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main()
{
FILE *dump,*dat;
unsigned long int num,i,len,off;
   
printf("Disgaea 2 Dark Hero Days InProgramTxtDB.dat Dumper by Vash v0.9\n\n");    
if (fopen("InProgramTxtDB.dat","r+b") == 0)
{
printf("Impossibile trovare o aprire il file InProgramTxtDB.dat\n");
return(0);
}
dat=fopen("InProgramTxtDB.dat","r+b");
dump=fopen("InProgramTxtDB.txt","w+b");
fread(&num,4,1,dat);
fseek(dat,8,SEEK_SET);
for (i=0;i<num;i++)
{
off=ftell(dat);    
fread(buffer,0x500,1,dat);
len=strlen(buffer);
fwrite(buffer,len,1,dump);
fprintf(dump,"\n");
fseek(dat,off+len+2,SEEK_SET);    
}    
}    
