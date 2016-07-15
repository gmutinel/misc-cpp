//FF7 Bin Maker for Saffo by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[1048576];

main()
{
      
      FILE *bin,*ext,*tbl;
      unsigned long int i,c,num[4]={23,52,47,47},pointer[53],n0=0,n1=1,end;
      unsigned char command[500],newnames[50],stringa[50];
      unsigned char names[4][20]={{'O','P','E','N','I','N','G'},
                                  {'S','T','A','F','F'},
                                  {'S','T','A','F','F','2'},
                                  {'S','T','A','F','F','2','U','S'}};    
                                  
      printf("Final Fantasy 7 Bin Maker by Vash v0.9 -www.sadnescity.it-\n\n");
      
      for (i=0;i<4;i++)
      {                            
        sprintf(stringa,"%s.bin\0",names[i]);
        bin=fopen(stringa,"w+b");
        mkdir(names[i]);
        //sprintf(command,"copy LZSS.exe %s",names[i]);
        //system(command);                          
        chdir(names[i]);
        for (c=0;c<(num[i]*4);c++)
        {
            fputc(0x00,bin);
            }
        //sprintf(command,"for %%i in (*.dat) do LZSS e %%i %%i.com");
       // system(command);
        //system("del LZSS.exe");
        for (c=0;c<num[i];c++)
        {
         pointer[c]=ftell(bin);
         sprintf(newnames,"%s%d%d.dat\0",names[i],n0,n1);
         ext=fopen(newnames,"r+b");
         fseek(ext,0x00,SEEK_END);
         end=ftell(ext);
         rewind(ext);
         fread(buffer,end,1,ext);
         fwrite(buffer,end,1,bin);
         if (n1==9)
                         {
                         n1=0;
                         n0=n0+1;
                          }else{
                           n1=n1+1;
                           }
                           
         fclose(ext);
         }
         rewind(bin);
         for (c=0;c<num[i];c++)
        {
             fwrite(&pointer[c],4,1,bin);
             }
         //system("del *.com");
         chdir("..");
         n0=0;
         n1=1;
         fclose(bin);
         }
         }
                 
