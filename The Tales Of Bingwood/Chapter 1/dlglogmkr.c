/*The Tales Of Bingwood DLG Log Maker by Vash*/
#include <stdio.h>
#include <windows.h>
#include <string.h>

BYTE buffer[1048576];
int main(int argc, char *argv[])
{
    
    FILE *dat;
    unsigned long int off=0x01,byte,lastbyte,end;
    unsigned char stringa[50];
    //printf("Inserisci il nome del file che vuoi analizzare, senza estensione:  ");
    //scanf("%s\n",stringa);
    if (argc < 2) printf("The Tales Of Bingwood DLG Log Maker by Vash v0.9 by Vash\n\nadvext file.log \n\n");
     else {
    if (fopen(argv[1],"r+b")==NULL)
    {
       dat=fopen(argv[1],"w+b");
       }else{
           
           dat=fopen(argv[1],"r+b");
           fseek(dat,-4,SEEK_END);
           fread(&lastbyte,4,1,dat);
           printf("L'ultimo off inserito e' 0x%x\n",lastbyte+4);
           fseek(dat,0x00,SEEK_END);
           end=ftell(dat);
           rewind(dat);
           fread(buffer,end,1,dat);
           fclose(dat);
           dat=fopen(argv[1],"w+b");
           fwrite(buffer,end,1,dat);           
           }                                
    while (byte!=0)
    {
          printf("Inserisci l'offset: 0x");
          scanf("%x",&byte);
          if (byte!=0)
          {
          byte=byte-4;
          fwrite(&byte,4,1,dat);
          system("cls");
          printf("\nL'ultimo off inserito e' 0x%x\n",byte+4);
          }
          }
          fclose(dat);
          }}
           
