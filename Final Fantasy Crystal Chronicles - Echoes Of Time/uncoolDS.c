#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

main()
{
      FILE *rsb,*ext,*tbl;
      unsigned long int off=0x14,init,len[9999],point[9999],i=0,n0=0,n1=0,n2=0,n3=1,c,s0=0,s1=0,s2=1,tmpp[4],tmpl[4],d;
      unsigned char stringa[50];
      
      printf("Final Fantasy Crystal Chronicles Echoes Of Time Extractor (Ds Version)\nby Vash v0.9 -www.romhacking.it-\n\n");
      rsb=fopen("coolres.rsb","r+b");
      mkdir("CoolresDS");
      chdir("CoolresDS");
      mkdir("Text");
      chdir("Text");
      mkdir("Eng");
      mkdir("Fra");
      mkdir("Ger");
      mkdir("Spa");
      chdir("..");
      tbl=fopen("table","w+b");
      fseek(rsb,0x14,SEEK_SET);
      fread(&init,4,1,rsb);
      fseek(rsb,off,SEEK_SET);
      while (off < init)
      {
           
           fread(&point[i],4,1,rsb);
           fread(&len[i],3,1,rsb); 
           i++;
           if (point[i-1]==0x00)
           {
              i--;
              fseek(rsb,1,SEEK_CUR);
              fputc(0x00,tbl);
              }else{
           fputc(fgetc(rsb),tbl);
          // printf("OFF: %x\nLEN: %x\n\n",point[i-1],len[i-1]);
           //system("pause");
           }
      off=ftell(rsb);
      }
      //fine ciclo raccolta puntatori e dimensioni
      //inizio estrazione dei file e divisione del testo
      for (c=0;c<i;c++)  
      {
         fseek(rsb,point[c],SEEK_SET);  
         sprintf(stringa, "%d%d%d%d.dat\0",n0,n1,n2,n3);
         if (len[c]!=0x00)
           {
             ext=fopen(stringa,"w+b");             
             fread(buffer,len[c],1,rsb);             
             fwrite(buffer,len[c],1,ext);
             fclose(ext);
             //aumento numerazione
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
              //fine
              }
         if (len[c]==0x00)
         {
                                           
             for (d=0;d<4;d++)
             {
             fread(&tmpp[d],4,1,rsb);
             fread(&tmpl[d],3,1,rsb);
             fseek(rsb,1,SEEK_CUR);
             }
             chdir("Text"); 
             //for (d=0;d<4;d++)
             //INGLESE            
             if (tmpp[d]!=0x00)
             {
             sprintf(stringa, "%d%d%d.eng\0",s0,s1,s2);             
             chdir("Eng");             
             ext=fopen(stringa,"w+b");             
             fseek(rsb,tmpp[0],SEEK_SET);
             fread(buffer,tmpl[0],1,rsb);
             fwrite(buffer,tmpl[0],1,ext);
             chdir("..");
             fclose(ext);
             //FRANCESE            
             sprintf(stringa, "%d%d%d.fra\0",s0,s1,s2);             
             chdir("Fra");             
             ext=fopen(stringa,"w+b");             
             fseek(rsb,tmpp[1],SEEK_SET);
             fread(buffer,tmpl[1],1,rsb);
             fwrite(buffer,tmpl[1],1,ext);
             chdir(".."); 
             fclose(ext);
             //TEDESCO           
             sprintf(stringa, "%d%d%d.ger\0",s0,s1,s2);             
             chdir("Ger");             
             ext=fopen(stringa,"w+b");             
             fseek(rsb,tmpp[2],SEEK_SET);
             fread(buffer,tmpl[2],1,rsb);
             fwrite(buffer,tmpl[2],1,ext);
             chdir(".."); 
             fclose(ext);
             //SPAGNOLO            
             sprintf(stringa, "%d%d%d.spa\0",s0,s1,s2);             
             chdir("Spa");             
             ext=fopen(stringa,"w+b");             
             fseek(rsb,tmpp[3],SEEK_SET);
             fread(buffer,tmpl[3],1,rsb);
             fwrite(buffer,tmpl[3],1,ext);
             chdir("..");
             fclose(ext);
             } else {
             //INGLESE       
             sprintf(stringa, "%d%d%d.eng\0",s0,s1,s2);             
             chdir("Eng");             
             ext=fopen(stringa,"w+b");
             chdir("..");
             fclose(ext);
             //FRANCESE
             sprintf(stringa, "%d%d%d.fra\0",s0,s1,s2);             
             chdir("Fra");             
             ext=fopen(stringa,"w+b");
             chdir("..");
             fclose(ext);
             //TEDESCO
             sprintf(stringa, "%d%d%d.ger\0",s0,s1,s2);             
             chdir("Ger");             
             ext=fopen(stringa,"w+b");
             chdir("..");
             fclose(ext);
             //SPAGNOLO
             sprintf(stringa, "%d%d%d.spa\0",s0,s1,s2);             
             chdir("Spa");             
             ext=fopen(stringa,"w+b");
             chdir("..");
             fclose(ext);
             }
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
                                 }              
                          
                          
                          }                     
                          
                          
                          
                          
                          
                          
                          
                          
                          
                          
                          
          
          
          
          
}
