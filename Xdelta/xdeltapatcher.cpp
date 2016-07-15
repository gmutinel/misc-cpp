#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define NMAX 99999

void cmd(int,int);
void puliscivett(char []);

char stringa[NMAX];
FILE *fcmd;

int main()
{
 FILE *flist;
 int i,lunga,pos=0;
 int lung=NMAX;
 flist=fopen("listold.txt","r");
 if(flist!=NULL)
 {
  fcmd=fopen("patch.cmd","w");
  while(fgets(stringa,lung,flist)!=NULL)
  {
    lunga=strlen(stringa);
    for(i=lunga;i>=0;i--)
    {
     if((stringa[i]=='\\')&&(stringa[i-1]=='D')&&(stringa[i-2]=='L')&&(stringa[i-3]=='O')&&(stringa[i-4]=='\\'))
     {
      pos=i+1;
      i=-1;
     }
    }
    cmd(lunga,pos);
  }
  fprintf(fcmd,"del /f /q /s *.tbh");
  fprintf(fcmd,"\n");
  fprintf(fcmd,"del /f /q /s xdelta.exe");
  fprintf(fcmd,"\n");
  fprintf(fcmd,"del /f /q /s patch.cmd");
  fclose(flist);
  fclose(fcmd);
 }
 return 0;
}

void cmd(int lunga,int pos)
{
 int u=0;
 char filename[NMAX];
 char byte=0x22;
 puliscivett(filename);
 for(int i=pos;i<=lunga-2;i++)
 {
  filename[u]=stringa[i];
  u++;
 }
 sprintf(filename,"%s\0",filename);
 fprintf(fcmd,"xdelta patch %c%s.tbh%c %c%s%c %c%s.tmp%c\n",byte,filename,byte,byte,filename,byte,byte,filename,byte);
 fprintf(fcmd,"del %c%s%c\n",byte,filename,byte);
 fprintf(fcmd,"move %c%s.tmp%c %c%s%c\n",byte,filename,byte,byte,filename,byte);
}

void puliscivett(char filename[])
{
 for(int i=0;i<=99999;i++)
      filename[i]=0;
}
