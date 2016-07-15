//Nostalgia (USA) dat "MASS" Packer by Vash

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    FILE *mass,*tbl,*ext;
    unsigned long int num,point[2000],len[2000],i,start;
    unsigned char stringa[256],name[2000][0x21];
    
    if (argc < 2) printf("Nostalgia (USA) dat 'MASS' Packer by Vash v0.9 -www.romhacking.it-\n\nssam_packer directory\n\n");
      else{
    
    sprintf(stringa,"%s.dat\0",argv[1]);
    mass=fopen(stringa,"w+b");
    chdir(argv[1]);
    tbl=fopen("table","r+b");
    fseek(tbl,0x00,SEEK_END);
    num=(ftell(tbl))/0x20;
    fprintf(mass,"SSAM");
    fwrite(&num,4,1,mass);
    //printf("%x\n",num);
    rewind(tbl);
    point[0]=0;
    start=(num*0x28)+8;
    //system("pause");
    for (i=0;i<num;i++)
    {
      fwrite(&point[i],4,1,mass);
      fread(&name[i],0x20,1,tbl);  
      name[i][0x20]='\0';
      ext=fopen(name[i],"r+b");
      fseek(ext,0x00,SEEK_END);  
      len[i]=ftell(ext);
      fwrite(&len[i],4,1,mass);
      fwrite(&name[i],0x20,1,mass);
      point[i+1]=point[i]+len[i];
      while (((point[i+1]+start) % 0x10) != 0 )
      {
       point[i+1]=point[i+1]+1;     
       }      
     fclose(ext);  
    }   
   //system("pause");
    for (i=0;i<num;i++)
    {
      ext=fopen(name[i],"r+b");
      fread(buffer,len[i],1,ext);
      //fseek(mass,point[i],SEEK_SET);
      fwrite(buffer,len[i],1,mass);
      while ((ftell(mass) % 0x10) != 0 )
      {
        fputc(0x00,mass);
      }
     }
     
}}     
         
