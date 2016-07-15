//Sands Of Destruction IEAR Unpakcer by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    
    FILE *iear, *ext, *log;
    unsigned long int lunghezza,num,point[5000],len[5000],i,n0=0,n1=0,n2=0,n3=0;
    unsigned char stringa[50],extens[5],name[9];
    
    if (argc < 2) printf("Sands Of Destruction Unpacker by Vash v0.01\n-www.romhacking.it-\n\nsod_iear_unpacker file.iear\n\n");    
      else{
  printf("Sands Of Destruction Unpacker by Vash v0.01\n-www.romhacking.it-\n\n");

if (fopen(argv[1],"r+b") == 0)
{
printf("Impossible to open %s\n\n", argv[1]);
return(0);                   
}
iear=fopen(argv[1],"r+b");
lunghezza=strlen(argv[1]);
sprintf(stringa,"%s",argv[1]);
stringa[lunghezza-4]=0;
mkdir(stringa);
chdir(stringa);
fseek(iear,0x04,SEEK_SET);
fread(&num,4,1,iear);
fseek(iear,0x20,SEEK_SET);
for (i=0;i<num;i++) //ciclo raccolta puntatori e dimensioni
{
fread(&point[i],4,1,iear);
fread(&len[i],4,1,iear);    
}    
log=fopen("log.bin","w+b");
for (i=0;i<num;i++) //ciclo raccolta estensione, dimensione reale e estrazione file
{
fseek(iear,point[i],SEEK_SET);
fread(extens,4,1,iear);
extens[4]=0;
sprintf(name,"%x%x%x%x.%s",n0,n1,n2,n3,extens);
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
ext=fopen(name,"w+b");                   
fwrite(name,9,1,log);
printf ("Extracting %s (%d/%d)\n",name,i+1,num);
fseek(iear,point[i]+0x10,SEEK_SET);
fread(buffer,len[i]-0x10,1,iear);
fwrite(buffer,len[i]-0x10,1,ext);
fclose(ext);
}
printf("\nDone. Enjoy!");   
}}
