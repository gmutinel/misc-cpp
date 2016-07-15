/*Nancy Drew: Phantom Of Venice Text Dumper by Vash*/
#include <stdio.h>
#include <windows.h>
BYTE buffer[51200];
int main(int argc, char *argv[])
{
      FILE *txt,*cif;
      unsigned long int i,pointer,lunghezza,end=0;
      unsigned char stringa[250];
      char event[33];
      short int num,length;
      if (argc < 2) printf("Nancy Drew: Phantom Of Venice Text Dumper by Vash v0.1\n\nnddump file.cif");
      else {
           
           cif=fopen(argv[1],"r+b");
           lunghezza=strlen(argv[1]);
           sprintf(stringa, "%s",argv[1]);
           stringa[lunghezza-4]=0;
           sprintf(stringa, "%s.txt",stringa);
           txt=fopen(stringa,"w+b");
           fseek(cif,0x44,SEEK_SET);
           fread(&num,2,1,cif);
           printf("%x\n",num);
           for(i=0;i<num;i++)
           {
             fread(event,33,1,cif);
             fprintf(txt,"%s",event);
             fprintf(txt,"\n");
             fread(&length,2,1,cif);
             fread(buffer,length,1,cif);
             fwrite(buffer,length,1,txt);
             fprintf(txt,"\n\n");
             }                           
                 
           
           
           
      
























}}
