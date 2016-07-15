/*The Tales Of Bingwood SPK Dumper by Vash*/
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
BYTE ogg[50*1024*1024];
int main(int argc, char *argv[])
{
    FILE *txt, *spk, *dat, *oggs;
    unsigned char stringa[50];
    unsigned long int lunghezza,num,len,i,shit=0,c=0,off,end;
    
    if (argc < 2) printf("The Tales Of Bingwood SPK Dumper by Vash v0.9 by Vash\n\nspkext file.spk \n\n");
     else {

          spk=fopen(argv[1],"r+b");
          lunghezza=strlen(argv[1]);
          sprintf(stringa, "%s",argv[1]);
          stringa[lunghezza-4]=0;
          sprintf(stringa, "%s.txt",stringa);
          txt=fopen(stringa,"w+b");
          stringa[lunghezza-4]=0;
          sprintf(stringa, "%s.dat",stringa);
          dat=fopen(stringa,"w+b");
          stringa[lunghezza-4]=0;
          sprintf(stringa, "%s.shit",stringa);
          oggs=fopen(stringa,"w+b");
          fread(&num,4,1,spk);
          fwrite(&num,4,1,dat);
          for (i=0;i<num;i++)
          {
            fread(&len,4,1,spk); 
            fread(buffer,len,1,spk);
            fwrite(buffer,len,1,txt);
            fprintf(txt,"\n");
            fread(&len,4,1,spk); 
            fread(buffer,len,1,spk);
            fwrite(buffer,len,1,txt);
            fprintf(txt,"\n\n");
            fread(buffer,0x50,1,spk);
            while (shit!=1)
            {
              if  ((buffer[c]==0x05 && buffer[c+1]==0x00 && buffer[c+2]==0x00 && buffer[c+3]==0x00) || (buffer[c]==0x4F && buffer[c+1]==0x67 && buffer[c+2]==0x67 && buffer[c+3]==0x53))
              {
                  shit=1;
                  }else{
                        c++;}
                        }
                        
                        shit=0;
                        fwrite(&c,4,1,dat);
                        fwrite(buffer,c,1,dat);
                        fseek(spk,-(0x50-c),SEEK_CUR);
                        c=0;
                        }
                        off=ftell(spk);
                        fseek(spk,0x00,SEEK_END);
                        end=ftell(spk);
                        fseek(spk,off,SEEK_SET);
                        fread(ogg,(end-off),1,spk);
                        fwrite(ogg,(end-off),1,oggs);
                        fclose(spk);
                        fclose(txt);
                        fclose(dat);
                        
                        }
                        }
            
            
             
          
          
