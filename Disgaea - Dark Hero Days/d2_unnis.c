//Disgaea 2 Dark Hero Days NISPACK Unpacker by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    FILE *nis,*tbl,*ext;
    unsigned long int num,points[500],lens[500],i,boh[500],lunghezza;
    unsigned char names[500][500],stringa[256],head[8];
    
    if (argc < 2) printf("Disgaea 2 Dark Hero Days NISPACK Unpacker by Vash v0.9 -www.romhacking.it-\n\nd2_unnis file.dat\n\n");
      else{
           
           nis=fopen(argv[1],"r+b");
           fread(&head,8,1,nis);
           if (strcmp(head,"NISPACK") != 0)
           {
              printf("Not a valid NISPACK archive.\n\n");
              return(0);  
                }    
           fseek(nis,0x0C,SEEK_SET);
           fread(&num,4,1,nis);
           for (i=0;i<num;i++)
           {
               fread(&names[i],0x20,1,nis);
               fread(&points[i],4,1,nis);
               fread(&lens[i],4,1,nis);
                fread(&boh[i],4,1,nis);
           }
           lunghezza=strlen(argv[1]);
           sprintf(stringa, "%s",argv[1]);
           stringa[lunghezza-4]=0;
           mkdir(stringa);
           chdir(stringa);
           tbl=fopen("table","w+b");
           for (i=0;i<num;i++)
           {
               fwrite(&names[i],0x20,1,tbl);
               fwrite(&boh[i],4,1,tbl);
               ext=fopen(names[i],"w+b");
               printf("%s/%s\n",stringa,names[i]);
               fseek(nis,points[i],SEEK_SET);
               fread(buffer,lens[i],1,nis);
               fwrite(buffer,lens[i],1,ext);
               fclose(ext);
           }
           fclose(nis);
           fclose(tbl);
           }} 
               
                    
               
           
