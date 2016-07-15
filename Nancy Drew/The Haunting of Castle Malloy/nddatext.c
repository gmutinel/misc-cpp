/*Nancy Drew DAT Extractor by Vash*/
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
int main(int argc, char *argv[])
{
    FILE *dat,*ext,*tbl;
    unsigned long int end,pointer[9999],tableinit,num,i,lunghezza,length;
    unsigned char point1,point2,point3,point4,stringa[500],name[9999][37];
    if (argc < 2) printf("Nancy Drew DAT Extractor v0.9 by Vash\n\nnddatext file.dat \n\nNOTE:\nThis tool supports ONLY the new game files.\n\n");
     else {
          dat=fopen(argv[1],"r+b");
          lunghezza=strlen(argv[1]);
          sprintf(stringa, "%s.dat",argv[1]);
          stringa[lunghezza-4]=0;
          mkdir(stringa);
          chdir(stringa);
          fseek(dat,0x00,SEEK_END);
          end=ftell(dat);
          fseek(dat,end-4,SEEK_SET);
          point1=fgetc(dat);
          point2=fgetc(dat);
          point3=fgetc(dat);
          point4=fgetc(dat);
          tableinit=((point4*16777216+point3*65536+point2*256)+point1);
          fseek(dat,end-tableinit-4,SEEK_SET);
          point1=fgetc(dat);
          point2=fgetc(dat);
          point3=fgetc(dat);
          point4=fgetc(dat);
          num=((point4*16777216+point3*65536+point2*256)+point1);
          tbl=fopen("table","w+b");
          for (i=0;i<num;i++)
          {
           fread(name[i],33,1,dat);
           point1=fgetc(dat);
           point2=fgetc(dat);
           point3=fgetc(dat);
           point4=fgetc(dat);
           pointer[i]=((point4*16777216+point3*65536+point2*256)+point1);
           fwrite(name[i],33,1,tbl);
           sprintf(name[i],"%s.cif",name[i]);
           }
           pointer[i]=end-tableinit-4;
           // recuperati nomi dei file e puntatori
           for (i=0;i<num;i++)
          {
           fseek(dat,pointer[i],SEEK_SET);
           ext=fopen(name[i],"w+b");
           length=pointer[i+1]-pointer[i];
           fread(buffer,length,1,dat);
           fwrite(buffer,length,1,ext);
           fclose(ext);
           }
           
           
           
           }
           
           
           
}           
              
          
          
