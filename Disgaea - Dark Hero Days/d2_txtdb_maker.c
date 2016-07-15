//Disgaea 2 Dark Hero Days InProgramTxtDB.dat Maker by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main()
{
FILE *dump,*dat;
unsigned long int num=0,i,len[5000],off,end,temp=0;

printf("Disgaea 2 Dark Hero Days InProgramTxtDB.dat Maker by Vash v0.9\n\n");    
if (fopen("InProgramTxtDB.txt","r+b") == 0)
{
printf("Impossibile trovare o aprire il file InProgramTxtDB.txt\n");
return(0);
}

if (fopen("InProgramTxtDB.dat","w+b") == 0)
{
printf("Impossibile creare il file InProgramTxtDB.dat\n");
return(0);
}

dump=fopen("InProgramTxtDB.txt","r+b");
dat=fopen("InProgramTxtDB.dat","w+b");
fseek(dump,0x00,SEEK_END);
end=ftell(dump);
rewind(dump);
fread(buffer,end,1,dump);
for (i=0;i<end;i++)
{
 if (buffer[i] == 0x0A)
    { 
      len[num]=i-temp;
      temp=i+1;
      num++;         
     }   
}    
rewind(dump);
fwrite(&num,4,1,dat);
fwrite(&num,4,1,dat);
for (i=0;i<num;i++)
{
fread(buffer,len[i],1,dump);
fwrite(buffer,len[i],1,dat);
fputc(0x00,dat);
fputc(0x00,dat);
fseek(dump,1,SEEK_CUR);
}
while ((ftell(dat) % 0x10) != 0)
{
      fputc(0x00,dat);
      }
}
