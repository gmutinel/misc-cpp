/*Nancy Drew: The Haunting Of Castle Malloy Cif to Png Converter by Vash*/
#include <stdio.h>
#include <windows.h>
BYTE buffer[5120000];
int main(int argc, char *argv[])
{
    FILE *cif,*png;
    unsigned char check[4],head[]={0x89,0x50,0x4E,0x47},stringa[250];
    unsigned long int pointer,lunghezza;
    if (argc < 2) printf("Nancy Drew: The Haunting Of Castle Malloy Cif to Png Converter by Vash v0.9\n\nnciftopng file.cif\n\n");
      else {
           mkdir("PNG");
           cif=fopen(argv[1],"r+b");
           fseek(cif,0x30,SEEK_SET);
           fread(check,4,1,cif);
           if (strncmp(head,check,4)!=0)
           {
               printf("This file isn't a PNG\n");
               }else{
                     fseek(cif,0x2C,SEEK_SET);
                     fread(&pointer,4,1,cif);
                     fread(buffer,pointer,1,cif);
                     chdir("PNG");
                     lunghezza=strlen(argv[1]);
                     sprintf(stringa, "%s",argv[1]);
                     stringa[lunghezza-4]=0;
                     sprintf(stringa, "%s.png",stringa);
                     png=fopen(stringa,"w+b");
                     fwrite(buffer,pointer,1,png);
                     printf("%s successfully created: %x\n", stringa,pointer);
                     }
                     }
                     }                      
