#include <stdio.h>
#include <windows.h>
#include <string.h>

main()
{
FILE *listnew;
FILE *listold;
FILE *cmd;
int offl=0x00,offcmd=0x00, a=0,b=0,c=0,z=0,i,q=0,off=0x00,offtmp=0x00,w,s=0;
char bytel,bytec,bytecnv2,bytecnv3,bytecnv4,bytecnv5;
unsigned char bytecnv1,tmp,tmp2;
system("dir NEW /A:-D /b /s  >> listnew.txt");
system("dir OLD /A:-D /b /s >> listold.txt");
listnew=fopen("listnew.txt","r+b");
listold=fopen("listold.txt","r+b");
cmd=fopen("createpatch.cmd","w+");
system("del /s /q /f cnv\\*.*");
//ciclo for per individuare il numero di righe da scrivere
while (i!=1)
{
tmp=fgetc(listnew);
if (tmp==0x0A)
{
z=z+1;
}
else
{
    if (tmp==0xFF)
    {
                 i=1;
                 }}}
fseek(listnew, 0x00, SEEK_SET);
//ciclo che crea il primo script
for (i=0;i<z;i++)
{
fputc(0x78,cmd);
fputc(0x64,cmd);
fputc(0x65,cmd);
fputc(0x6C,cmd);
fputc(0x74,cmd);
fputc(0x61,cmd);
fputc(0x20,cmd);
fputc(0x64,cmd);
fputc(0x65,cmd);
fputc(0x6C,cmd);
fputc(0x74,cmd);
fputc(0x61,cmd);
fputc(0x20,cmd);
s=0;
q=0;
a=0;
b=0;
c=0;
fputc(0x22,cmd);
offtmp=ftell(listold);
tmp=fgetc(listold);
//if (w==1)
//{
 //        q=q+1;
  //       }
if (tmp!=0x0A && tmp!=0x0D)
{
          fseek(listold, offtmp, SEEK_SET);  
          
          } 
          offtmp=ftell(listnew);
tmp=fgetc(listnew);

if (tmp!=0x0A && tmp!=0x0D)
{
          fseek(listnew, offtmp, SEEK_SET);  
          } 
          
//crea il primo argv
while (a!=1)
{
      bytel=fgetc(listold);
      if (bytel == 0x0D)
      {
                a=1;
                fputc(0x22,cmd);
                }
                else
                {
                fputc(bytel, cmd);
                }
                offcmd=offcmd+1;
                q=q+1;
                }
                
                
                fputc(0x20, cmd);
                fputc(0x22,cmd);
                offcmd=offcmd+2;
                //crea il secondo argv
                while (b!=1)
{
      bytel=fgetc(listnew);
      
      if (bytel == 0x0D)
      {
                b=1;
                fputc(0x22,cmd);
                }
                else
                {
                fputc(bytel, cmd);
                }
                offcmd=offcmd+1;
                }
                
                
                fputc(0x20, cmd);
                fputc(0x22,cmd);
               offcmd=offcmd+2;
               //crea il terzo argv 
                off=ftell(listold);
                fseek(listold, off-q, SEEK_SET);
                while (c!=1)
{
      
while (s!=1)
{      
bytecnv1=fgetc(listold);
bytecnv2=fgetc(listold);
bytecnv3=fgetc(listold);
bytecnv4=fgetc(listold);
bytecnv5=fgetc(listold);
off=ftell(listold);
if (bytecnv1==0x5C && bytecnv2==0x4F && bytecnv3==0x4C && bytecnv4==0x44 && bytecnv5==0x5C)
{
                   fputc(0x5C,cmd);
                   fputc(0x63,cmd);
                   fputc(0x6E,cmd);
                   fputc(0x76,cmd);
                   fputc(0x5C,cmd);
                   s=1;
                   }
                   else
                   {
                       fputc(bytecnv1, cmd);
                       fseek(listold, off-4, SEEK_SET);
                       }
                       }
                       bytecnv1=fgetc(listold);
      if (bytecnv1 == 0x0D)
      {
                c=1;
                fputc(0x2E,cmd);
                fputc(0x74,cmd);
                fputc(0x62,cmd);
                fputc(0x68,cmd);
                fputc(0x22,cmd);
                fputc(0x0A,cmd);
                }
                else
                {
                
                fputc(bytecnv1, cmd);
                }
                }
                
                }
                             
                }
