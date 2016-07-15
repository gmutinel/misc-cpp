#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "files.c"
BYTE buffer[51200];

int main()
{
      FILE *txt,*sdb,*tbl;
      unsigned long int p,i,c,endtbl,end,num,len,punt[1000],curr,lungf,y,lungfn;
      unsigned char table[256][256],byte,byte1,byte2,byte3,byte4;
      printf("Digimon World DS *.sdb Dumper v0.9\n\n"); 
           tbl=fopen("dgmnwrld.tbl","r+b");
           //carico la table
           for(i=0;i<256;i++)
           {
             for(c=0;c<256;c++)
             {
                table[i][c]='*';
                }}
           table[0xFD][0xFF]='\n';
           fseek(tbl,0x00,SEEK_END);
           endtbl=ftell(tbl);
           rewind(tbl);
           while(ftell(tbl)<endtbl)
           {
             byte1=fgetc(tbl);
             if (byte1 >= 0x30 && byte1 <= 0x39)
             {
                byte1=(byte1-0x30)*0x10;
                }else{
                      byte1=(byte1-0x37)*0x10;
                      }
             byte2=fgetc(tbl);
             if (byte2 >= 0x30 && byte2 <= 0x39)
             {
                byte2=(byte2-0x30);
                }else{
                      byte2=(byte2-0x37);
                      }
                      byte3=fgetc(tbl);
             if (byte3 >= 0x30 && byte3 <= 0x39)
             {
                byte3=(byte3-0x30)*0x10;
                }else{
                      byte3=(byte3-0x37)*0x10;
                      }
            byte4=fgetc(tbl);
             if (byte4 >= 0x30 && byte4 <= 0x39)
             {
                byte4=(byte4-0x30);
                }else{
                      byte4=(byte4-0x37);
                      }
             fseek(tbl,1,SEEK_CUR);
             byte=fgetc(tbl);
             table[byte1+byte2][byte3+byte4]=byte; 
             fseek(tbl,2,SEEK_CUR);
             }  
             //table caricata
             for(y=0;y<85;y++)
             {
                 lungfn=strlen(names[y]);
                 names[y][lungfn]=0;
                 sdb=fopen(names[y],"r+b");
                 fseek(sdb,0x00,SEEK_END);
                 lungf=ftell(sdb);
                 rewind(sdb);
                 end=0;
                 p=0;
                 while(end==0)
                 {
                  fread(&punt[p],4,1,sdb);
                  curr=ftell(sdb);
                  if(curr==punt[0])
                   end=1;
                  else
                   p++;
                 }
                 mkdir("Dumps");
                 chdir("Dumps");
                 texts[y][lungfn]=0;
                 txt=fopen(texts[y],"w+b");
                 for (i=0;i<=p;i++)
                 {
                  fseek(sdb,punt[i],SEEK_SET);
                  fread(buffer,0x250,1,sdb);
                  if(i==p)
                  {
                   len=lungf-punt[i];
                  }
                  else
                  {
                   len=punt[i+1]-punt[i];
                  }
                  for(c=0;c<len;c++)
                    {
                      if(strcmp(names[y],"DigZknHelp.sdb")==0)
                      {
                        if ((buffer[c]==0xE9))
                        {
                        fprintf(txt,"\n\n");
                        c++;
                        }else{
                        byte1=buffer[c];
                        byte2=buffer[c+1];                         
                        if (table[byte1][byte2]=='*')
                        {
                         fprintf(txt,"{%x}{%x}",byte1,byte2);
                         c++;
                         }else{                           
                         fprintf(txt,"%c",table[byte1][byte2]);
                         c++;
                        }
                        }
                      }
                      else
                      { 
                       if ((buffer[c]==0xFF && buffer[c+1]==0xFF) ||(buffer[c]==0xFE && buffer[c+1]==0xFF))
                      {
                       fprintf(txt,"\n\n");
                       c++;
                       }else{
                       byte1=buffer[c];
                       byte2=buffer[c+1];                         
                       if (table[byte1][byte2]=='*')
                       {
                         fprintf(txt,"{%x}{%x}",byte1,byte2);
                         c++;
                         }else{                           
                          fprintf(txt,"%c",table[byte1][byte2]);
                          c++;
                        } }   
                        }
                        }
                        }
                  fclose(txt);
                  chdir("..");
             }
             }
           
           
           
           
           
           
           
           
           
           
           
           
           
           
