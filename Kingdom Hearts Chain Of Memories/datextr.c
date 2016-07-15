//Kingdom Hearts Chain Of Memories Dat Extractor
#include <stdio.h>
#include <windows.h>

BYTE buffer[2048];

int main(int argc, char *argv[])
{
    FILE *dat,*ext;
    unsigned long int type,end=0,c=0,i,len,q=0,s,pointerfile,lenfile,off,times,w,pointer,lunghezza;
    unsigned char name[24],tabella[25],stringa[50];
    if (argc < 2) printf("Kingdom Hearts Chain Of Memories Dat Extractor by Vash v0.9 -www.romhacking.it-\n\ndatext file.dat\n\n");    
      else{
           dat=fopen(argv[1],"r+b");
           lunghezza=strlen(argv[1]);
           sprintf(stringa,"%s",argv[1]);
           stringa[lunghezza-4]=0;
           mkdir(stringa);
           chdir(stringa);
           while (end!=1)
           {
             fread(&type,4,1,dat);    
             if (type==0x00)
             {
                end=1;
                }else{
                      c++;
                      fseek(dat,0x1C,SEEK_CUR);
                      }
                      }
            rewind(dat);          
            for (i=0;i<c;i++)
            {          
             fseek(dat,0x20*i,SEEK_SET);
             fread(&type,4,1,dat);
             tabella[0]=0;
             sprintf(tabella,"Table %d\0",type);
             mkdir(tabella);
             chdir(tabella);
             fread(&pointer,4,1,dat);
             pointer=pointer*0x800;
             fread(&len,4,1,dat);
             len=len*0x800;
             fseek(dat,pointer,SEEK_SET);
             end=0;
             while (end!=1)
           {    
             if (fgetc(dat)==0x00)
             {
                end=1;
                }else{
                      q++;
                      fseek(dat,0x2F,SEEK_CUR);
                      }
                      }
             
             fseek(dat,pointer,SEEK_SET);
             off=pointer;
             for (s=0;s<q;s++)
              {
                fseek(dat,off,SEEK_SET);
                fread(name,24,1,dat);
                ext=fopen(name,"w+b");
                printf("%s\\%s  [%d\\%d]\n",tabella,name,s+1,q);
                fseek(dat,0x0C,SEEK_CUR); 
                fread(&lenfile,4,1,dat);
                lenfile=lenfile*0x800; 
                fread(&pointerfile,4,1,dat);
                pointerfile=pointerfile*0x800;
                fseek(dat,0x04,SEEK_CUR); 
                off=ftell(dat);
                fseek(dat,pointer,SEEK_SET);
                fseek(dat,pointerfile,SEEK_CUR);
                times=lenfile/0x800;
                for (w=0;w<times;w++)
                {
                   fread(buffer,0x800,1,dat); 
                   fwrite(buffer,0x800,1,ext);
                }
                fclose(ext);
                fseek(dat,off,SEEK_SET);
              }
           chdir("..");
           q=0;
           }   
               }} 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                 
                                      
