//Resident Evil Code Veronica X Text Dumper By Vash
#include <stdio.h>
#include <windows.h>
BYTE buffer[51200];
//0xFFFF=fine frase; 0x00FF=A capo
int main(int argc, char *argv[])
{
      FILE *txt,*ald,*tbl;
      unsigned long int lunghezza,lungtot,i,c,endtbl,num,pointer[500],init,len,part=1,q;
      unsigned char stringa[50],table[256][256],byte,byte1,byte2,byte3,byte4;
      
      if (argc < 2) printf("Resident Evil Code Veronica X Text Dumper By Vash v0.9\n\nrecvxdump file.ald");
      else{
           ald=fopen(argv[1],"r+b");
           
           tbl=fopen("recvx.tbl","r+b");
           //carico la table
           for(i=0;i<256;i++)
           {
             for(c=0;c<256;c++)
             {
                table[i][c]='*';
                }}
           //table[0xFF][0xFF]="<end>";
           table[0x00][0xFF]='\n';
           fseek(tbl,0x00,SEEK_END);
           endtbl=ftell(tbl);
           rewind(tbl);
           while(ftell(tbl)<endtbl)
           {
             byte1=fgetc(tbl);
             if (byte1 >= 0x30 && byte1 <= 0x39)
             {
                byte1=(byte1-0x30)*0x10;
                }else{
                      byte1=(byte1-0x37)*0x10;
                      }
             byte2=fgetc(tbl);
             if (byte2 >= 0x30 && byte2 <= 0x39)
             {
                byte2=(byte2-0x30);
                }else{
                      byte2=(byte2-0x37);
                      }
              byte3=fgetc(tbl);
             if (byte3 >= 0x30 && byte3 <= 0x39)
             {
                byte3=(byte3-0x30)*0x10;
                }else{
                      byte3=(byte3-0x37)*0x10;
                      }
            byte4=fgetc(tbl);
             if (byte4 >= 0x30 && byte4 <= 0x39)
             {
                byte4=(byte4-0x30);
                }else{
                      byte4=(byte4-0x37);
                      }
             fseek(tbl,1,SEEK_CUR);
             byte=fgetc(tbl);
             table[byte1+byte2][byte3+byte4]=byte; 
             //printf("%x%x = %c\n",byte1+byte2,byte3+byte4,byte);
             fseek(tbl,2,SEEK_CUR);
             }  
             //table caricata
             for (q=0;q<2;q++)
             {
             lunghezza=strlen(argv[1]);
             sprintf(stringa, "%s",argv[1]);
             stringa[lunghezza-4]=0;
             sprintf(stringa, "%s.%d.txt",stringa,part);
             txt=fopen(stringa,"w+b");    
             fread(&lungtot,4,1,ald);
             init=ftell(ald);
             fread(&num,4,1,ald);
             for(i=0;i<num;i++)
             {
               fread(&pointer[i],4,1,ald);
               }
               pointer[i]=lungtot;
              for(i=0;i<num;i++)
              {
                fseek(ald,pointer[i]+init,SEEK_SET);                  
                len=pointer[i+1]-pointer[i];
                fread(buffer,len,1,ald);
                printf("%x\n",len);
                for(c=0;c<len;c++)
                {
                  if (buffer[c]==0xFF && buffer[c+1]==0xFF)
                  {
                   fprintf(txt,"<end>\n\n");
                   c++;
                   }else{
                   byte1=buffer[c];
                   byte2=buffer[c+1];                         
                   if (table[byte1][byte2]=='*')
                   {
                     fprintf(txt,"{%x}{%x}",byte1,byte2);
                     c++;
                     }else{                           
                   fprintf(txt,"%c",table[byte1][byte2]);
                   c++;
                   }
                         }
                
                } 
               }
               fclose(txt);
               part++;
               }
               
                }}                               
           
           
