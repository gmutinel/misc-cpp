//Dissidia Final Fantasy Mpk Creator
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    FILE *mpk,*ext,*tbl;
    unsigned long int num,tmp;
    unsigned char stringa[1500],nome[50];
    if (argc < 2) printf("Dissidia Final Fantasy Mpk Creator by Vash v0.9 -www.romhacking.it-\n\nmpkcr dir\n\n");
      else{
      sprintf(stringa,"%s.mpk\0",argv[1]);
      pak=fopen(stringa,"w+b");
      chdir(argv[1]);
      tbl=fopen("table","r+b");
      fread(&num,4,1,tbl);
      //HEADER!!
      for (i=0;i<num;i++)
      {
          fread(&tmp,4,1,tbl);
          fread(nome,tmp,1,tbl);
          nome[tbl]=0;
          ext=fopen(nome,"r+b");
          
      
