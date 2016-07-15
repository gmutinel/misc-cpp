/*The Tales Of Bingwood DLG Dumper by Vash*/
#include <stdio.h>
#include <windows.h>

BYTE buffer[1048576];
int main(int argc, char *argv[])
{
    FILE *dlg, *log, *txt, *shit;
    unsigned long int i,num,pointer,lunghezza,off=0x00,end,len;
    unsigned char stringa[50],testo[500];
    if (argc < 2) printf("The Tales Of Bingwood DLG Dumper by Vash v0.9 by Vash\n\nadvext file.log \n\n");
     else {

log=fopen(argv[1],"r+b");
fseek(log,0x00,SEEK_END);
num=ftell(log)/4;
rewind(log);
lunghezza=strlen(argv[1]);
sprintf(stringa,"%s",argv[1]);
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.dlg",stringa);
//printf("%s\n",stringa);
dlg=fopen(stringa,"r+b");
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.txt",stringa);
//printf("%s\n",stringa);
txt=fopen(stringa,"w+b");
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.shit",stringa);
shit=fopen(stringa,"w+b");
for (i=0;i<num;i++)
{
    fread(&pointer,4,1,log);//leggo il primo puntatore dal log
    fread(buffer,pointer-off,1,dlg);//recupero il pezzo di robaccia
    len=pointer-off;
    fwrite(&len,4,1,shit);//scrivo la lunghezza del pezzo
    fwrite(buffer,pointer-off,1,shit);//e scrivo il pezzo
    //fseek(dlg,pointer,SEEK_SET);
    fread(&pointer,4,1,dlg);//leggo la dimensione della frase
    //printf("%x\n",pointer);
    fread(buffer,pointer,1,dlg);//copio la frase
    fwrite(buffer,pointer,1,txt);//scrivo la frase sul dump
    fprintf(txt,"\n");//a capo
    off=ftell(dlg);//off prendere il valore della posizione attuale, cioè la fine della frase
}
fseek(dlg,0x00,SEEK_END);
end=ftell(dlg);
fseek(dlg,off,SEEK_SET);
fread(buffer,end-off,1,dlg);
pointer=end-off;
fwrite(&pointer,4,1,shit);
fwrite(buffer,pointer,1,shit);
}
}
