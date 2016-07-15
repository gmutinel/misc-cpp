//Tales Of Destiny 2 FPB Extractor -CLESS SUKA- by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    FILE *fpb, *ext, *exe;
    unsigned char name[9],files[8]={'f','i','l','e','.','f','p','b'},movie[9]={'m','o','v','i','e','.','f','p','b'};
    unsigned long int numpoint, pointer, fpoints[9999],i,rpoints[9999],c,temp,padding[9999],dim[9999],n0=0,n1=0,n2=0,n3=1,times,resto; 
    if (argc < 2) printf("Tales Of Destiny 2 FPB Extractor -CLESS SUKA- by Vash v0.91 -www.romhacking.it-\n\ntod2ext file.fpb OR movie.fpb\n\n");    
      else{
          
      
      fpb=fopen(argv[1],"r+b");
      exe=fopen("SLPS_251.72","r+b");
      
      if ((strcmp(argv[1],"file.fpb") == 0))
      {
          numpoint=9204;
          pointer=0xDD320;        
          mkdir("File");
          chdir("File");
      } //else {                 
     //  printf("%x  %x\n",pointer, numpoint); 
    if (strcmp(argv[1],"movie.fpb") == 0)
      {
          numpoint=12;
          pointer=0xE62F0;        
          mkdir("Movie");
          chdir("Movie");
      }
      
       fseek(exe,pointer,SEEK_SET);
       for (i=0;i<numpoint;i++)
       {
           fread(&fpoints[i],4,1,exe);
       }
       //system("pause"); 
        for (i=0;i<numpoint-1;i++)
       {
          temp=fpoints[i]; 
          for(c=0;c<0x40;c++)
          {
                       
          if (((temp%64) == 0) || (temp == 0) )
          {
               rpoints[i]=temp;
               c=0x41;
               }else{
                     temp--;
           
                     }                   
                     } 
         //system("pause");                             
         //printf("%x = %x\n",fpoints[i],rpoints[i]);
         padding[i]=fpoints[i]-rpoints[i];
         }    
         rpoints[numpoint-1]=fpoints[numpoint-1];
         //printf("%x\n",fpoints[numpoint-1]);
         for (i=0;i<numpoint-1;i++)
       {
       dim[i]=rpoints[i+1]-rpoints[i]-padding[i];      
                      
       sprintf(name,"%x%x%x%x.dat\0",n0,n1,n2,n3);
       if (n3==9)
                   {
                   n3=0;
                   n2=n2+1;
                   }else{
                   n3=n3+1;
                         }
                         if (n2==10)
                         {
                         n2=0;
                         n1=n1+1;
                          }
                          if (n1==10)
                         {
                         n1=0;
                         n0=n0+1;
                          }
       ext=fopen(name,"w+b");
       fseek(fpb,rpoints[i],SEEK_SET);
       times=dim[i]/10485760;
       resto=dim[i]%10485760;
       printf("\r %s\n",name);
       for (c=0;c<times;c++)
        {
       fread(buffer,10485760,1,fpb);
       fwrite(buffer,10485760,1,ext);
       }
       
       if (resto > 0)
       {
       fread(buffer,resto,1,fpb);
       fwrite(buffer,resto,1,ext);
                 
       }
       
       fclose(ext);
       }      
                       
      
      
      
      
       
}}
