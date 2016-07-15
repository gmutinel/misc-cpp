/*Nancy Drew: The Haunting Of Castle Malloy Png to Cif Converter by Vash*/
#include <stdio.h>
#include <windows.h>
BYTE buffer[5120000];
int main(int argc, char *argv[])
{
    FILE *cif,*png;
    unsigned char stringa[250],header[44];
    unsigned long int lunghezza,endpng;
    if (argc < 2) printf("Nancy Drew: The Haunting Of Castle Malloy Png to Cif Converter by Vash v0.9\n\nnciftopng file.png\n\n");
      else {
           png=fopen(argv[1],"r+b");
           lunghezza=strlen(argv[1]);
           sprintf(stringa, "%s",argv[1]);
           stringa[lunghezza-4]=0;
           sprintf(stringa, "%s.cif",stringa);
           cif=fopen(stringa,"r+b");
           fread(header,44,1,cif);
           fclose(cif);
           cif=fopen(stringa,"w+b");
           fwrite(header,44,1,cif);
           fseek(png,0x00,SEEK_END);
           endpng=ftell(png);
           fwrite(&endpng,4,1,cif);
           rewind(png);
           fread(buffer,endpng,1,png);
           fwrite(buffer,endpng,1,cif);
           printf("PNG Successfully inserted");
           }
}
