//Arc Rise Fantasia VOL Unpacker by Vash

#include <windows.h>
#include <stdio.h>

BYTE buffer[10485760];

unsigned long int Endian_Int_Conversion(unsigned long int dword)
{
   return ((dword>>24)&0x000000FF) | ((dword>>8)&0x0000FF00) | ((dword<<8)&0x00FF0000) | ((dword<<24)&0xFF000000);
}

int main(int argc, char *argv[])
{
FILE *vol,*ext;
unsigned long int lunghezza,point[9999],len[9999],num,i,tmp,c;
unsigned char head[5],stringa[500],name[9999][0x21];
int xor;
if (argc < 2) printf("Arc Rise Fantasia VOL Unpacker by Vash v0.91 -www.romhacking.it-\n\narf_vol_unpacker file.vol\n\n");
      else{

printf("Arc Rise Fantasia VOL Unpacker by Vash v0.91 -www.romhacking.it-)\n\n");

vol=fopen(argv[1],"r+b");
fread(head,4,1,vol);
head[4]=0x00;
if (strcmp(head,"RTDP\0") != 0)
{
printf("This is not a proper VOL archive.\n");
return(0);    
}
lunghezza=strlen(argv[1]);
sprintf(stringa, "%s",argv[1]);
stringa[lunghezza-4]=0;
sprintf(stringa, "%s",stringa);
mkdir(stringa);
chdir(stringa);
fseek(vol,0x04,SEEK_SET);
fread(&tmp,4,1,vol);
tmp=Endian_Int_Conversion(tmp);
fread(&num,4,1,vol);
num=Endian_Int_Conversion(num);
fseek(vol,0x10,SEEK_SET);
xor=fgetc(vol);
fseek(vol,0x20,SEEK_SET);
for (i=0;i<num;i++)
{
fread(name[i],0x20,1,vol);
name[i][0x20]=0x00;
if (strcmp(name[i],"reserved_file")==0)
{
fseek(vol,8,SEEK_CUR);
num--;
i--;   
}else{
fread(&len[i],4,1,vol);   
len[i]=Endian_Int_Conversion(len[i]);
fread(&point[i],4,1,vol);
point[i]=Endian_Int_Conversion(point[i]);    
point[i]=point[i]+tmp;
//tmp=point[i];
//printf("point[%d](%x)=point[%d](%x)+tmp(%x)\n",i,point[i],i-1,point[i-1],tmp);
}   
}

for (i=0;i<num;i++)
{
fseek(vol,point[i],SEEK_SET);
fread(buffer,len[i],1,vol);

for (c=0;c<len[i];c++)
{ 
buffer[c]=buffer[c]^xor;   
}
ext=fopen(name[i],"w+b");
printf("%s [0x%x]\n",name[i],point[i]);
fwrite(buffer,len[i],1,ext);
fclose(ext);
}
}}
