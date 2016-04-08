#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#endif

int main(int argc, char** argv) {
   unsigned int items;
   unsigned int i;
   unsigned int original_size;

   char head[0xC];

   char inputfile[99];
   unsigned int inputfile_size;

   char filename[0x99];
   unsigned int file_offset;
   unsigned int file_size;

   FILE *fd;
   FILE *tbl;
   FILE *output;

   fd = fopen(argv[1],"r+b");

   inputfile_size = strlen(argv[1]);
   sprintf(inputfile, "%s",argv[1]);
   inputfile[inputfile_size-4] = 0;

   #ifdef WIN32
      mkdir(inputfile);
   #else
      mkdir(inputfile,0777);
   #endif
   chdir(inputfile);

   tbl = fopen("table","w+b");

   fseek(fd,0x8,SEEK_SET);
   fread(&original_size,4,1,fd);

   fseek(fd,0x18,SEEK_SET);
   fread(&items,4,1,fd);

   fseek(fd,0x10,SEEK_SET);
   fread(head,0xC,1,fd);
   fwrite(head,0xC,1,tbl);

   fseek(fd,0x1C,SEEK_SET);

   for (i=0;i<items;i++)
   {
      fseek(fd,0x1C+(0x4*i),SEEK_SET);
      sprintf(filename, "file_%i.lzma", i);
      fread(&file_offset,4,1,fd);
      fread(&file_size,4,1,fd);

      file_offset += 0x04;
      if ( i == items -1 ) {
         file_size = original_size - file_offset;
      } else {
         file_size -= file_offset;
      }

      char buffer[file_size];

      fseek(fd,file_offset,SEEK_SET);
      fread(buffer,file_size,1,fd);

      output = fopen(filename,"w+b");
      printf("File: %s, offset: %X, size: %X\n",filename, file_offset, file_size);

      fwrite(filename,sizeof(filename),1,tbl);
      fwrite(buffer,file_size,1,output);
      fclose(output);
   }
   fclose(tbl);
   fclose(fd);
}

