/*The Tales Of Bingwood DLG Reinserter by Vash*/
#include <stdio.h>
#include <windows.h>

BYTE buffer[1048576];
int main(int argc, char *argv[])
{
    
    FILE *dlg, *log, *txt, *shit;
    unsigned long int num,lunghezza,pointer,shitpoint,match=0,z=0,i,off=0x00,end;
    unsigned char stringa[50];
    
    if (argc < 2) printf("The Tales Of Bingwood DLG Reinserter by Vash v0.9 by Vash\n\nadvext file.log \n\n");
     else {
          
log=fopen(argv[1],"r+b");
fseek(log,0x00,SEEK_END);
num=ftell(log)/4;
rewind(log);
lunghezza=strlen(argv[1]);
sprintf(stringa,"%s",argv[1]);
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.dlg",stringa);
dlg=fopen(stringa,"w+b");
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.txt",stringa);
txt=fopen(stringa,"r+b");
fseek(txt,0x00,SEEK_END);
end=ftell(txt);
rewind(txt);
stringa[lunghezza-4]=0;
sprintf(stringa, "%s.shit",stringa);
shit=fopen(stringa,"r+b");
for (i=0;i<num;i++)
{
    fread(&shitpoint,4,1,shit);//recupero lunghezza del pezzo di robaccia
    fread(buffer,shitpoint,1,shit);//leggo il pezzo
    fwrite(buffer,shitpoint,1,dlg);//lo scrivo nel nuovo dlg
    fread(buffer,end-off,1,txt);//leggo tutto il file da dove sono alla fine così da essere sicuro di prendere tutta la prima frase e di trovarne così la lunghezza
    while (match!=1) //ciclo che recupera la lunghezza 'z' della frase
    {
       if (buffer[z]==0x0A)
       {
            match=1;
       }else{
             z++;
             }
    } 
    fseek(txt,off,SEEK_SET);//torno indietro per leggere la frase                               
    fwrite(&z,4,1,dlg);//scrivo nel nuovo dlg la lunghezza della frase
    fread(buffer,z,1,txt);//copio la frase nel buffer...
    fwrite(buffer,z,1,dlg);//...e la scrivo nel nuovo dlg
    //riazzero le variabili per il ciclo while
    z=0;
    match=0;
    fseek(txt,1,SEEK_CUR);//mi sposto di 1 in avanti sul txt a causa dello 0x0A
    off=ftell(txt);

}
//inserisco l'ultimo pezzo di robaccia
fread(&shitpoint,4,1,shit);
fread(buffer,shitpoint,1,shit);
fwrite(buffer,shitpoint,1,dlg);
}
}

