//Dissidia Final Fantasy Arc Extractor
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    FILE *arc,*ext,*tbl;
    unsigned long int i,lunghezza,num,dop=0,ok=0,pointer,len,off=0x10,c;
    unsigned char stringa[50],table[8],nome[10],tempnome[4];
    if (argc < 2) printf("Dissidia Final Fantasy Arc Extractor by Vash v0.91 -www.romhacking.it-\n\nmpkext file.arc\n\n");
      else{
           arc=fopen(argv[1],"r+b");
           lunghezza=strlen(argv[1]);
           sprintf(stringa, "%s",argv[1]);
           stringa[lunghezza-4]=0;
           mkdir(stringa);
           chdir(stringa);
           tbl=fopen("table","w+b");
           fseek(arc,4,SEEK_SET);
           fread(&num,4,1,arc);
           fseek(arc,8,SEEK_CUR);
           fwrite(&num,4,1,tbl);
           for (i=0;i<num;i++)
           {
              fread(table,8,1,arc);
              fwrite(table,8,1,tbl);
              fseek(arc,8,SEEK_CUR);
              }
              //fclose(tbl);
              
           for (c=0;c<num;c++)
           {
              fseek(arc,off,SEEK_SET);
              fseek(arc,4,SEEK_CUR);
              fread(tempnome,4,1,arc);
              tempnome[4]=0;
              tempnome[4]=0;
              sprintf(nome, "%s.%d.dat",tempnome,dop);
              //printf("%s:   %x\n",nome,num);  
              if (fopen(nome,"r+b")==NULL)
              {
                ok=1;
                }                          
              while (ok!=1)
              {
              nome[0]=0;
              sprintf(nome, "%s.%d.dat",tempnome,dop);
              
              if (fopen(nome,"r+b")!=NULL)
              {
                 dop++;
                 
                 }else{
                       ok=1;
                       }                        
              
              }
              ext=fopen(nome,"w+b");
              fwrite(nome,10,1,tbl);
              printf("%s\n",nome); 
              fread(&pointer,4,1,arc);
              fread(&len,4,1,arc);
              off=ftell(arc);
              //printf("%x",off);
              fseek(arc,pointer,SEEK_SET);
              fread(buffer,len,1,arc);
              fwrite(buffer,len,1,ext);
              fclose(ext);
              dop=0;
              ok=0;
              }
}}
              
               
           
           
