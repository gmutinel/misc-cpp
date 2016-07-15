#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];
unsigned short int Endian_Short_Conversion(unsigned short int word) 
{ 
      return ((word>>8)&0x00FF) | ((word<<8)&0xFF00) ; 
}
int main(int argc, char *argv[])
{
    FILE *dat,*txt;
    unsigned short int num=0,byte;
    unsigned long int s=-1,q,m,txtlen,length,lunghezza,end[1500],i=0,sum=0,c,off[1500],keys[16]={0x98ED,0xAB90,0x285E,0x4284,0xB132,0xDA2D,0x57A6,0xBFC8,0x3300,0x9A57,0x27F2,0x4C4B,0xA736,0x7D92,0x9D73,0xCE84};
    unsigned char stringa[50];
    txt=fopen(argv[1],"r+b");
    lunghezza=strlen(argv[1]);
    sprintf(stringa,"%s",argv[1]);
    stringa[lunghezza-4]=0;
    sprintf(stringa,"%s.dat\0",stringa);
    dat=fopen(stringa,"w+b");
    fseek(txt,0x00,SEEK_END);
    txtlen=ftell(txt);
    rewind(txt);
    fread(buffer,txtlen,1,txt);
    for (c=0;c<txtlen-3;c++)
    {
       if (buffer[c]==0x0D && buffer[c+1]==0x00 && buffer[c+2]==0x0A && buffer[c+3]==0x00)
       {
         num++;
         end[i]=c;
         i++;
         //printf("%x\n",end[i-1]);
         }                  
     }
     rewind(txt);
     fwrite(&num,2,1,dat);
     for (c=0;c<num;c++)
     {     
        fputc(0x00,dat);
        fputc(0x00,dat);
        }
    for (c=0;c<num;c++)
    {   
    s++;
       if (s>=16)
             {s=0;}
    length=end[c]-sum+2;
    sum=end[c]+4;
    //printf("LENGTH: %x   SUM: %x\n",length,sum);
    off[c]=(ftell(dat)/2);
    if (length==2)
    {
       off[c]=0x00;
       }else{                      
    fwrite(&length,2,1,dat);
    fread(buffer,length-2,1,txt);
    q=s;
    buffer[length-2]=0x00;
    buffer[length-1]=0x00;
    for (m=0;m<length;m++)
          {
             byte=((buffer[m]*0x100)+buffer[m+1]);
             byte=byte^keys[q];
             byte=Endian_Short_Conversion(byte);
             fwrite(&byte,2,1,dat);
             m++;
             q++;
             if (q>=16)
             {q=0;}
             }}
    //fwrite(buffer,length-2,1,dat);
    //fputc(0x00,dat);
    //fputc(0x00,dat);
    fseek(txt,4,SEEK_CUR);
    //printf("%x\n",ftell(dat));
}
fseek(dat,2,SEEK_SET);
for (c=0;c<num;c++)
    {
      fwrite(&off[c],2,1,dat);
      }             
}
           
           
