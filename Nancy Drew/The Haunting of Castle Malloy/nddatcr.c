/*Nancy Drew DAT Creator by Vash*/
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
int main(int argc, char *argv[])
{
    FILE *dat,*ext,*tbl;
    unsigned long int c,end,pointer[9999],tableinit,num,i,lunghezza,length,byte1,byte2,byte3;
    unsigned char point1,point2,point3,point4,stringa[500],name[9999][33],nametemp[9999][37],header[28]={0x43,0x49,0x46,0x20,0x46,0x49,0x4C,0x45,0x20,0x48,0x65,0x72,0x49,0x6E,0x74,0x65,0x72,0x61,0x63,0x74,0x69,0x76,0x65,0x00,0x03,0x00,0x00,0x00};
    if (argc < 2) printf("Nancy Drew DAT Creator v0.9 by Vash\n\nnddatext directory \n\nNOTE:\n-This tool supports ONLY the new game files.\n-The directory MUST have been created by the Nancy Drew DAT Extractor\n\n");
     else {
     
     sprintf(stringa,"%s.dat",argv[1]);
     dat=fopen(stringa,"w+b");
     chdir(argv[1]);
     tbl=fopen("table","r+b");
     fseek(tbl,0x00,SEEK_END);
     num=ftell(tbl)/0x21;
     rewind(tbl);
     for (i=0;i<num;i++)
     {
         fread(name[i],33,1,tbl);
         sprintf(nametemp[i],"%s.cif",name[i]);
         }
    //recuperati i nomi dei file da inserire
    fwrite(header,28,1,dat);
    for (i=0;i<num;i++)
    {
        printf("%s\n",nametemp[i]);
        pointer[i]=ftell(dat);
        ext=fopen(nametemp[i],"r+b");
        fseek(ext,0x00,SEEK_END);
        end=ftell(ext);
        rewind(ext);
        fread(buffer,end,1,ext);
        fwrite(buffer,end,1,dat);
        fseek(dat,-(end-0x2c),SEEK_END);
        end=end-0x30;
        fwrite(&end,1,4,dat);
        fseek(dat,0x00,SEEK_END);
        fclose(ext);
        }
     fwrite(&num,1,4,dat);
     for (i=0;i<num;i++)
     {
         fprintf(dat,"%s",name[i]);
         for(c=0;c<0x21-strlen(name[i]);c++)
         {
                   fputc(0x00,dat);
                   }        
         fwrite(&pointer[i],1,4,dat);
         }
         end=(num*0x25)+4;
         fwrite(&end,1,4,dat);
            
        
        
        
        
        
        
        
        
        
        
        
        
         









}
}
