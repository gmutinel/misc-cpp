#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

BYTE buffer[32];
main()
{
FILE *log, *tmp;
unsigned long int randkey, key[32],i,end,c=0,num,same;
unsigned char bat[500],byte=0x22,tmpkey[32],checkkey[32];      
mkdir("Extr");
chdir("Extr");
if (fopen("keys.txt","r+b"))
{
log=fopen("keys.txt","r+b");
fseek(log,0x00,SEEK_END);
}else{                            
log=fopen("keys.txt","w+b");
}
chdir("..");
while (c!=1)
{
srand(clock());      
//srand ( rand() % 274589 );
sprintf(bat,"simpack x %cLeft 4 Dead 2_disk1.sim%c Extr -g552 -k",byte,byte);
for (i=0;i<32;i++)
{
randkey=rand() % 16;
key[i]=randkey;
//tmpkey[i]=key[i];
sprintf(bat,"%s%X",bat,key[i]);
}

//controllo chiavi già usate
key[32]='\0';
for (i=0;i<32;i++)
{
fprintf(log,"%X",key[i]);
}
fseek(log,-32,SEEK_CUR);
fread(buffer,32,1,log);

buffer[32]='\0';
num=(ftell(log)/33);
rewind(log);
same=0;

for (i=0;i<num;i++)
{
fread(&checkkey,32,1,log);
checkkey[32]='\0';
//printf("\n\na- %s\n",buffer);
//printf("b- %s\n\n",checkkey);
//system("pause");
if (strcmp(checkkey,buffer) == 0)
{
same==1;
i=num;
//system("pause");
}
fseek(log,1,SEEK_CUR);                           
}
fseek(log,0x00,SEEK_END);
fseek(log,-32,SEEK_CUR);
if (same != 1)
{
system(bat);
printf("%s\n",bat);
chdir("Extr");
tmp=fopen("left4dead2\\media\\l4d2_background01.bik","r+b");
fseek(tmp,0x00,SEEK_END);
end=ftell(tmp);
fclose(tmp);
if(end==0)
{
system("del /q /s left4dead2\\media\\l4d2_background01.bik");
system("rmdir /q /s left4dead2\\media");
system("rmdir /q /s left4dead2");
//system("rmdir /q /s bin");
chdir("..");
for (i=0;i<32;i++)
{
fprintf(log,"%X",key[i]);
}
fprintf(log,"\n");
}else{
for (i=0;i<32;i++)
{
fprintf(log,"%X",key[i]);
}
fprintf(log,"<---VALID!!!\n");
return(0);      
}
}
}}
