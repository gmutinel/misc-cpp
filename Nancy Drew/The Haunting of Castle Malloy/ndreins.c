/*Nancy Drew: The Haunting Of Castle Malloy Text Reinserter by Vash*/
#include <stdio.h>
#include <windows.h>
BYTE buffer[512000];
BYTE firsthird[512000];
BYTE thirdthird[512000];
int main(int argc, char *argv[])
{
FILE *txt,*lua;
unsigned long int pointer,lunghezza,first,end=0,length,third,endlua,endtxt,off=0x00,byte=0x00,c=0;
unsigned char stringa[250];
if (argc < 2) printf("Nancy Drew: The Haunting Of Castle Malloy Text Reinserter by Vash v0.1\n\nndreins file.txt");
      else {
           
           txt=fopen(argv[1],"r+b");
           lunghezza=strlen(argv[1]);
           sprintf(stringa, "%s",argv[1]);
           stringa[lunghezza-4]=0;
           sprintf(stringa, "%s.cif",stringa);
           lua=fopen(stringa,"r+b");
           fseek(lua,0x00,SEEK_END);
           endlua=ftell(lua);
           fseek(lua,0x3C,SEEK_SET);
           fread(&pointer,4,1,lua);
           fseek(lua,pointer+0x0C,SEEK_CUR);
           fread(&pointer,4,1,lua);
           fseek(lua,(pointer*4)+0x21,SEEK_CUR);
           first=ftell(lua);
           rewind(lua);
           fread(firsthird,first,1,lua);
           fseek(lua,first,SEEK_SET);
           while (end!=1)
           {
           fseek(lua,1,SEEK_CUR);
           if (fgetc(lua)!=0x04)
           {
               end=1;
               }else{
                     fread(&length,4,1,lua);
                     fseek(lua,length-1,SEEK_CUR);
                     }
                     }
                     third=ftell(lua)-1;
                     fseek(lua,third,SEEK_SET);
                     fread(thirdthird,(endlua-third),1,lua);
                     //printf("%x\n",third);
                     fclose(lua);
                     lua=fopen(stringa,"w+b");
                     fwrite(firsthird,first,1,lua);
                     //recuperate le parti di codice LUA coompilato prima e dopo il testo e aggiunta la prima
                     fseek(txt,0x00,SEEK_END);
                     endtxt=ftell(txt);
                     rewind(txt);
                     fputc(0x00,lua);
                     while(off<endtxt)
                     {
                       while(byte!=0x0A)
                       {
                         byte=fgetc(txt);
                         c++;
                         }
                         fseek(txt,-c,SEEK_CUR);
                         fread(buffer,c-1,1,txt);
                         fputc(0x04,lua);
                         fwrite(&c,4,1,lua);
                         fwrite(buffer,c-1,1,lua);
                         fputc(0x00,lua);
                         fseek(txt,2,SEEK_CUR);
                         off=ftell(txt);
                         c=0;
                         byte=0x00;
                     
                     
                     }
                     //system("pause");
                     fwrite(thirdthird,endlua-third,1,lua);
                     fseek(lua,0x00,SEEK_END);
                     endlua=ftell(lua)-0x30;
                     fseek(lua,0x2C,SEEK_SET);
                     fwrite(&endlua,4,1,lua);
                     fclose(lua);
                     }
                     }
           
           
