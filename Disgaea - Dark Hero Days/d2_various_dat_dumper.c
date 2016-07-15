//Disgaea 2 Dark Hero Days Various DAT Unpacker by Vash

//Every file seems to have a slightly different format so i have to build different functions for each one...fuck

#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

main()
{
FILE *dungeon,*chardat,*charhelp,*habit,*magic,*mitem,*music,*wish2,*dump;
unsigned long int num,len,i;
//unsigned char

//Dungeon.dat

if (fopen("dungeon.dat","r+b") == 0)
{
printf("Impossibile to open 'dungeon.dat'");                               
}else{
dungeon=fopen("dungeon.dat","r+b");      
dump=fopen("dungeon.txt","w+b");      
fread(&num,4,1,dungeon);      
fseek(dungeon,8,SEEK_SET);
for (i=0;i<num;i++)
{      
fread(buffer,0x16,1,dungeon);
len=strlen(buffer);
fwrite(buffer,len,1,dump);      
fprintf(dump,"\n");
fseek(dungeon,0x3A,SEEK_CUR);
}      
fclose(dungeon);
fclose(dump);
      }

//mitem.dat
if (fopen("mitem.dat","r+b") == 0)
{
printf("Impossibile to open 'mitem.dat'");                               
}else{
mitem=fopen("mitem.dat","r+b");      
dump=fopen("mitem.txt","w+b");   
fread(&num,4,1,mitem);  
fseek(mitem,8,SEEK_SET);
for (i=0;i<num;i++)
{ 
fread(buffer,0x15,1,mitem);
len=strlen(buffer);
fwrite(buffer,len,1,dump);
fprintf(dump,"\n");
fread(buffer,0x3B,1,mitem);
len=strlen(buffer);
fwrite(buffer,len,1,dump);        
fprintf(dump,"\n\n");
fseek(mitem,0x28,SEEK_CUR);
}      
fclose(mitem);
fclose(dump);   


     }

//habit.dat

if (fopen("habit.dat","r+b") == 0)
{
printf("Impossibile to open 'habit.dat'");                               
}else{
habit=fopen("habit.dat","r+b");      
dump=fopen("habit.txt","w+b");      
fread(&num,4,1,habit);      
fseek(habit,8,SEEK_SET);
for (i=0;i<num;i++)
{      
fread(buffer,0x20,1,habit);
len=strlen(buffer);
fwrite(buffer,len,1,dump);      
fprintf(dump,"\n");
fseek(habit,0x20,SEEK_CUR);
}      
fclose(habit);
fclose(dump);
      }




//magic.dat


if (fopen("magic.dat","r+b") == 0)
{
printf("Impossibile to open 'magic.dat'");                               
}else{
magic=fopen("magic.dat","r+b");      
dump=fopen("magic.txt","w+b");   
fread(&num,4,1,magic);  
fseek(magic,0x102,SEEK_SET);
for (i=0;i<num-2;i++)
{ 
fread(buffer,0x17,1,magic);
len=strlen(buffer);
fwrite(buffer,len,1,dump);
fprintf(dump,"\n");
fread(buffer,0x3B,1,magic);
len=strlen(buffer);
fwrite(buffer,len,1,dump);        
fprintf(dump,"\n\n");
fseek(magic,0x26,SEEK_CUR);
}      
fclose(magic);
fclose(dump);
}
}
