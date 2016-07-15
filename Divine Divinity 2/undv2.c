#include <stdio.h>
#include <windows.h>


BYTE buffer[1048576];

int main(int argc, char *argv[])
{

FILE *dv2,*ext;
unsigned long int pointinit,filenum,i,tmp,lenzl[2500],firstfile,q;
unsigned char name[3000][500];

if (argc < 2) printf("Divinity 2 Ego Draconis *.dv2 Extractor by DarkVash -www.romhacking.it-\n\nundv2 file.dv2");   
else{
     
//system("pause");     
dv2=fopen(argv[1],"r+b");  
fseek(dv2,0x06,SEEK_SET);   
fread(&firstfile,4,1,dv2);
fseek(dv2,0x0A,SEEK_SET);

fread(&pointinit,4,1,dv2);     
fseek(dv2,pointinit+0x0E,SEEK_SET);     
fread(&filenum,4,1,dv2);      
fseek(dv2,0x0E,SEEK_SET);     
for (i=0;i<filenum;i++)
{
  fread(buffer,0x500,1,dv2);
  fseek(dv2,-0x500,SEEK_CUR);
  tmp=strlen(buffer);
  fread(name[i],tmp,1,dv2);
  name[i][tmp]=0x00;
  //printf("%s\n",name[i]);
  fseek(dv2,1,SEEK_CUR);
}         
fseek(dv2,pointinit+0x12,SEEK_SET); 
q=firstfile;
for (i=0;i<filenum;i++)
{
fread(&lenzl[i],4,1,dv2);
printf("%s  -  %x\n",name[i],q); 
q=q+lenzl[i];
}       


  
}         
  
    
}
