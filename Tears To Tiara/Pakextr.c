#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    FILE *pak,*ext,*table;
    unsigned long int lunghezza,num,i,puntatore,len,off;
    unsigned char stringa[500],nome[24];
    if (argc < 2) printf("Tears Of Tiara Pak Extractor by Vash v0.9 -www.romhacking.it-\n\npakextr file.pak\n\n");
      else{


      pak=fopen(argv[1],"r+b");
      lunghezza=strlen(argv[1]);
      sprintf(stringa, "%s",argv[1]);
      stringa[lunghezza-4]=0;
      mkdir(stringa);
      chdir(stringa);
      table=fopen("table","w+b");
      fseek(pak,4,SEEK_SET);
      fread(&num,4,1,pak);
      num--;
      fwrite(&num,4,1,table);
      fseek(pak,4,SEEK_CUR);
      off=ftell(pak);
      for (i=0;i<num;i++)
      {
        fseek(pak,off,SEEK_SET);
        fread(nome,24,1,pak);
        fread(&puntatore,4,1,pak);
        fread(&len,4,1,pak);
        fseek(pak,4,SEEK_CUR);
        off=ftell(pak);
        ext=fopen(nome,"w+b");
        fwrite(nome,24,1,table);
        printf("%s\\%s\n",stringa,nome);
        fseek(pak,puntatore,SEEK_SET);
        fread(buffer,len,1,pak);
        fwrite(buffer,len,1,ext);
        fclose(ext);
        }
}}           
           
