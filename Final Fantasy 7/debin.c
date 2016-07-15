//FF7 Bin Extractor for Saffo by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[1048576];

main()
{
      FILE *bin,*ext,*tbl;
      unsigned long int i,num,c,pointer[53],n0=0,n1=1;
      unsigned char newnames[50],stringa[50],command[500];
      unsigned char names[4][20]={{'O','P','E','N','I','N','G'},
                                  {'S','T','A','F','F'},
                                  {'S','T','A','F','F','2'},
                                  {'S','T','A','F','F','2','U','S'}};                              
      
      printf("Final Fantasy 7 Bin Extractor by Vash v0.9 -www.sadnescity.it-\n\n");
      
      for (i=0;i<4;i++)
      {
        sprintf(stringa,"%s.bin\0",names[i]);
        bin=fopen(stringa,"r+b");
        mkdir(names[i]);
        //sprintf(command,"copy LZSS.exe %s",names[i]);
        //system(command);
        chdir(names[i]);
        fread(&num,4,1,bin);
        num=num/4;
        //printf("%x\n",num);
        // system("pause");
        rewind(bin);
        for (c=0;c<num;c++)
        {
          fread(&pointer[c],4,1,bin);
         }
         
         fseek(bin,0x00,SEEK_END);
        
         pointer[c]=ftell(bin);  
        
         
          for (c=0;c<num;c++)
         {
           fseek(bin,pointer[c],SEEK_SET);  
           fread(buffer,pointer[c+1]-pointer[c],1,bin);
           sprintf(newnames,"%s%d%d.dat\0",names[i],n0,n1);
           ext=fopen(newnames,"w+b");
           fwrite(buffer,pointer[c+1]-pointer[c],1,ext);
           if (n1==9)
                         {
                         n1=0;
                         n0=n0+1;
                          }else{
                           n1=n1+1;
                           } 
           
           fclose(ext);
           }                 
                     
           //sprintf(command,"for %%i in (*.dat) do LZSS d %%i %%i.dec");
           //system(command);
           //sprintf(command,"del *.dat");
           //system(command);
           //sprintf(command,"ren *.dat.dec *.");
           //system(command);
           //system("del LZSS.exe");
           //system("pause");
           chdir(".."); 
           fclose(bin);
           n0=0;
           n1=1;
           }          
           }
           
           
           
           
           
           
           
           
           
           
           
