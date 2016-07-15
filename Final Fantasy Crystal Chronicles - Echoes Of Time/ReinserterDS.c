#include <stdio.h>
#include <windows.h>
#include "eng.c"

BYTE buffer[10485760];

main()
{
    FILE *text,*dump;
    unsigned long int totl,num,i,pointer[30000],off,c[30000],s,q;
    //unsigned char stringa[0x100];
    printf("Final Fantasy Crystal Chronicles Echoes Of Time Dumper (Ds Version)\nby Vash v0.9 -www.romhacking.it-\n\n");
    
    for (i=0;i<90;i++)
    {
        chdir("Dump");
        text=fopen(texts[i],"r+b");
        chdir("..");
        dump=fopen(names[i],"w+b");
        fseek(text,0x00,SEEK_END);
        totl=ftell(text);
        rewind(text);
        fread(buffer,totl,1,text);
        num=0;
        for (q=0;q<totl;q++)
        {
           if (buffer[q]==0x5B)
           {
              num++;
              }
        } 
        num=num/2; //Numero di puntatori
        rewind(text);
        //Calcolo dei puntatori
        pointer[0]=num*4;
        for (s=1;s<num+1;s++)
        {
           fwrite(&pointer[s-1],4,1,dump);
           fseek(text,8,SEEK_CUR);
           off=ftell(text);
           fread(buffer,0x5500,1,text);
           c[s]=0;
           
           while (buffer[c[s]]!=0x5B)
           {
           if (buffer[c[s]] != 0x5B)
           {
              c[s]++;
              }
           }  
          // printf("0x%x\n", c);
          // system("pause");
           fseek(text,off,SEEK_SET);
           pointer[s]=pointer[s-1]+c[s];
           fseek(text,7+c[s],SEEK_CUR);   
           }
         //banco dei puntatori scritto
         rewind(text);
         for (s=1;s<num+1;s++)
         {   
            fseek(text,8,SEEK_CUR);
            fread(buffer,c[s]-1,1,text);
            if(buffer[0]!=0x3C || buffer[1]!=0x4E || buffer[2]!=0x55 || buffer[3]!=0x4C)
            {
            fwrite(buffer,c[s]-1,1,dump);
            fputc(0x00,dump);
            }
            fseek(text,8,SEEK_CUR);
            }  
            
            
            }
        
        
        }
        
        
        
        
    
