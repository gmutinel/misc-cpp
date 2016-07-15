//Kingdom Hearts Chain Of Memories Ctd Dumper
#include <stdio.h>
#include <windows.h>
BYTE buffer[100*1024];

int main(int argc, char *argv[])
{
    
    FILE *txt,*ctd;
    unsigned long int num,i,filepoint,pointbank,textbank,pointers[500],check=0,q=0,lunghezza,c;
    unsigned char stringa[350];
    short int frasi;
    if (argc < 2) printf("Kingdom Hearts Chain Of Memories Ctd Dumper by Vash v0.9 -www.romhacking.it-\n\ndatext file.ctd\n\n");    
      else{     
      ctd=fopen(argv[1],"r+b");
      fread(&num,4,1,ctd);
      num=(num-0x20)/0x20;
      if (num>10)
      {
        printf("This file is compressed or useless, move on");
        return(0);
        }
      rewind(ctd);
      lunghezza=strlen(argv[1]);
      sprintf(stringa,"%s",argv[1]);
      stringa[lunghezza-4]=0;
      sprintf(stringa,"%s.txt",stringa);
      txt=fopen(stringa,"w+b");
      
      
      for(i=0;i<num;i++)
      {  
         fseek(ctd,i*0x20,SEEK_SET);
         fread(&filepoint,4,1,ctd);
         fseek(ctd,filepoint,SEEK_SET);
         fseek(ctd,4,SEEK_CUR);
         fread(&frasi,2,1,ctd);
         fseek(ctd,2,SEEK_CUR);
         fread(&pointbank,4,1,ctd);
         fread(&textbank,4,1,ctd);
         fseek(ctd,-0x10,SEEK_CUR);
         fseek(ctd,pointbank,SEEK_CUR);
         fprintf(txt,"[FILE %d]\n\n",i+1);
         for (c=0;c<frasi;c++)
         {
           fread(&pointers[c],4,1,ctd);
           }
         //fseek(ctd,(textbank-pointbank-(frasi*4)),SEEK_CUR);
         
         for (c=0;c<frasi;c++)
         {
             fseek(ctd,pointers[c]+textbank+filepoint,SEEK_SET);
         while (check != 1)
         {
           if (fgetc(ctd)==0x00)
           {
             check=1;
             }else{
                   q++;
                   }}
         
         check=0;
         fseek(ctd,-(q+1),SEEK_CUR);
         fprintf(txt,"<start>");
         fread(buffer,q,1,ctd);
         fwrite(buffer,q,1,txt);
         fprintf(txt,"<end>\n\n");
         q=0;
         }
         fprintf(txt,"\n\n\n");
         }
         }}
                                              
         
         
                                                
         
