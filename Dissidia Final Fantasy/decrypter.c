#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
unsigned short int Endian_Short_Conversion(unsigned short int word) 
{ 
      return ((word>>8)&0x00FF) | ((word<<8)&0xFF00) ; 
}
int main(int argc, char *argv[])
{
    FILE *pak,*txt;
    unsigned short int num,off,i,c,len,pointer,s=-1,q,byte,check=0,control;
    unsigned long int point,keys[16]={0x98ED,0xAB90,0x285E,0x4284,0xB132,0xDA2D,0x57A6,0xBFC8,0x3300,0x9A57,0x27F2,0x4C4B,0xA736,0x7D92,0x9D73,0xCE84},lunghezza;
    unsigned char stringa[1250];
    pak=fopen(argv[1],"r+b");
    lunghezza=strlen(argv[1]);
    sprintf(stringa,"%s",argv[1]);
    stringa[lunghezza-4]=0;
    sprintf(stringa,"%s.txt\0",stringa);
    //printf("%s\n",stringa);
    //controllo
    fread(&num,2,1,pak);
    while (check < 1)
    {
    fread(&control,2,1,pak);
    if (control != 0x00 && control == num+1)
    {
       check=1;
      }
    if ((control != 0x00 && control != num+1) || feof(pak))  
    {
       check=2;
      }
              
    }
    if (check==2)
    {
        printf("This file doesn't contain text\n");
        return (0);
    }
    rewind(pak);
    txt=fopen(stringa,"w+b");
    fread(&num,2,1,pak);
    
    for (i=0;i<num;i++)
    {
       s++;
       if (s>=16)
             {s=0;}
       fread(&pointer,2,1,pak);
       off=ftell(pak);
       point=pointer*2;
       //printf("%x-   %x",i+1,pointer); 
       if (point==0x00)
       {
         fputc(0x0D,txt);
         fputc(0x00,txt);
         fputc(0x0A,txt);
         fputc(0x00,txt);               
       }
       if (point!=0x00)
       {             
          fseek(pak,point,SEEK_SET);
          fread(&len,2,1,pak);  
          fseek(pak,point+2,SEEK_SET);
          fread(buffer,len,1,pak);
          q=s;
          for (c=0;c<len;c++)
          {
             byte=((buffer[c]*0x100)+buffer[c+1]);
             byte=byte^keys[q];
             byte=Endian_Short_Conversion(byte);
             if (byte==0x00)
             {
               //fprintf(txt,"<end>");
               fputc(0x0D,txt);
               fputc(0x00,txt);
               fputc(0x0A,txt);
               fputc(0x00,txt);
               }else{             
             fwrite(&byte,2,1,txt);
            }
             c++;
             q++;
             if (q>=16)
             {q=0;}
              }
              
          //fprintf(txt,"\n");    
          
          //system("pause");    
         
    }     
fseek(pak,off,SEEK_SET);
}

}


    
    
