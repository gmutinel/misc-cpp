#include <stdio.h>
#include <windows.h>
BYTE buffer[51200];

int main()
{
      FILE *txt,*pak,*tbl;
      unsigned long int lunghezza,lungtot,i,c,endtbl,num,pointerbase[500],lenbase[500],pointers[500][500],lens[500][500],init,tmp,len,part=1,q,now;
      unsigned char stringa[50],table[256][256],byte,byte1,byte2,byte3,byte4;
      printf("Digimon World Dusk MSG.PAK Dumper by Vash v0.9 -www.romhacking.it-\n\n"); 
       
           pak=fopen("MSG.PAK","r+b");
           tbl=fopen("table.tbl","r+b");
           //carico la table
           for(i=0;i<256;i++)
           {
             for(c=0;c<256;c++)
             {
                table[i][c]='*';
                }}
          // table[0xFF][0xFF]='<end>\n\n';
           table[0xFD][0xFF]='\n';
         //  table[0xFE][0xFF]='\n\n';
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
             //system("pause");
             //table caricata
             
             
             fread(&num,4,1,pak);
             for (i=0;i<num;i++)
             {
               fread(&pointerbase[i],4,1,pak);
               fread(&lenbase[i],3,1,pak);
               fseek(pak,1,SEEK_CUR);  
                 }
             fseek(pak,0x00,SEEK_END);    
             pointerbase[i]=ftell(pak); 
             for (i=0;i<num;i++)
             {
               fseek(pak,pointerbase[i],SEEK_SET);
               fread(&tmp,4,1,pak);
               tmp=tmp/4;
               fseek(pak,pointerbase[i],SEEK_SET);
               for (c=0;c<tmp;c++)
               {
                fread(&pointers[i][c],4,1,pak);    
                 }
                 pointers[i][c]=pointerbase[i+1]-pointerbase[i];
               //  printf("%x\n",pointers[i][c]);
                 for (c=0;c<tmp;c++)
               {
                lens[i][c]=pointers[i][c+1]-pointers[i][c];
              // printf("%x=%x-%x\n",lens[i][c],pointers[i][c+1],pointers[i][c]);
                 }       
            // system("pause");
             
             }
             mkdir("Dumps");
             chdir("Dumps");
             for (i=0;i<num;i++)
             {
             lunghezza=7;
             sprintf(stringa, "MSG.PAK");
             stringa[lunghezza-4]=0;
             sprintf(stringa, "%s.%d.txt",stringa,part);
             txt=fopen(stringa,"w+b"); 
             part++;
             
             fseek(pak,pointerbase[i],SEEK_SET);
             fread(&tmp,4,1,pak);
             tmp=tmp/4;
            // printf("%x   %x   %x\n",pointerbase[i],lenbase[i], tmp);
          //   system("pause");
             for(q=0;q<tmp;q++)
                {
                  fseek(pak,pointerbase[i]+pointers[i][q],SEEK_SET);
               //  printf("%s: %x  %x\n",stringa,ftell(pak),lens[i][q]);
             //system("pause");
                  fread(buffer,lens[i][q],1,pak);
                   
                   for(c=0;c<lens[i][q];c++)
                {
                   
                   if ((buffer[c]==0xFF && buffer[c+1]==0xFF) ||(buffer[c]==0xFE && buffer[c+1]==0xFF))
                  {
                   fprintf(txt,"\n\n");
                   c++;
                   }else{
                         
                       /*  if (buffer[c]==0xED && buffer[c+1]==0xFF)
                  {
                   fprintf(txt,"<start>\n");
                   c++;
                   }else{*/
                   
                   byte1=buffer[c];
                   byte2=buffer[c+1];                         
                   if (table[byte1][byte2]=='*')
                   {
                     fprintf(txt,"{%x}{%x}",byte1,byte2);
                     c++;
                     }else{                           
                   fprintf(txt,"%c",table[byte1][byte2]);
                   c++;
               //    }
                    } }   
                    }
                    
                    }
             fclose(txt);
             
             }
             
             }
           
           
           
           
           
           
           
           
           
           
           
           
           
           
