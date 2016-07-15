//Nostalgia (USA) MSD Dumper by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
BYTE buffer2[10485760];
int main(int argc, char *argv[])
{
    FILE *msd,*tbl,*dump;
    unsigned long int i,lunghezza,num,point[3000],len[3000],c;
    unsigned char stringa[256],junk[8];
    if (argc < 2) printf("Nostalgia (USA) MSD Dumper by Vash v0.9 -www.romhacking.it-\n\nmsd_dumper file.msd\n\n");
      else{
           
msd=fopen(argv[1],"r+b");
lunghezza=strlen(argv[1]);
sprintf(stringa, "%s",argv[1]);
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.txt",stringa);
dump=fopen(stringa,"w+b");
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.tbl",stringa);
tbl=fopen(stringa,"w+b");
fseek(msd,8,SEEK_SET);
fread(&num,4,1,msd);
fseek(msd,0x10,SEEK_SET);
for (i=0;i<num;i++)
{
fread(&junk,8,1,msd);
fread(&point[i],4,1,msd);
fwrite(&junk,8,1,tbl);
}    
fseek(msd,0x00,SEEK_END);
point[i]=ftell(msd);    
for (i=0;i<num;i++)
{
len[i]=point[i+1]-point[i];
fseek(msd,point[i],SEEK_SET);
fread(buffer,len[i],1,msd);
//len[i+1]=point[i+2]-point[i+1];
//fseek(msd,point[i+1],SEEK_SET);
//fread(buffer2,len[i+1],1,msd);
//scrivo chi parla
/*c=0;
while (c < len[i+1])
{
if (buffer2[c] != 0x00)
{      
fputc(buffer2[c],dump); 
}
c=c+2; 
}
fprintf(dump,"\n");*/
//scrivo il testo
c=0;
while (c < len[i])
{
if (buffer[c] != 0x00)
{      
fputc(buffer[c],dump); 
}
c=c+2; 
}  
fprintf(dump,"\n\n");      
}

}}
