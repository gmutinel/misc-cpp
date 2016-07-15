/*Nancy Drew: Phantom Of Venice Text Reinserter by Vash*/
#include <stdio.h>
#include <windows.h>
BYTE buffer[51200];
BYTE event[33];
unsigned long int Endian_Int_Conversion(unsigned long int dword)
{
   return ((dword>>24)&0x000000FF) | ((dword>>8)&0x0000FF00) | ((dword<<8)&0x00FF0000) | ((dword<<24)&0xFF000000);
}

int main(int argc, char *argv[])
{
      FILE *txt,*cif;
      unsigned char pattern[33]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
      unsigned char head[70]={0x43,0x49,0x46,0x20,0x46,0x49,0x4C,0x45,0x20,0x48,0x65,0x72,0x49,0x6E,0x74,0x65,0x72,0x61,0x63,0x74,0x69,0x76,0x65,0x00,0x03,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x41,0x54,0x41,0x00,0x00,0x00,0x00,0x54,0x45,0x58,0x54,0x43,0x56,0x54,0x58,0x00,0x00,0x00,0x00,0x00,0x00};
      unsigned long int endtxt,off=0x00,lunghezza,endcif,endcif2;
      unsigned char stringa[250],byte=0x00;
      short int c=0,events=0;
      if (argc < 2) printf("Nancy Drew: Phantom Of Venice Text Reinserter by Vash v0.1\n\nnddump file.txt");
      else {
           
           txt=fopen(argv[1],"r+b");
           lunghezza=strlen(argv[1]);
           sprintf(stringa, "%s",argv[1]);
           stringa[lunghezza-4]=0;
           sprintf(stringa, "%s.cif",stringa);
           cif=fopen(stringa,"w+b");
           fwrite(head,70,1,cif);
           fseek(txt,0x00,SEEK_END);
           endtxt=ftell(txt);
           rewind(txt);
           while(off<endtxt)
                     {
                       
                       while(byte!=0x0A)
                       {
                         byte=fgetc(txt);
                         c++;
                         }
                         events++;
                         fseek(txt,-c,SEEK_CUR);
                         fread(event,c-1,1,txt);
                         fwrite(pattern,33,1,cif);
                         fseek(cif,-33,SEEK_CUR);
                         fwrite(event,c-1,1,cif);
                         fseek(cif,33-(c-1),SEEK_CUR);
                         fseek(txt,1,SEEK_CUR);
                         byte=0x00;
                         c=0;
                         while(byte!=0x0A)
                       {
                         byte=fgetc(txt);
                         c++;
                         }
                         fseek(txt,-c,SEEK_CUR);
                         c--;
                         fwrite(&c,2,1,cif);
                         fread(buffer,c,1,txt);
                         fwrite(buffer,c,1,cif);
                         fseek(txt,2,SEEK_CUR);
                         off=ftell(txt);
                         byte=0x00;
                         c=0;
                         }
                         fseek(cif,0x00,SEEK_END);
                         endcif=ftell(cif)-0x30;
                         fseek(cif,0x2C,SEEK_SET);
                         fwrite(&endcif,4,1,cif);
                         endcif=endcif-8;
                         endcif2=Endian_Int_Conversion(endcif);
                         fseek(cif,4,SEEK_CUR);
                         fwrite(&endcif2,4,1,cif);
                         endcif=endcif-0x0C;
                         fseek(cif,8,SEEK_CUR);
                         endcif2=Endian_Int_Conversion(endcif);
                         fwrite(&endcif2,4,1,cif);
                         fwrite(&events,2,1,cif);
                         }}
           
