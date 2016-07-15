//Disgaea 2 Dark Hero Days NISPACK Creator by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    FILE *nis,*tbl,*ext;
    unsigned long int i,num,point[500],lens[500],boh[500];
    unsigned char names[500][500],stringa[256],header[12]={0x4E,0x49,0x53,0x50,0x41,0x43,0x4B,0x00,0x00,0x00,0x00,0x00};
    
    if (argc < 2) printf("Disgaea 2 Dark Hero Days NISPACK Creator by Vash v0.01 -www.romhacking.it-\n\nd2_niscr directory\n\n");
      else{
      
      sprintf(stringa, "%s.dat",argv[1]);
      nis=fopen(stringa,"w+b");
      chdir(argv[1]);
      tbl=fopen("table","r+b");
      fwrite(&header,12,1,nis);
      fseek(tbl,0x00,SEEK_END);
      num=(ftell(tbl)/0x24);
      fwrite(&num,4,1,nis);
      rewind(tbl);
      point[0]=(num*0x2C)+0x10;
      if ((point[0] % 0x800) == 0)
      {
        point[0]=point[0];
        }else{
             point[0]=((point[0]/0x800)+1)*0x800;               
             }
      for (i=1;i<=num;i++)
      {
        fread(&names[i-1],0x20,1,tbl);
        fwrite(&names[i-1],0x20,1,nis);
        fwrite(&point[i-1],4,1,nis);
        ext=fopen(names[i-1],"r+b");
        fseek(ext,0x00,SEEK_END);
        lens[i-1]=ftell(ext);
        fclose(ext);
        fread(&boh[i-1],4,1,tbl);
        fwrite(&lens[i-1],4,1,nis);
        fwrite(&boh[i-1],4,1,nis);
        if ((point[i-1]+lens[i-1]) % 0x800 == 0)
        {
           point[i]=point[i-1]+lens[i-1];
        }else{
             point[i]=(((point[i-1]+lens[i-1])/0x800)+1)*0x800;               
             }                       
        
          }
        while (ftell(nis) != point[0])
        {  
         fputc(0x00,nis); 
         }  
       for (i=0;i<num;i++)
       {
         ext=fopen(names[i],"r+b");  
         printf("%s/%s\n",argv[1],names[i]);
         fread(buffer,lens[i],1,ext);
         fwrite(buffer,lens[i],1,nis);
         fclose(ext);
         if (i != num-1)
         {
         while (ftell(nis) != point[i+1])
        {  
         fputc(0x00,nis); 
         }
         }
         }      
          
          
          }}
      
