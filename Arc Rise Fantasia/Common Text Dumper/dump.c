#include "arf_common_text_dumper.h"

void DumpOperation(void)
{
text=fopen("operation.bin","r+b");
chdir("Dump");
dump=fopen("operation.txt","w+b");
shit=fopen("operation.sht","w+b");
for (i=0;i<7;i++)
{
fread(buffer,0x18,1,text);
len=strlen(buffer);
fwrite(buffer,len,1,dump);
fprintf(dump,"\n");
fread(buffer,0x60,1,text);
len=strlen(buffer);
fwrite(buffer,len,1,dump);
fprintf(dump,"\n\n");    
}
fread(buffer,0x78,1,text);
fwrite(buffer,0x78,1,shit);    
fclose(text);
fclose(shit);
fclose(dump);
}


void DumpAbility(void)
{
text=fopen("ability.bin","r+b");
chdir("Dump");
dump=fopen("ability.txt","w+b");
shit=fopen("ability.sht","w+b");
fread(buffer,0x92,1,text);
fwrite(buffer,0x92,1,shit);
for (i=0;i<225;i++)
{
fread(buffer,0x15,1,text);
len=strlen(buffer);
fwrite(buffer,len,1,dump);
fprintf(dump,"\n");
fread(buffer,0x51,1,text);
len=strlen(buffer);
fwrite(buffer,len,1,dump);
fprintf(dump,"\n\n");
fread(buffer,0x2C,1,text);
fwrite(buffer,0x2C,1,shit);    
}
fread(buffer,0xDB0,1,text);
fwrite(buffer,0xDB0,1,shit);    
fclose(text);
fclose(shit);
fclose(dump);    
}
