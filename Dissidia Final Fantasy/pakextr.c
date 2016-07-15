//Dissidia Final Fantasy Pak Extractor
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    FILE *pak,*ext,*head;
    unsigned long int lunghezza,n0=0,n1=0,n2=0,n3=1,pointer[500],len[500],i;
    unsigned char stringa[250],nome[8];
    unsigned short int num;
    if (argc < 2) printf("Dissidia Final Fantasy Pak Extractor by Vash v0.9 -www.romhacking.it-\n\npakext file.pak\n\n");
      else{
           
           pak=fopen(argv[1],"r+b");
           lunghezza=strlen(argv[1]);
           sprintf(stringa, "%s",argv[1]);
           stringa[lunghezza-4]=0;
           mkdir(stringa);
           chdir(stringa);
           head=fopen("table","w+b");
           fread(buffer,0x10,1,pak);
           fwrite(buffer,0x10,1,head);
           rewind(pak);
           fseek(pak,0x0A,SEEK_SET);
           fread(&num,2,1,pak);
           fseek(pak,0x10,SEEK_SET);
           for (i=0;i<num;i++)
           {
             fread(&pointer[i],4,1,pak);
             fread(&len[i],4,1,pak);
             }   
             
           for (i=0;i<num;i++)
           {
              sprintf(nome, "%d%d%d%d.dat\0",n0,n1,n2,n3);
              ext=fopen(nome,"w+b");
              fprintf(head,"%s",nome);
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
              fseek(pak,pointer[i],SEEK_SET);
              fread(buffer,len[i],1,pak);
              fwrite(buffer,len[i],1,ext);
              fclose(ext);
              }
              }}   
