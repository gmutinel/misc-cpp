//Tales Of Legendia MCD Unpacker by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    
FILE *mcd,*log,*ext;
unsigned long int type[1000],len[1000],point[1000],num,i,lunghezza,n0=0,n1=0,n2=0,n3=1,tmp,x;
unsigned char stringa[256],name[10];

if (argc < 2) printf("Tales Of Legendia MCD Unpacker by Vash v1.0 -www.romhacking.it-\n\ntol_unmcd file.mcd\n\n");    
      else{   

mcd=fopen(argv[1],"r+b");
fread(buffer,3,1,mcd);
if (buffer[0] == 0x43 && buffer[1] == 0x50 && buffer[2] == 0x53)
{
printf("This file is still compressed. Decompress it first. If you don't know how, you shouldn't have this tool so fuck you\n");    
system("pause");
return(0);    
}
lunghezza=strlen(argv[1]);
sprintf(stringa,"%s",argv[1]);
stringa[lunghezza-4]=0;
mkdir(stringa);
chdir(stringa);
log=fopen("log.bin","w+b");
rewind(mcd);
fread(&num,4,1,mcd);
fseek(mcd,0x10,SEEK_SET);
for (i=0;i<num;i++)
{
fread(&type[i],4,1,mcd);    
fread(&point[i],4,1,mcd);
fread(&len[i],4,1,mcd);
fseek(mcd,4,SEEK_CUR);    
}

for (i=0;i<num;i++)
{
fseek(mcd,point[i],SEEK_SET);
fread(buffer,8,1,mcd);
buffer[8]=0x00;
x=0;
if (buffer[0] == 0x4D && buffer[1] == 0x53 && buffer[2] == 0x47 && buffer[3] == 0x45) //MSGE
{
    x=1;
}

if (buffer[0] == 0x53 && buffer[1] == 0x32 && buffer[2] == 0x42 && buffer[3] == 0x00) //S2B
{
    x=1;
}
if (strcmpi(buffer, "TLPKv150")==0)
{
fread(&tmp,4,1,mcd) ;
fseek(mcd,point[i]+(tmp*0x10)+0x10,SEEK_SET);
fread(buffer,8,1,mcd);
buffer[8]=0x00;
if (strcmpi(buffer, "TLsCrIpT")==0)
{
x=1;    
}      
}   



if (x==0)
{  
sprintf(name,"%d%d%d%d.unkn",n0,n1,n2,n3);    
}else{
sprintf(name,"%d%d%d%d.text",n0,n1,n2,n3);        
}    
ext=fopen(name,"w+b");
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
                             
fseek(mcd,point[i],SEEK_SET);
fread(buffer,len[i],1,mcd);
fwrite(buffer,len[i],1,ext);
fwrite(name,10,1,log);
fwrite(&type[i],4,1,log);
fclose(ext);
} 
   
}}
