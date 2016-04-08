//Arc Rise Fantasia BSCR Dumper by Vash

#include <windows.h>
#include <stdio.h>
#include <string.h>

BYTE buffer[10485760];
BYTE buffer2[10485760];
BYTE buffer3[10485760];
FILE *ascii, *tags;
unsigned long int tagsnumb;
unsigned char table[256],tagval[500][500],tagsymb[500][500];
unsigned long int Endian_Int_Conversion(unsigned long int dword)
{
   return ((dword>>24)&0x000000FF) | ((dword>>8)&0x0000FF00) | ((dword<<8)&0x00FF0000) | ((dword<<24)&0xFF000000);
}

unsigned short int Endian_Short_Conversion(unsigned short int word) 
{ 
      return ((word>>8)&0x00FF) | ((word<<8)&0xFF00) ; 
}

void LoadTable(void);
void ParseSentece(void);
void LoadTags(void);
void ParseSentenceWithTags(void);

int main(int argc, char *argv[])
{
FILE *bscr,*dump,*tbl;
unsigned long int i,tmp,lunghezza,num,c,textstart,bcdinfolen,bcdstart,secpoint[5000],bcdlen[5000],numpoints,textpoint[5000],textlen;
unsigned char stringa[500],head[5],secname[5000][0x21];
unsigned short int seclen;
if (argc < 2) printf("Arc Rise Fantasia BSCR Dumper by Vash v0.9 -www.romhacking.it-\n\narf_bscr_dumper file.bscr\n\n");
      else{

printf("Arc Rise Fantasia BSCR Dumper by Vash v0.9 -www.romhacking.it-)\n\n");
bscr=fopen(argv[1],"r+b");
fread(head,5,1,bscr);
if (strcmp(head,"bscr\0") != 0)
{
printf("This is not a proper BSCR file.\n");
return(0);    
}
ascii=fopen("arf.tbl","r+b");
LoadTable();
tags=fopen("arf_tags.tbl","r+b");
LoadTags();
lunghezza=strlen(argv[1]);
sprintf(stringa, "%s",argv[1]);
stringa[lunghezza-4]=0;
sprintf(stringa, "%stxt",stringa);
dump=fopen(stringa,"w+b");
stringa[lunghezza-4]=0;
sprintf(stringa, "%stbl",stringa);
tbl=fopen(stringa,"w+b");

fseek(bscr,0x28,SEEK_SET);
fread(&num,4,1,bscr);
num=Endian_Int_Conversion(num);

fseek(bscr,0x00,SEEK_END);
secpoint[num]=ftell(bscr);

fseek(bscr,0x34,SEEK_SET);
fread(&textstart,4,1,bscr);
textstart=Endian_Int_Conversion(textstart);

fread(&bcdinfolen,4,1,bscr);
bcdinfolen=Endian_Int_Conversion(bcdinfolen);

fread(&bcdstart,4,1,bscr);
bcdstart=Endian_Int_Conversion(bcdstart);
fwrite(&num,4,1,tbl);
for (i=0;i<num;i++)
{
fread(&seclen,2,1,bscr);
seclen=Endian_Short_Conversion(seclen);
fseek(bscr,0x2,SEEK_CUR);
fread(secname[i],0x20,1,bscr);
secname[i][0x20]=0x00;
fread(&secpoint[i],4,1,bscr);
secpoint[i]=Endian_Int_Conversion(secpoint[i]);
secpoint[i]=secpoint[i]+bcdstart;
tmp=seclen-0x28;
fread(buffer,tmp,1,bscr);
fwrite(&tmp,4,1,tbl);
fwrite(buffer,tmp,1,tbl);
//printf("%s [LEN=%x][NOW=%x]\n",secname[i],seclen,ftell(bscr));
}

for (i=0;i<num;i++)
{
fprintf(dump,"[%s]\n\n",secname[i]);    
bcdlen[i]=secpoint[i+1]-secpoint[i];    
fseek(bscr,secpoint[i],SEEK_SET);
fread(buffer,bcdlen[i],1,bscr);
numpoints=0;
fwrite(&bcdlen[i],4,1,tbl);
fwrite(buffer,bcdlen[i],1,tbl);
for (c=0;c<bcdlen[i];c++)
{
if ((buffer[c]==0x1A && buffer[c+1]==0xF0 && buffer[c+2]==0xF1 && buffer[c+3]==0x5A) || (buffer[c]==0x81 && buffer[c+1]==0x00 && buffer[c+2]==0xF3 && buffer[c+3]==0xF2))
{
textpoint[numpoints]=(buffer[c+4]*0x1000000)+(buffer[c+5]*0x10000)+(buffer[c+6]*0x100)+(buffer[c+7]);
numpoints++;
}  
}
//found pointers
for (c=0;c<numpoints;c++)
{
fseek(bscr,textpoint[c]+textstart,SEEK_SET);
fread(buffer,bcdstart,1,bscr);
ParseSentenceWithTags();
ParseSentence();
textlen=strlen(buffer2);
//printf("%d\n",textlen);
fwrite(buffer2,textlen,1,dump);  
fprintf(dump,"\n\n");
}}
}
}

