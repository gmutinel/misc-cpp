/*The Tales Of Bingwood ADV Creator by Vash*/
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
int main(int argc, char *argv[])
{
    FILE *ext,*adv,*shit,*tbl;
    unsigned char fixpath[0x12]={0x44, 0x3A, 0x5C, 0x42, 0x75, 0x67, 0x46, 0x61, 0x63, 0x74, 0x6F, 0x72, 0x79, 0x5C, 0x41, 0x57, 0x45, 0x5C}, header[0x0C]={0x00, 0x00, 0xA0, 0x43, 0x00, 0x00, 0x70, 0x43,/* 4 byte che indicano il totale dei file png -->*/0x39, 0x04, 0x00, 0x00};
    unsigned long int lunghezza,i,len,endext,end;
    unsigned char stringa[250];
    if (argc < 2) printf("The Tales Of Bingwood ADV Creatore by Vash v0.9 by Vash\n\nadvext file.adv \n\n");
     else {
          
        adv=fopen(argv[1],"w+b");
        lunghezza=strlen(argv[1]);
        sprintf(stringa, "%s",argv[1]);
        stringa[lunghezza-4]=0;
        chdir(stringa);
        tbl=fopen("table.dat","r+b");
        sprintf(stringa, "%s.shit",stringa);
        shit=fopen(stringa,"r+b");
        fwrite(header,0x0C,1,adv);//scritto l'header (compreso il totale delle png, per cui non è molto generico)
        for (i=0;i<1096;i++)//numero dei file png e dlg
        {
          fread(&len,4,1,tbl);
          len=len+0x12;
          fwrite(&len,4,1,adv);//scrittura della lunghezza del percorso
          fwrite(fixpath,0x12,1,adv);//scrittura del percorso fisso
          len=len-0x12;
          fread(stringa,len,1,tbl);//lettura del resto del percorso
          stringa[len]=0;//metto uno /0 dopo l'ultimo carattere del percorso finale del file
          ext=fopen(stringa,"r+b");//apro il file da inserire
          fwrite(stringa,len,1,adv);//scrivo il resto del percorso
          fseek(ext,0x00,SEEK_END);//vado alla fine per...
          endext=ftell(ext);//...recuperare la fine del file e...
          fwrite(&endext,4,1,adv);//...la scrivo
          rewind(ext);//torno all'inizio del file
          fread(buffer,endext,1,ext);//bufferizzo l'intero file...
          fwrite(buffer,endext,1,adv);//...e lo scrivo
          if (i==1080)
          {
             fread(buffer,0xf84c,1,shit);//finite le png copio il primo pezzo di robaccia
             fwrite(buffer,0xf84c,1,adv);//e lo incollo nel file
             }
             fclose(ext);
             }
             //finiti anche i 15 dlg incollo il resto di robaccia
             fseek(shit,0x00,SEEK_END);
             end=ftell(shit);
             fseek(shit,0xf84c,SEEK_SET);
             fread(buffer,end-0xf84c,1,shit);
             fwrite(buffer,end-0xf84c,1,adv);
             }
             }    
          
        
        
        
