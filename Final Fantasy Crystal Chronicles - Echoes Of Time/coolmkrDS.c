#include <stdio.h>
#include <windows.h>
BYTE buffer[10485760];
BYTE textf[4][10485760];
main()
{
 
  FILE *rsb,*ext,*tbl;
  unsigned long int i,punt[100000],tmp,n0=0,n1=0,n2=0,n3=1,byte,end,s0=0,s1=0,s2=1,endt[4],ciccia,somma,z,pointculo;
  unsigned char stringa[0x14]={0x06, 0x00, 0x00, 0x00, 0x08, 0x0C, 0x06, 0x06, 0x0C, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},nome[9];
  
  printf("Final Fantasy Crystal Chronicles Echoes Of Time RSB Maker (Ds Version)\nby Vash v0.9 -www.romhacking.it-\n\n");
  rsb=fopen("coolres.rsb","w+b");
  chdir("CoolresDS");
  tbl=fopen("table","r+b");
  fwrite(stringa,0x14,1,rsb);
  //calcolo puntatori
  for (i=0;i<((0xFFFF)*8);i++)
  {
      fputc(0x00,rsb);
      //fputc(0x00,rsb);
      //fputc(0x00,rsb);
      //fputc(0x00,rsb);
      //fputc(0x00,rsb);
      //fputc(0x00,rsb);
      //fputc(0x00,rsb);
      //fputc(0x00,rsb);
      
  }
 // system("pause");
  tmp=ftell(rsb);
  while ((tmp-0x0C)%0x10 != 0) //puntatori in posizione 0xXXXXXC
  {
    
    fputc(0x00,rsb);
    tmp=ftell(rsb);
  }     
  
  for (i=0;i<0xFFFF;i++)
  {
     punt[i]=ftell(rsb);
     byte=fgetc(tbl);
     if (byte == 0x60 || byte == 0x40)
     {
      sprintf(stringa, "%d%d%d%d.dat\0",n0,n1,n2,n3);
      ext=fopen(stringa,"r+b");
      fseek(ext,0x00,SEEK_END);
      end=ftell(ext);
      rewind(ext);
      fread(buffer,end,1,ext);
      fwrite(buffer,end,1,rsb);
      tmp=ftell(rsb);
      while ((tmp-0x0C)%0x10 != 0) //puntatori in posizione 0xXXXXXC
  {
    
    fputc(0x00,rsb);
    tmp=ftell(rsb);
  }
      
      fseek(rsb,0x14+(i*8),SEEK_SET);
      fwrite(&punt[i],4,1,rsb);
      fwrite(&end,3,1,rsb);
      fputc(byte,rsb);
      fseek(rsb,0x00,SEEK_END);
      if (n3==9)
                   {
                   n3=0;
                   n2=n2+1;
                   }else{
                   n3=n3+1;
                         }
                         if (n2==10)
                         {
                         n2=0;
                         n1=n1+1;
                          }
                          if (n1==10)
                         {
                         n1=0;
                         n0=n0+1;
                          }
      fclose(ext);
      }
      if (byte == 0x80)
      {
      chdir("Text");
      //INGLESE
      chdir("Eng");      
      sprintf(stringa, "%d%d%d.eng\0",s0,s1,s2);
      ext=fopen(stringa,"r+b");
      fseek(ext,0x00,SEEK_END);
      endt[0]=ftell(ext);
      rewind(ext);
      fread(textf[0],endt[0],1,ext);
      fclose(ext);
      chdir("..");
      //FRANCESE
      chdir("Fra");      
      sprintf(stringa, "%d%d%d.fra\0",s0,s1,s2);
      ext=fopen(stringa,"r+b");
      fseek(ext,0x00,SEEK_END);
      endt[1]=ftell(ext);
      rewind(ext);
      fread(textf[1],endt[1],1,ext);
      fclose(ext);
      chdir("..");
      //TEDESCO
      chdir("Ger");      
      sprintf(stringa, "%d%d%d.ger\0",s0,s1,s2);
      ext=fopen(stringa,"r+b");
      fseek(ext,0x00,SEEK_END);
      endt[2]=ftell(ext);
      rewind(ext);
      fread(textf[2],endt[2],1,ext);
      fclose(ext);
      chdir("..");
      //SPAGNOLO
      chdir("Spa");      
      sprintf(stringa, "%d%d%d.spa\0",s0,s1,s2);
      ext=fopen(stringa,"r+b");
      fseek(ext,0x00,SEEK_END);
      endt[3]=ftell(ext);
      rewind(ext);
      fread(textf[3],endt[3],1,ext);
      fclose(ext);
      chdir("..");
      //fine raccolta info lingue
      if (s2==9)
                         {
                         s2=0;
                         s1=s1+1;
                          }else{s2++;}
                          if (s1==10)
                         {
                         s1=0;
                         s0=s0+1;
                          }
      chdir("..");
      ciccia=ftell(rsb);
     // somma=0;
      fputc(0x00,rsb);//eng p
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);//eng d
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);//fra p
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);//fra d
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);//ger p
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);//ger d
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);//spa p
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);//spa d
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      if (endt[0] != 0x00)
      {
         
         for (z=0;z<4;z++)
         {
            pointculo=ftell(rsb);
            fwrite(textf[z],endt[z],1,rsb); 
            tmp=ftell(rsb);
            while ((tmp-0x0C)%0x10 != 0) //puntatori in posizione 0xXXXXXC
            {
    
             fputc(0x00,rsb);
             tmp=ftell(rsb);
            }
            fseek(rsb,ciccia+(z*8),SEEK_SET);
            fwrite(&pointculo,4,1,rsb);
            fwrite(&endt[z],3,1,rsb);
            fputc(0xC0,rsb);
            fseek(rsb,0x00,SEEK_END);
            
        }    } 
      fseek(rsb,0x14+(i*8),SEEK_SET);
      fwrite(&punt[i],4,1,rsb);      
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(byte,rsb);
      fseek(rsb,0x00,SEEK_END);
      }//else
      if (byte == 0x00)
      {
      fseek(rsb,0x14+(i*8),SEEK_SET);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fputc(0x00,rsb);
      fseek(rsb,0x00,SEEK_END);
      }
      }//for
      }//main
      
     
     
     
     
     
     
     
     
     
     
     
     
     
     
      
       
