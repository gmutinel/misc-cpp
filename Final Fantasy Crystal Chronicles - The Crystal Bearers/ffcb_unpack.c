//Final Fantasy Crystal Chronicles - The Crystal Bearers Unpacker

#include <stdio.h>
#include <windows.h>

unsigned long int Endian_Int_Conversion(unsigned long int dword)
{
   return ((dword>>24)&0x000000FF) | ((dword>>8)&0x0000FF00) | ((dword<<8)&0x00FF0000) | ((dword<<24)&0xFF000000);
}

BYTE buffer[10485760];

int main(int argc, char *argv[])
{
    
    FILE *log, *ext, *dat, *pos;
    unsigned long int num,n0=0,n1=0,n2=0,n3=0,init,end,off,point[5000],len[5000],i=0,c=1; 
    unsigned char temp[100],name[5000][10];  
    
    if (argc < 3) printf("Final Fantasy Crystal Chronicles - The Crystal Bearers Unpacker by Vash v0.92\n-www.romhacking.it-\n\nffcb_unpack file WITHOUT EXTENSION A/B\nEx: ffcb_unpack dvdimageA A\n\n");    
      else{
  printf("Final Fantasy Crystal Chronicles - The Crystal Bearers Unpacker by Vash v0.92\n-www.romhacking.it-\n\n");
  sprintf(temp,"%s.pos\0",argv[1]);
  pos=fopen(temp,"r+b");
  sprintf(temp,"%s.dat\0",argv[1]);
  dat=fopen(temp,"r+b");         
  mkdir(argv[1]);
  chdir(argv[1]);
  log=fopen("archive.bin","w+b");
  fprintf(log,"File generated with ffcb_unpack, do not modify or remove this.");
  fseek(pos,4,SEEK_SET);
  fread(&num,4,1,pos);
  num=Endian_Int_Conversion(num);
  fwrite(&num,4,1,log);
  fread(buffer,num*8,1,pos);
  fwrite(buffer,num*8,1,log);
  init=(num*8)+8+4+4;
  fseek(pos,0x00,SEEK_END);
  end=ftell(pos);
  fseek(pos,init,SEEK_SET);
  off=ftell(pos);
  while (off != end)//recupero pointer e dim
  {
  off=ftell(pos);
  sprintf(name[i],"%x%x%x%x%s.dat\0",n0,n1,n2,n3,argv[2]);      //in caso di riutilizzo, togliere %s e argv[2], mettere name a 9 e l'if a < 2                         
  fread(&point[i],4,1,pos);
  point[i]=Endian_Int_Conversion(point[i])*0x800;
  fread(&len[i],4,1,pos);
  len[i]=Endian_Int_Conversion(len[i]);
  if (len[i] == 0x00)
  {
    c=c+1;           
  }else{
   i=i+1;
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
  fwrite(name[i-1],9,1,log);
  fwrite(&c,2,1,log);
  c=1;
  }
  }
  fclose(log);
  fclose(pos);
  
  for (c=0;c<i;c++)
  {
    ext=fopen(name[c],"w+b");  
    printf("\rExtracting file %d on %d",c+1,i);
    fseek(dat,point[c],SEEK_SET);  
    fread(buffer,len[c],1,dat);
    fwrite(buffer,len[c],1,ext);
    fclose(ext); 
  }   
  printf("\nDone. Enjoy!\n\n");     
}}          
