//Dissidia Final Fantasy Mpk Extractor
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    FILE *mpk,*ext,*tbl;
    unsigned long int lunghezza,num,pointername[500],pointer[500],peso[500],match=0,i,c=0;
    unsigned char stringa[50],filename[150];
     if (argc < 2) printf("Dissidia Final Fantasy Mpk Extractor by Vash v0.9 -www.romhacking.it-\n\nmpkext file.mpk\n\n");
      else{
           mpk=fopen(argv[1],"r+b");
           lunghezza=strlen(argv[1]);
           sprintf(stringa, "%s",argv[1]);
           stringa[lunghezza-4]=0;
           mkdir(stringa);
           chdir(stringa);
           tbl=fopen("table","w+b");
           fseek(mpk,8,SEEK_SET);
           fread(&num,4,1,mpk);
           fwrite(&num,4,1,tbl);
           fseek(mpk,4,SEEK_CUR);
           for (i=0;i<num;i++)
           {
              fread(&pointername[i],4,1,mpk);
              fread(&pointer[i],4,1,mpk);
              fread(&peso[i],4,1,mpk);
              fseek(mpk,4,SEEK_CUR);
              }
               
           for (i=0;i<num;i++)
           {
               fseek(mpk,pointername[i],SEEK_SET);
               while (match!=1)
               {
                  if (fgetc(mpk)==0x00)
                  {
                      match=1;
                      }else{
                            c++;
                            }                     
        
                            }
               fseek(mpk,pointername[i],SEEK_SET);
               fread(filename,c,1,mpk);
               filename[c]=0;
               fseek(mpk,pointer[i],SEEK_SET);
               printf("%s   %x\n",filename,c);
               fwrite(&c,4,1,tbl);
               fwrite(filename,c,1,tbl);
               ext=fopen(filename,"w+b");
               fread(buffer,peso[i],1,mpk);
               fwrite(buffer,peso[i],1,ext);
               fclose(ext);
               match=0;
               c=0;
               }
               }                              
}
