#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "files.c"

void conversione();

BYTE buffer[52000];
BYTE buffer2[4];
FILE *txt,*sdb;
unsigned int c,i;
unsigned char punt[10000];

int main()
{
  unsigned long int end,righe,z,y,x,ent;
  unsigned int len;
  unsigned char byte1,byte2,byte3,byte4;
  printf("Digimon World DS *.sdb Reinserter v1.0 by Joghi\n\n");
  for(y=0;y<92;y++)
  {
   chdir("Dumps");
   printf("Creazione File \"%s\" in corso... ",names[y]);
   txt=fopen(texts[y],"r+b");
   fseek(txt,0x00,SEEK_END);
   end=ftell(txt);
   rewind(txt);
   righe=0;
   i=0;
   for(z=0;z<end;z++)
   {
    if((fgetc(txt)==0x0A)&&(fgetc(txt)=='<')&&(fgetc(txt)=='e')&&(fgetc(txt)=='n')&&(fgetc(txt)=='d')&&(fgetc(txt)=='1')&&(fgetc(txt)=='>')&&(fgetc(txt)==0x0A))
    {
     righe++;
     z=z+7;
    }
    else
    {
     if((fgetc(txt)==0x0A)&&(fgetc(txt)=='<')&&(fgetc(txt)=='e')&&(fgetc(txt)=='n')&&(fgetc(txt)=='d')&&(fgetc(txt)=='2')&&(fgetc(txt)=='>')&&(fgetc(txt)==0x0A))
     {
      righe++;
      z=z+7;
     }
     else
     {
      if(fgetc(txt)==0x0A)
       righe++;
     }
    }
   }
   rewind(txt);
   chdir("..");
   sdb=fopen(names[y],"w+b");
   punt[0]=righe*4;
   fseek(sdb,(righe*4),SEEK_SET);            
   fread(buffer,end,1,txt);
   buffer[end]=0;
   for(c=0;c<strlen(buffer);c++)
   {
    ent=0;
    if((buffer[c]=='{')&&(buffer[c+3]=='}')&&(buffer[c+4]=='{')&&(buffer[c+7]=='}'))
    { 
     byte1=buffer[c+1];
     byte2=buffer[c+2];
     byte3=buffer[c+5];
     byte4=buffer[c+6];
     if((byte1=='e')&&(byte2=='e')&&(byte3=='f')&&(byte4=='f'))
     {
      buffer2[0]=0xEE;
      buffer2[1]=0xFF;
      fwrite(buffer2,2,1,sdb);
      c=c+7;
      ent==1;
     }
     else
     {
      if((byte1=='f')&&(byte2=='0')&&(byte3=='f')&&(byte4=='f'))
      {
       buffer2[0]=0xF0;
       buffer2[1]=0xFF;
       fwrite(buffer2,2,1,sdb);
       c=c+7;
       ent=1;
      } 
      else
      {
       if((byte1=='e')&&(byte2=='c')&&(byte3=='f')&&(byte4=='f'))
       {
        buffer2[0]=0xEC;
        buffer2[1]=0xFF;
        fwrite(buffer2,2,1,sdb);
        c=c+7;
        ent=1;
       }
       else
       {
        if((byte1=='f')&&(byte2=='1')&&(byte3=='f')&&(byte4=='f'))
        {
         buffer2[0]=0xF1;
         buffer2[1]=0xFF;
         fwrite(buffer2,2,1,sdb);
         c=c+7;
         ent=1;
        }
        else
        {
         if((byte1=='e')&&(byte2=='d')&&(byte3=='f')&&(byte4=='f'))
         {
          buffer2[0]=0xED;
          buffer2[1]=0xFF;
          fwrite(buffer2,2,1,sdb);
          c=c+7;
          ent=1;
         }
        }
       }
      }
     } 
     if(ent==0)
     {
      if (byte1 >= 0x30 && byte1 <= 0x39)
      {
       byte1=(byte1-0x30)*0x10;
      }
      else
      {
       byte1=(byte1-0x37)*0x10;
      }
      if (byte2 >= 0x30 && byte2 <= 0x39)
      {
       byte2=(byte2-0x30);
      }
      else
      {
       byte2=(byte2-0x37);
      }
      if (byte3 >= 0x30 && byte3 <= 0x39)
      {
       byte3=(byte3-0x30)*0x10;
      }
      else
      {
       byte3=(byte3-0x37)*0x10;
      }
      if (byte4 >= 0x30 && byte4 <= 0x39)
      {
       byte4=(byte4-0x30);
      }
      else
      {
       byte4=(byte4-0x37);
      }
      buffer2[0]=byte1+byte2;
      buffer2[1]=byte3+byte4;
      fwrite(buffer2,2,1,sdb);
      c=c+7;
     }
    }
    else
    {
     if((buffer[c]=='{')&&(buffer[c+3]=='}')&&(buffer[c+4]=='{')&&(buffer[c+6]=='}'))
      {
       byte1=buffer[c+1];
       byte2=buffer[c+2];
       ent=0;
       if((byte1=='1')&&(byte2=='b'))
       {
        buffer2[0]=0x1B;
        buffer2[1]=0x00;
        fwrite(buffer2,2,1,sdb);
        c=c+6;
        ent=1;
       }
       else
       {
        if((byte1=='1')&&(byte2=='c'))
        {
         buffer2[0]=0x1C;
         buffer2[1]=0x00;
         fwrite(buffer2,2,1,sdb);
         c=c+6;
         ent=1;
        }
       }
      if(ent==0)
      {
       if (byte1 >= 0x30 && byte1 <= 0x39)
       {
        byte1=(byte1-0x30)*0x10;
       }
       else
       {
        byte1=(byte1-0x37)*0x10;
       }
       if (byte2 >= 0x30 && byte2 <= 0x39)
       {
        byte2=(byte2-0x30);
       }
       else
       {
        byte2=(byte2-0x37);
       }
       buffer2[0]=byte1+byte2;
       buffer2[1]=0x00;
       fwrite(buffer2,2,1,sdb);
       c=c+6;
      }
      else
      {
       conversione();
      }
    } 
   }
   //ricreazione puntatori
   rewind(sdb);
   
   fclose(sdb);
   fclose(txt);
   printf("Completata\n\n");
  }
 return 0;
}
}
void conversione()
{
 unsigned long int end,r,ent;
 unsigned char byte1,byte2,byte3,byte4,byte;
 FILE *tbl;
    tbl=fopen("dgmnwrld.tbl","r+b");
    end=0;
    ent=0;
    if((buffer[c]==0x0A)&&(buffer[c+1]=='<')&&(buffer[c+2]=='e')&&(buffer[c+3]=='n')&&(buffer[c+4]=='1'))
    {
     buffer2[0]=0xFF;
     buffer2[1]=0xFF;
     fwrite(buffer2,2,1,sdb);
     ent=1;
     punt[i]=ftell(sdb);
     i++;
     c=c+7;
    }
    if((buffer[c]==0x0A)&&(buffer[c+1]=='<')&&(buffer[c+2]=='e')&&(buffer[c+3]=='n')&&(buffer[c+4]=='2'))
    {
     buffer2[0]=0xFE;
     buffer2[1]=0xFF;
     fwrite(buffer2,2,1,sdb);
     ent=1;
     punt[i]=ftell(sdb);
     i++;
     c=c+7;
    }
    if((buffer[c]==0x0A)&&(ent==0))
    {
     buffer2[0]=0xFD;
     buffer2[1]=0xFF;
     fwrite(buffer2,2,1,sdb);
     ent=1;
    }
    if(ent==0)
    {
     for(r=0;r<83;r++)
     {
      if(end==0)
      {
       byte1=fgetc(tbl);
       byte2=fgetc(tbl);
       byte3=fgetc(tbl);
       byte4=fgetc(tbl);
       fseek(tbl,1,SEEK_CUR);
       byte=fgetc(tbl);
       if(buffer[c]==byte)
       {  
        if (byte1 >= 0x30 && byte1 <= 0x39)
        {
         byte1=(byte1-0x30)*0x10;
        }
        else
        {
         byte1=(byte1-0x37)*0x10;
        }
        if (byte2 >= 0x30 && byte2 <= 0x39)
        {
         byte2=(byte2-0x30);
        }
        else
        {
         byte2=(byte2-0x37);
        }
        if (byte3 >= 0x30 && byte3 <= 0x39)
        {
         byte3=(byte3-0x30)*0x10;
        }
        else
        {
         byte3=(byte3-0x37)*0x10;
        }
        if (byte4 >= 0x30 && byte4 <= 0x39)
        {
         byte4=(byte4-0x30);
        }
        else
        {
         byte4=(byte4-0x37);
        }
        buffer2[0]=byte1+byte2;
        buffer2[1]=byte3+byte4;
        fwrite(buffer2,2,1,sdb);
        end=1;
       }
       fseek(tbl,2,SEEK_CUR);
      }
      else
       r=83;
     }//chiusura for 
    }//chiusura if
    fclose(tbl);  
}
