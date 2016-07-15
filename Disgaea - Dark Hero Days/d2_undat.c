//Disgaea 2 Dark Hero Days DAT Unpacker by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    
    FILE *dat,*tbl,*ext;
    unsigned long int num,init,i,pointer[500],size[500],lunghezza;
    unsigned char head[8],name[500][500],stringa[256];
    
    if (argc < 2) printf("Disgaea 2 Dark Hero Days DAT Unpacker by Vash v0.9 -www.romhacking.it-\n\nd2_unlzs file.lzs\n\n");
      else{

dat=fopen(argv[1],"r+b");
fread(&head,8,1,dat);
if (strcmp(head,"NISPACK") == 0)
{
printf("Not a valid archive, use d2_unnis.exe instead.\n\n");
return(0);  
}
rewind(dat);
lunghezza=strlen(argv[1]);
sprintf(stringa, "%s",argv[1]);
stringa[lunghezza-4]=0;
mkdir(stringa);
chdir(stringa);
tbl=fopen("table","w+b");
fread(&num,4,1,dat);
init=(num*0x20)+0x10;
fseek(dat,0x10,SEEK_SET);
fread(&pointer[1],4,1,dat);
pointer[1]=pointer[1]+init;
pointer[0]=init;
fread(&name[0],0x1C,1,dat);
for (i=1;i<num;i++)
{
fread(&pointer[i+1],4,1,dat);
pointer[i+1]=pointer[i+1]+init;
fread(&name[i],0x1C,1,dat);
}

for (i=0;i<num;i++)
{
size[i]=pointer[i+1]-pointer[i];
}
for (i=0;i<num;i++)
{
fseek(dat,pointer[i],SEEK_SET);    
ext=fopen(name[i],"w+b");
printf("%s/%s\n",stringa,name[i]);
fwrite(&name[i],0x1c,1,tbl);
fread(buffer,size[i],1,dat);
fwrite(buffer,size[i],1,ext);
fclose(ext);
}

}}
