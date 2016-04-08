//string.tab deleter from lang file

#include <stdio.h>
#include <windows.h>

BYTE buffer[4];

main()
{
FILE *lang;
unsigned long int   check=0, i;   
      
if ((fopen("~en.vbf","r+b")) != NULL)      
{
lang=fopen("~en.vbf","r+b");                        
}

if ((fopen("~us.vbf","r+b")) != NULL)      
{
lang=fopen("~us.vbf","r+b");                        
}

if ((fopen("~pl.vbf","r+b")) != NULL)      
{
lang=fopen("~pl.vbf","r+b");                        
}

if ((fopen("~de.vbf","r+b")) != NULL)      
{
lang=fopen("~de.vbf","r+b");                        
}

if ((fopen("~es.vbf","r+b")) != NULL)      
{
lang=fopen("~es.vbf","r+b");                        
}

if ((fopen("~sp.vbf","r+b")) != NULL)      
{
lang=fopen("~sp.vbf","r+b");                        
}

if ((fopen("~fr.vbf","r+b")) != NULL)      
{
lang=fopen("~fr.vbf","r+b");                        
}

if ((fopen("~ru.vbf","r+b")) != NULL)      
{
lang=fopen("~ru.vbf","r+b");                        
}


while (check != 1)
{
//printf("%x\n",ftell(lang));
fread(buffer,4,1,lang);
if ((buffer[0] == 0x2E) && (buffer[1] == 0x74) && (buffer[2] == 0x61) && (buffer[3] == 0x62))   
{
fseek(lang,-0x1C,SEEK_CUR);
for (i=0;i<0x21;i++)
{
fputc(0x00,lang);    
}    
check=1;               
}  else{
        fseek(lang,-0x3,SEEK_CUR);               }
}            
}
