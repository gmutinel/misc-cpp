//Tales Of Legendia MCD Maker by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
FILE *mcd,*ext,*log;
unsigned long int num,type[500],len[500],point[500],endfile,i;
unsigned char stringa[256],name[500][10],padding[4]={0x00,0x00,0x00,0x00};

if (argc < 2) printf("Tales Of Legendia MCD Maker by Vash v1.0 -www.romhacking.it-\n\ntol_mcdmkr dir\n\n");    
      else{   

printf("Tales Of Legendia MCD Maker by Vash v1.0 -www.romhacking.it-\n\n");
sprintf(stringa,"%s.mcd",argv[1]);
mcd=fopen(stringa,"w+b");
chdir(argv[1]);
log=fopen("log.bin","r+b");
fseek(log,0x00,SEEK_END);
num=ftell(log)/14;
rewind(log);
for (i=0;i<num;i++)
{
fread(name[i],10,1,log);
fread(&type[i],4,1,log);
}
fclose(log);
fwrite(&num,4,1,mcd);
fwrite(padding,4,1,mcd); //padding
fwrite(padding,4,1,mcd); //total length
fwrite(padding,4,1,mcd); //padding
for (i=0;i<num;i++)
{
 fwrite(&type[i],4,1,mcd);
 fwrite(padding,4,1,mcd); //pointers
 fwrite(padding,4,1,mcd); //length
 fwrite(padding,4,1,mcd); //padding
}   

for (i=0;i<num;i++)
{
ext=fopen(name[i],"r+b");
fseek(ext,0x00,SEEK_END);
len[i]=ftell(ext);
rewind(ext);
fread(buffer,len[i],1,ext);
point[i]=ftell(mcd);
fwrite(buffer,len[i],1,mcd);
while (ftell(mcd) % 0x10 != 0)
{
fputc(0x00,mcd);    
}
fclose(ext);
}
fwrite(padding,4,1,mcd); //padding
fwrite(padding,4,1,mcd); //padding
fwrite(padding,4,1,mcd); //padding
fwrite(padding,4,1,mcd); //padding
endfile=ftell(mcd);
fseek(mcd,0x08,SEEK_SET);
fwrite(&endfile,4,1,mcd);
fseek(mcd,0x14,SEEK_SET);
for (i=0;i<num;i++)
{
fwrite(&point[i],4,1,mcd);
fwrite(&len[i],4,1,mcd);
fseek(mcd,0x08,SEEK_CUR);    
}

fclose(mcd);
}}
