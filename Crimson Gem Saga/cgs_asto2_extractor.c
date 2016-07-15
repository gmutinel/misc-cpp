//Crimson Gem Saga Asto2.dat Extractor/Decompressor by Vash

#include <stdio.h>
#include <windows.h>
#include <zlib.h>



BYTE buffer[10485760];
BYTE buffer2[5000000];
BYTE tempb[2621440];

main()
{
FILE *dat, *ext, *log;      
unsigned long int num,len[2500],point[2500],i,check,c,x,q,chlen,off,chsize=262144,err=5763,size;
unsigned char name[2500][0x50],temp[0x100],byte;      
uLongf maxsize=262144;

printf("Crimson Gem Saga Extractor by Vash v0.9 -www.romhacking.it-\n\n");
if (fopen("asto2.dat","r+b") == 0)
{
printf("Can't open asto2.dat\n");
return(0);
}else{
dat=fopen("asto2.dat","r+b");      
mkdir("Asto2");
chdir("Asto2");
log=fopen("asto2.tbl","w+b");
fread(&num,4,1,dat);
//raccolgo nomi dei file, puntatori e dimensioni
for (i=0;i<num;i++)
{
fread(&temp,0x100,1,dat);    
//metto a posto il nome del file (con relativo path)
check=0;
c=0;
while (check != 1)
{
if (temp[c] == 0x00 && temp[c+1] == 0x00)       
{
check=1;
}
c=c+2;
}
q=0;           
for (x=0;x<c/2;x++)
{
name[i][x]=temp[q];
q=q+2;
}

//system("pause");
fread(&point[i],4,1,dat);
fread(&len[i],4,1,dat);
//printf("%d\n",len[i]);
}
//estrazione dei file e relative sottocartelle
for (i=0;i<num;i++)
{
fseek(dat,point[i],SEEK_SET);
fread(buffer,len[i],1,dat);
byte=0x01;
q=0;
x=0;
while (byte != 0x00)
{      
byte=name[i][q];
q=q+1;
if (byte == 0x2F)
{
x=x+1;   // numero di sottocartelle       
}              
}          
q=0;
for (c=0;c<x;c++) //creazione sottocartelle
{
sprintf(temp,"\0");    
byte=0x01;
while (byte != 0x2F)
{      
byte=name[i][q];
//printf("%c",byte);  
if (byte != 0x2F)
{
sprintf(temp,"%s%c",temp,byte);
}
q=q+1;
}
sprintf(temp,"%s\0",temp);
//printf("\n%s\n",temp);
//system("pause");  
mkdir(temp);
chdir(temp);
}
sprintf(temp,"\0");
//temp=\0;
//recupero solo nome del file
byte=0x01;
while (byte != 0x00)
{      
byte=name[i][q];  
sprintf(temp,"%s%c",temp,byte);
q=q+1;
}
//e finalmente lo scrivo   
ext=fopen(temp,"w+b");
printf("%s",name[i]); 
//scrivo il log (0 non compresso, 1 compresso, vedi header 0x7A6C6962)
fwrite(name[i],0x50,1,log);
if (buffer[0]==0x7A && buffer[1]==0x6C && buffer[2]==0x69 && buffer[3]==0x62)
{
fputc(0x01,log);
printf("    (Compression found...decompressing....");
fseek(dat,point[i]+0x04,SEEK_SET);
off=ftell(dat);
//printf("\n%x - %x\n",off,point[i]+len[i]); 
while (off < (point[i]+len[i]))
{
maxsize=262144;      
fread(&chlen,4,1,dat);
fread(buffer2,chlen,1,dat); 
//printf("%d",&maxsize);                
err=uncompress(tempb,&maxsize,buffer2,chlen);
//printf("%d",err);
fwrite(tempb,maxsize,1,ext);
off=ftell(dat);
//printf("%x\n",maxsize);
}
printf("done\n");
//system("pause");
} else {
printf("    (Compression not found)\n");
fputc(0x00,log);
fwrite(buffer,len[i],1,ext);      
}                          
//log scritto
fclose(ext);
for (c=0;c<x;c++)
{
chdir("..");    
}    
}
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}    
}      
