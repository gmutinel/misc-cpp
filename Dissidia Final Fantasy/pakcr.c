//Dissidia Final Fantasy Pak Creator
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    
    FILE *pak,*ext,*head;
    unsigned long int header[16],pad[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},num,i,pos,len;
    unsigned char stringa[50],name[9];
    //unsigned short int
    if (argc < 2) printf("Dissidia Final Fantasy Pak Creator by Vash v0.01 -www.romhacking.it-\n\npakcr directory\n\n");
      else{
   
   sprintf(stringa,"%s.pak\0",argv[1]);
   pak=fopen(stringa,"w+b");
   chdir(argv[1]);
   head=fopen("table","r+b");
   fread(&header,16,1,head);
   fwrite(&header,16,1,pak);
   fseek(head,0x00,SEEK_END);
   num=(ftell(head)-0x10)/8;
   for (i=0;i<num;i++)
   {
     fwrite(&pad,8,1,pak);
   }
   while (ftell(pak)%16!=0)
   {
      fputc(0x77,pak);
   }      
   fseek(head,0x10,SEEK_SET);
   for (i=0;i<num;i++)
   {   
     fread(name,8,1,head);
     name[8]=0;
     ext=fopen(name,"r+b");
     fseek(ext,0x00,SEEK_END);
     len=ftell(ext);
     pos=ftell(pak);
     rewind(ext);
     fread(buffer,len,1,ext);
     fwrite(buffer,len,1,pak);
     while (ftell(pak)%16!=0)
     { 
      fputc(0x77,pak);
     }
     fseek(pak,(8*i)+0x10,SEEK_SET);
     fwrite(&pos,4,1,pak);
     fwrite(&len,4,1,pak);
     fseek(pak,0x00,SEEK_END);
   }     

}} 
    
