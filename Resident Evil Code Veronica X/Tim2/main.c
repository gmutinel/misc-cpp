#include "Texter.h"

int main(int argc, char *argv[])
{



if (argc < 4) printf("\nTextures Extractor/Reinserter v1.0b5 by Vash (Modified for Resident Evil Code Veronica X)\n\n-> TextER [option] [file] [type]\n\nOPTION:\n\n-e file [extract the files]\n-c file [insert the textures extracted in the original file]\n\nTYPE:\n\n-tm [TIM2 & TIM3 (PS2)]\n-gim [GIM (psp)]\n\n");
    else {
    if (strstr(argv[0], argv[2])!=0)
    {
      printf("\nC'mon guy! You can't scan me....What the fuck!\n");                    
      return 0;
}

if (fopen(argv[2], "r+b")==NULL)
{
   printf("\nThe file is read only or is used by another application or it doesn't exist\n");                    
      return 0;
}    

if(strcmpi(argv[1], "-e")!=0 && strcmpi(argv[1], "-c")!=0)
{
   printf("\nTextures Extractor/Reinserter v0.9 by Vash\n\n-> TextER [option] [file] [type]\n\nOPTION:\n\n-e file [extract the files]\n-c file [insert the textures extracted in the original file]\n\nTYPE:\n\n-tm [TIM2 & TIM3 (PS2)]\n-gim [GIM (psp)]\n\n");                    
      return 0;
}
if (strstr(argv[2], "\\")!=0)
{
   printf("\nThe file MUST be in the same directory of the program\n");                    
      return 0;
} 

if(strcmpi(argv[1], "-e")==0) //Estrazione
    {
                    arch=fopen64(argv[2], "r+b");       
              
              fseeko64(arch,0x00,SEEK_END);
              endfile=ftell(arch);
              
              if (endfile<=0)
              {
                   printf("Sorry dude, this file is too big for now or it's empty...\n");
                   return 0;
                   }
                   fclose(arch);  
 

if(strcmpi(argv[3], "-tm")==0 || strcmpi(argv[argc-1], "-tm")==0  || strcmpi(argv[argc-2], "-tm")==0)   
          {
              arch=fopen64(argv[2], "r+b");       
              printf("\nLooking for TIM2 and TIM3:\n\n");
              tmsearch();
              tmextr(argv[2]);
              }
              
if(strcmpi(argv[3], "-gim")==0 || strcmpi(argv[argc-1], "-gim")==0  || strcmpi(argv[argc-2], "-gim")==0)   
          {   
              arch=fopen64(argv[2], "r+b");     
              printf("Looking for GIM:\n\n");
              gimsearch();
              gimextr(argv[2]);              
              }        

/*if(strcmpi(argv[3], "-tpl")==0 || strcmpi(argv[argc-1], "-tpl")==0  || strcmpi(argv[argc-2], "-tpl")==0)   
          {   
              arch=fopen64(argv[2], "r+b");     
              printf("Looking for TPL:\n\n");
              tplsearch();
              //gimextr(argv[2]);              
              } */  



}                    


if(strcmpi(argv[1], "-c")==0)
              {
              
              
              if(strcmpi(argv[3], "-tm")==0 || strcmpi(argv[argc-1], "-tm")==0)  
              {
                 arch=fopen64(argv[2],"r+b");
                 printf("\nInserting TIM2 and/or TIM3:\n\n");
                 timins(argv[2]);
              }
              
              if(strcmpi(argv[3], "-gim")==0 || strcmpi(argv[argc-1], "-gim")==0)   
             {   
              arch=fopen64(argv[2], "r+b");     
              printf("Inserting GIM:\n\n");
              gimins(argv[2]);
              }
              



}
}
}
