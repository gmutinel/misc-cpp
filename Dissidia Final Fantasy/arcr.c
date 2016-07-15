//Dissidia Final Fantasy Arc Creator
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
  FILE *arc,*ext,*tbl;
  unsigned long int num,i,peso[500],off=0;
  unsigned char stringa[1500],halfhead[500][8],nome[500][11],header[16]={0x41,0x52,0x43,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    
    if (argc < 2) printf("Dissidia Final Fantasy Arc Creator by Vash v0.7 -www.romhacking.it-\n\narcr directory\n\n");
      else{
           
    sprintf(stringa,"%s.arc\0",argv[1]);
    arc=fopen(stringa,"w+b");
    chdir(argv[1]);
    tbl=fopen("table","r+b");  
    fread(&num,4,1,tbl);
    
    for (i=0;i<num;i++)
    {
      fread(halfhead[i],8,1,tbl);
      }
     for (i=0;i<num;i++)
    {
      fread(nome[i],10,1,tbl);
      nome[i][10]=0;
      }         
   for (i=0;i<num;i++)
    {
      ext=fopen(nome[i],"r+b");
      fseek(ext,0x00,SEEK_END);
      peso[i]=ftell(ext);
      fclose(ext);
      }
   
  fwrite(header,16,1,arc);
  fseek(arc,0x04,SEEK_SET);     
  fwrite(&num,4,1,arc);
  fseek(arc,0x00,SEEK_END);
  off=(num*0x10)+0x10;
  for (i=0;i<num;i++)
    {
  fwrite(halfhead[i],8,1,arc);
  fwrite(&off,4,1,arc);                   
  fwrite(&peso[i],4,1,arc);
  off=off+peso[i];
}
for (i=0;i<num;i++)
    {
      ext=fopen(nome[i],"r+b");
      fread(buffer,peso[i],1,ext);
      fwrite(buffer,peso[i],1,arc);            
      while ((ftell(arc) % 4) != 0)
      {
        fputc(0x00,arc);
        }    
      fclose(ext);
}
  
  
  
  
}}           
