//Dissidia Final Fantasy Bin Creator
#include <stdio.h>
#include <windows.h>

//per il package.bin leggo table2 e reinserisco i file in ordine, ricordandomi di far diventare il file multiplo di 0x800, ricordandomi di segnare l'offset di scrittura del file
//per il package_info.bin leggo table, tralascio i nomi dei file ma ne scrivo la dimensione e l'off di inizio ad una seconda passata.

BYTE buffer[10485760];

main()
{
      FILE *bin,*tbl,*ext,*table,*table2;
      unsigned long int num,fileoff[5500],peso[5500],sect,pad,name,i,c;
      unsigned char nome[10],byte1,byte2,byte3,byte4,header[0x10]={0x17,0x09,0x08,0x20,0x70,0x61,0x63,0x6B,0xB9,0x14,0x00,0x00,0x00,0x00,0x00,0x00};
      printf("Dissidia: Final Fantasy PACKAGE.BIN Creator by Vash v0.9b -www.romhacking.it-\n\n");
      
      bin=fopen("PACKAGE.BIN","w+b");
      tbl=fopen("PACKAGE_INFO.BIN","w+b");
      chdir("Package");
      table=fopen("table","r+b");
      table2=fopen("table2","r+b");
      //PACKAGE.BIN
      fseek(table2,0x00,SEEK_END);
      num=ftell(table2)/9;
      rewind(table2);
      for (i=0;i<num;i++)
      {
          printf("\rCreation in progress: %d%%",((i+1)*100)/num);
          fread(nome,9,1,table2);
          nome[9]=0;
          ext=fopen(nome,"r+b");
          fileoff[i]=ftell(bin);
          fseek(ext,0x00,SEEK_END);
          peso[i]=ftell(ext);
          rewind(ext);
          fread(buffer,peso[i],1,ext);
          fwrite(buffer,peso[i],1,bin);
          sect=peso[i]/0x800;
          if ((peso[i]%0x800) != 0)
          {
            sect++;
            }
         pad=(sect*0x800)-peso[i];   
         for (c=0;c<pad;c++)
         {
            fputc(0x00,bin);
            }
      fclose(ext);
      
      }        
      //Creato Package.bin e ho dimensione del file (peso[5500]) e offset di dove inizia (fileoff[5500])
      
      //PACKAGE_INFO.BIN
      fwrite(header,0x10,1,tbl);
      for (i=0;i<num;i++)
      {
       byte1=(fgetc(table)-0x30);   
       byte2=(fgetc(table)-0x30);
       byte3=(fgetc(table)-0x30);
       byte4=(fgetc(table)-0x30);
       name=(byte1*1000)+(byte2*100)+(byte3*10)+byte4;
       //fscanf(table,"%d",name);
       /*printf("\n%d+%d+%d+%d=%d\n",byte1,byte2,byte3,byte4,name);
       system("pause");*/
       fseek(table,5,SEEK_CUR);
       fread(buffer,8,1,table);
       fwrite(buffer,8,1,tbl);
       fwrite(&fileoff[name-1],4,1,tbl);
       fwrite(&peso[name-1],3,1,tbl);
       fseek(table,7,SEEK_CUR);
       fread(buffer,1,1,table);
       fwrite(buffer,1,1,tbl);
       }
       printf("\n\nCreation Complete. Enjoy");
       
       }
