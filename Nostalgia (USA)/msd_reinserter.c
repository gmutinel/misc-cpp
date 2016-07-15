//Nostalgia (USA) MSD Reinserter by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
BYTE buffer2[10485760];
int main(int argc, char *argv[])
{
    FILE *msd,*tbl,*dump;
    unsigned long int lunghezza,num,i,lendump,c=0,x,point;
    unsigned char stringa[256],junk[8],head[8]={0x4D,0x53,0x44,0x41,0x00,0x00,0x01,0x00};
    
    if (argc < 2) printf("Nostalgia (USA) MSD Reinserter by Vash v0.9 -www.romhacking.it-\n\nmsd_reinserter file.txt\n\n");
      else{

dump=fopen(argv[1],"r+b");
lunghezza=strlen(argv[1]);
sprintf(stringa, "%s",argv[1]);
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.tbl",stringa);
tbl=fopen(stringa,"r+b");
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.msd",stringa);
msd=fopen(stringa,"w+b");
fwrite(&head,8,1,msd);
fseek(tbl,0x00,SEEK_END);
num=ftell(tbl)/8;
rewind(tbl);
fwrite(&num,4,1,msd);
fputc(0x00,msd);
fputc(0x00,msd);
fputc(0x00,msd);
fputc(0x00,msd);
for (i=0;i<num;i++)
{
 fread(&junk,8,1,tbl);
 fwrite(&junk,8,1,msd);
 fputc(0x00,msd);
 fputc(0x00,msd);
 fputc(0x00,msd);
 fputc(0x00,msd);   
}    
fseek(dump,0x00,SEEK_END);
lendump=ftell(dump);
rewind(dump);
fread(buffer,lendump,1,dump);
for (i=0;i<num;i++)
{
point=ftell(msd);    
x=0;
while (buffer[c] != 0x0A || buffer[c+1] != 0x0A)
{
buffer2[x]=buffer[c];
buffer2[x+1]=0x00;
x=x+2;
c=c+1;
}
c=c+2;        
buffer2[x]=0x00;
buffer2[x+1]=0x00;
buffer2[x+2]=0x00;
buffer2[x+3]=0x00;
buffer2[x+4]=0x00;
fwrite(buffer2,x+4,1,msd);
fseek(msd,(i*0x0C)+0x18,SEEK_SET);
fwrite(&point,4,1,msd);
fseek(msd,0x00,SEEK_END);
}    

}}
