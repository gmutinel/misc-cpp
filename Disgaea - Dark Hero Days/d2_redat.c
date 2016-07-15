//Disgaea 2 Dark Hero Days DAT Packer by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    
    FILE *dat,*tbl,*ext;
    unsigned long int num,end[500],i,point=0;
    unsigned char stringa[256],name[500][28],head[0x0C]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    if (argc < 2) printf("Disgaea 2 Dark Hero Days DAT Packer by Vash v0.9 -www.romhacking.it-\n\nd2_redat directory\n\n");
      else{

    sprintf(stringa,"%s.DAT\0",argv[1]); 
    dat=fopen(stringa,"w+b");
    chdir(argv[1]);
    tbl=fopen("table","r+b");
    fseek(tbl,0x00,SEEK_END);
    num=(ftell(tbl))/0x1C;
    rewind(tbl);
    fwrite(&num,0x04,1,dat);
    fwrite(&head,0x0C,1,dat);
    for (i=0;i<num;i++)
    {
        fread(&name[i],28,1,tbl);
        ext=fopen(name[i],"r+b");
        fseek(ext,0x00,SEEK_END);
        end[i]=ftell(ext);
        rewind(ext);
        point=point+end[i];
        fwrite(&point,4,1,dat);
        fwrite(&name[i],28,1,dat);
        fclose(ext);
    }
    
    for (i=0;i<num;i++)
    {
      ext=fopen(name[i],"r+b");
      fread(buffer,end[i],1,ext);
      fwrite(buffer,end[i],1,dat);
      fclose(ext);
    }  
}}
