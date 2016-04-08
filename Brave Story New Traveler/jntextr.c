//Brave Story New Traveler Jnt Extractor
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    FILE *jnt,*ext,*tbl;
    unsigned long int lunghezza,num,i,pointer,size;
    unsigned char stringa[500],head[0xC],name[32];
    if (argc < 2) printf("Brave Story New Traveler Jnt Extractor by Vash v0.9 -www.romhacking.it-\n\njntextr file.jnt\n\n");
      else{
           
           jnt=fopen(argv[1],"r+b");
           lunghezza=strlen(argv[1]);
           sprintf(stringa, "%s",argv[1]);
           stringa[lunghezza-4]=0;
           mkdir(stringa);
           chdir(stringa);
           tbl=fopen("table","w+b");
           fseek(jnt,0x18,SEEK_SET);
           fread(&num,4,1,jnt);
           fseek(jnt,0x10,SEEK_SET);
           fread(head,0xC,1,jnt);
           fwrite(head,0xC,1,tbl);
           fseek(jnt,0x20,SEEK_SET);
           for (i=0;i<num;i++)
           {
             fseek(jnt,0x20+(0x28*i),SEEK_SET);
             fread(name,0x20,1,jnt);
             fread(&pointer,4,1,jnt);
             fread(&size,4,1,jnt);
             fseek(jnt,pointer,SEEK_SET);
             fread(buffer,size,1,jnt);
             ext=fopen(name,"w+b");
             printf("%s\n",name);
             fwrite(name,0x20,1,tbl);
             fwrite(buffer,size,1,ext);
             fclose(ext);
             }  }}
