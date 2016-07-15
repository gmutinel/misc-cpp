//Kingdom Hearts Chain Of Memories Hidden Files Extractor
#include <stdio.h>
#include <windows.h>

BYTE buffer[2048];

int main(int argc, char *argv[])
{
    FILE *iso,*ext;
    long long unsigned int pointer;
    unsigned long int i,c,times,len,off=0x00;
    unsigned char name[16];

    if (argc < 2) printf("Kingdom Hearts Chain Of Memories Hidden Files Extractor by Vash v0.9 -www.romhacking.it-\n\nisoext file.iso\n\n");
      else{
      iso=fopen64(argv[1],"r+b");
      mkdir("ISO");
      chdir("ISO");
      for (i=0;i<144;i++)
      {
          fseek(iso,0x122800+off,SEEK_SET);
          fread(name,16,1,iso);
          ext=fopen(name,"w+b");
          fread(&pointer,4,1,iso);
          pointer=pointer*0x800;
          fread(&len,4,1,iso);
          len=len*0x800;
          fseeko64(iso,pointer,SEEK_SET);
          times=len/0x800;
          printf("Extracting %s\n",name);
          for (c=0;c<times;c++)
          {
            fread(buffer,0x800,1,iso);
            fwrite(buffer,0x800,1,ext);
            }
      fclose(ext);
      off=off+0x20;
      }
      
      }
      }
