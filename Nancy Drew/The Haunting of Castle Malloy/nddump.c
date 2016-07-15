/*Nancy Drew: The Haunting Of Castle Malloy Text Dumper by Vash*/
#include <stdio.h>
#include <windows.h>
BYTE buffer[51200];
int main(int argc, char *argv[])
{
      FILE *txt,*lua;
      unsigned long int c=0,pointer,lunghezza,end=0,length;
      unsigned char stringa[250];
      if (argc < 2) printf("Nancy Drew: The Haunting Of Castle Malloy Text Dumper by Vash v0.9\n\nnddump file.cif");
      else {
           
           lua=fopen(argv[1],"r+b");
           fseek(lua,0x3C,SEEK_SET);
           fread(&pointer,4,1,lua);
           fseek(lua,pointer+0x0C,SEEK_CUR);
           fread(&pointer,4,1,lua);
           fseek(lua,(pointer*4)+0x21,SEEK_CUR);
           lunghezza=strlen(argv[1]);
           sprintf(stringa, "%s",argv[1]);
           stringa[lunghezza-4]=0;
           sprintf(stringa, "%s.txt",stringa);
           txt=fopen(stringa,"w+b");
           while (end!=1)
           {//ciclo di estrazione e scrittura del testo
           fseek(lua,1,SEEK_CUR);
           if (fgetc(lua)!=0x04)
           {
               end=1;
               }else{
                     fread(&length,4,1,lua); 
                     fread(buffer,length-1,1,lua);
                     fwrite(buffer,length-1,1,txt);
                     fprintf(txt,"\n\n");
                     /*c++;
                     if (c==2)
                     {
                        c=0;
                        fprintf(txt,"\n");
                        } */     
                     } 
                     }               
                 
           
           
           
      
























}}
