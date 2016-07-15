/*The Tales Of Bingwood SPK Reinserter by Vash*/
#include <stdio.h>
#include <windows.h>

BYTE buffer[104857600];
BYTE ogg[50*1024*1024];
int main(int argc, char *argv[])
{
    FILE *txt, *spk, *dat, *oggs;
    unsigned char stringa[50];
    unsigned long int lunghezza,num,len,i,shit=0,c=0,end,off;
    
    if (argc < 2) printf("The Tales Of Bingwood SPK Reinserter by Vash v0.1 by Vash\n\nspkext file.txt \n\n");
     else {
          
          txt=fopen(argv[1],"r+b");
          lunghezza=strlen(argv[1]);
          sprintf(stringa, "%s",argv[1]);
          stringa[lunghezza-4]=0;
          sprintf(stringa, "%s.spk",stringa);
          spk=fopen(stringa,"w+b");
          stringa[lunghezza-4]=0;
          sprintf(stringa, "%s.dat",stringa);
          dat=fopen(stringa,"r+b");
          stringa[lunghezza-4]=0;
          sprintf(stringa, "%s.shit",stringa);
          oggs=fopen(stringa,"r+b");
          fseek(txt,0x00,SEEK_END);
          end=ftell(txt);
          rewind(txt);
          fread(&num,4,1,dat);
          fwrite(&num,4,1,spk);
          for (i=0;i<num;i++)
          {
             len=0x05;//lunghezza tag evento
             fwrite(&len,4,1,spk);//scrittura lunghezza tag evento
             fread(buffer,len,1,txt);//lettura tag evento 
             fwrite(buffer,len,1,spk);//scrittura tag evento
             fseek(txt,1,SEEK_CUR);//spostamento di 1 a causa dello 0x0A
             off=ftell(txt);
             fread(buffer,(end-off),1,txt);//lettura di tutto il file dalla posizione attuale alla fine in un buffer per calcolare la lunghezza della stringa
             fseek(txt,off,SEEK_SET);//ritorno allo stato originario prima della lettura
            while (shit!=1)
            {
              if  (buffer[c]==0x0A && buffer[c+1]==0x0A)
              {
                  shit=1;
              }else{
                        c++;
                    }
            }
              fwrite(&c,4,1,spk);//scrittura della lunghezza della stringa
              fread(buffer,c,1,txt);//lettura della stringa
              fwrite(buffer,c,1,spk);//scrittura della stringa
              fseek(txt,2,SEEK_CUR);//spostamento di due a causa di 0x0A0A
              fread(&len,4,1,dat);//lettura della lunghezza della stringa post-testo
              fread(buffer,len,1,dat);//lettura della stringa post-testo
              fwrite(buffer,len,1,spk);//scrittura della stringa post-testo
              shit=0;
              c=0;
              }
              fseek(oggs,0x00,SEEK_END);
              end=ftell(oggs);
              rewind(oggs);
              fread(ogg,end,1,oggs);
              fwrite(ogg,end,1,spk);
              
              
              
              }
              }
