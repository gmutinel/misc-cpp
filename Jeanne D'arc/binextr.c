/*Jeanne D'Arc BIN Dumper by Vash*/
#include <stdio.h>
#include <windows.h>

BYTE buffer[1048576];
int main(int argc, char *argv[])
{
    FILE *bin, *txt, *shit;
    unsigned long int lunghezza, hsize, psize, ssize,num,pointers[1500],temp,i,c=1,len;
    unsigned char stringa[250];
    if (argc < 2) printf("Jeanne D'Arc BIN Dumper v0.9 by Vash\n\nbinextr file.bin \n\n");
     else {
          bin=fopen(argv[1],"r+b");
          fseek(bin,0x08,SEEK_SET);
          fread(&temp,4,1,bin);
          if (temp == 0x00)
          {
              printf("No text in thise file, sorry\n");
              
              return(0);
              }     
          rewind(bin);
          lunghezza=strlen(argv[1]);
          sprintf(stringa,"%s",argv[1]);
          stringa[lunghezza-4]=0;
          sprintf(stringa, "%s.txt",stringa);
          txt=fopen(stringa,"w+b");
          stringa[lunghezza-4]=0;
          sprintf(stringa, "%s.shit",stringa);
          shit=fopen(stringa,"w+b");
          fread(&hsize,4,1,bin);
          fread(&ssize,4,1,bin);
          fseek(bin,0x10,SEEK_CUR);
          fread(&psize,4,1,bin);
          fseek(bin,0x10,SEEK_SET);
          fread(&num,4,1,bin);
          fseek(bin,hsize,SEEK_SET);
          fread(&pointers[0],4,1,bin);
          for (i=1;i<num;i++)
          {
            fread(&temp,4,1,bin);
            if (pointers[c-1] !=  temp)
             {
               pointers[c]=temp;
               c++;
               //printf("%d",c);
               //system("pause");
               }
            }
          fseek(bin, (hsize+psize+ssize),SEEK_SET);
          //printf("numero di P:  %x (%d)\nnumero di P utili:  %x (%d)\n",num,&c);
          for (i=0;i<c;i++)
          {
            fseek(bin,(hsize+psize+ssize)+pointers[i],SEEK_SET);
            fread(stringa,0x50,1,bin);
            len=strlen(stringa);
            fwrite(stringa,len,1,txt);
            fprintf(txt,"\n\n");
            
            }
          fseek(bin,(hsize+psize),SEEK_SET);
          fread(buffer,ssize,1,bin);
          fwrite(buffer,ssize,1,shit);
          
          
          
          }}  
                                    
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
          