void LoadTable()
{
unsigned long int i,c,endtbl;
unsigned char byte,byte1,byte2;        
for(i=0;i<256;i++)
           {
                table[i]='*';
                }
           
           fseek(ascii,0x00,SEEK_END);
           endtbl=ftell(ascii);
           rewind(ascii);
           while(ftell(ascii)<endtbl)
           {
             byte1=fgetc(ascii);
             if (byte1 >= 0x30 && byte1 <= 0x39)
             {
                byte1=(byte1-0x30)*0x10;
                }else{
                      byte1=(byte1-0x37)*0x10;
                      }
             byte2=fgetc(ascii);
             if (byte2 >= 0x30 && byte2 <= 0x39)
             {
                byte2=(byte2-0x30);
                }else{
                      byte2=(byte2-0x37);
                      }
             
             fseek(ascii,1,SEEK_CUR);
             byte=fgetc(ascii);
             table[byte1+byte2]=byte; 
            // printf("%x = %c\n",byte1+byte2,table[byte1+byte2]);
             fseek(ascii,2,SEEK_CUR);
            
            //add tags here
            table[0x0A]='\n';
             }
             //system("pause");
}

void LoadTags(void)
{
unsigned long int end,len; 
unsigned char byte[50];
fseek(tags,0x00,SEEK_END);
end=ftell(tags);
rewind(tags);
tagsnumb=0;
while (ftell(tags) < end)
{
fread(&len,4,1,tags);
fread(tagval[tagsnumb],len,1,tags);
tagval[tagsnumb][len]=0;
fread(&len,4,1,tags);
fread(tagsymb[tagsnumb],len,1,tags);
tagsymb[tagsnumb][len]=0;
tagsnumb=tagsnumb+1;
//printf("NOW: %X  END: %X\n",ftell(tags),end);
}
//printf("%x\n",tagsnumb);

}

ParseSentence()
{
unsigned long int  x,i,len;
unsigned char tmp;
len=strlen(buffer3);
x=0;
buffer2[0]=0;
for (i=0;i<len;i++)
{
tmp=buffer3[i];
if (table[tmp] == '*')
if (tmp<16)
sprintf(buffer2,"%s{0%X}",buffer2,tmp);
else
sprintf(buffer2,"%s{%X}",buffer2,tmp);
else
sprintf(buffer2,"%s%c",buffer2,table[tmp]);
}  
}

void ParseSentenceWithTags(void)
{
unsigned long int  i,len,posnum;
unsigned char tmp;    
char *init,*pos;
len=strlen(buffer);
buffer3[0]=0;

for (i=0;i<tagsnumb;i++)
{
while (strstr(buffer,tagval[i]) != NULL)
{
pos=strstr(buffer,tagval[i]);
init=strstr(buffer,buffer);
posnum=pos-init;
strncpy(buffer3,buffer,posnum);
buffer3[posnum]=0;
sprintf(buffer3,"%s%s%s\0",buffer3,tagsymb[i],pos+strlen(tagval[i]));
sprintf(buffer,"%s\0",buffer3);
}        
} 
sprintf(buffer3,"%s\0",buffer);   
}
