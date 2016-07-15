#include <stdio.h>
#include <windows.h>
#include "eng.c"

BYTE buffer[10485760];

main()
{
    FILE *text,*dump;
    unsigned long int num,i,point[30000],c,len,end;
    unsigned char stringa[0x500];
    
    
    
    printf("Final Fantasy Crystal Chronicles Echoes Of Time Dumper (Ds Version)\nby Vash v0.9 -www.romhacking.it-\n\n");
    mkdir("Dump");
    for (i=0;i<90;i++)
    {
        text=fopen(names[i],"r+b");
        chdir("Dump");
        dump=fopen(texts[i],"w+b");
        chdir("..");
        fread(&num,4,1,text);
        num=num/4;
        fseek(text,0x00,SEEK_END);
        end=ftell(text);
        rewind(text);
        for (c=0;c<num;c++)
        {
            fread(&point[c],4,1,text);
            }   
         for (c=0;c<num;c++)
        {
            if (point[c]!=end)
            {
            fseek(text,point[c],SEEK_SET);
            fread(buffer,0x5500,1,text);
            len=strlen(buffer);
            fprintf(dump,"[start]\n");
            fwrite(buffer,len,1,dump);
            fprintf(dump,"\n[end]\n\n");
            }else{
            fprintf(dump,"[start]\n<NULL>\n[end]");
                 }
                 }    
             fclose(text);
             fclose(dump);
             }    
            } 
    
   
   
