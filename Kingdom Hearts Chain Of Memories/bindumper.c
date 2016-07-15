//Kingdom Hearts Chain Of Memories Bin Dumper
#include <stdio.h>
#include <windows.h>
BYTE buffer[100*1024];

int main(int argc, char *argv[])
{
    
   FILE *txt,*bin;
   unsigned long int point,num,c,i,pointers[500],check=0,q=0,lunghezza,filepoint;
   unsigned char checks[3],stringa[350];
   short int frasi;
   if (argc < 2) printf("Kingdom Hearts Chain Of Memories Bin Dumper by Vash v0.9 -www.romhacking.it-\n\ndatext file.bin\n\n");    
      else{ 
      bin=fopen(argv[1],"r+b");
      fread(&point,4,1,bin);
      fseek(bin,point,SEEK_SET);
      fread(checks,3,1,bin);
      checks[3]=0;
      if (memcmp(checks,"MVS\0",3)!=0)
      {
        printf("This file is compressed or useless, move on\n");
        return(0);
        }
      rewind(bin);
      lunghezza=strlen(argv[1]);
      sprintf(stringa,"%s",argv[1]);
      stringa[lunghezza-4]=0;
      sprintf(stringa,"%s.txt",stringa);
      txt=fopen(stringa,"w+b");
      fread(&num,4,1,bin);
      num=(num-0x20)/0x20;
      
      for(i=0;i<num;i++)
      {  
         fseek(bin,i*0x20,SEEK_SET);
         fread(&filepoint,4,1,bin);
         fseek(bin,filepoint,SEEK_SET);
         fseek(bin,6,SEEK_CUR);
         fread(&frasi,2,1,bin);
         fseek(bin,8,SEEK_CUR);
         fprintf(txt,"[FILE %d]\n\n",i+1);
         for (c=0;c<frasi;c++)
         {
           fseek(bin,4,SEEK_CUR);
           fread(&pointers[c],4,1,bin);
           }
         for (c=0;c<frasi;c++)
         {
             fseek(bin,pointers[c]+filepoint,SEEK_SET);
         while (check != 1)
         {
           if (fgetc(bin)==0x00)
           {
             check=1;
             }else{
                   q++;
                   }}
         check=0;
         fseek(bin,-(q+1),SEEK_CUR);
         fprintf(txt,"<start>");
         fread(buffer,q,1,bin);
         fwrite(buffer,q,1,txt);
         fprintf(txt,"<end>\n\n");
         q=0;
         }
         fprintf(txt,"\n\n\n");
         }
         }}
         
