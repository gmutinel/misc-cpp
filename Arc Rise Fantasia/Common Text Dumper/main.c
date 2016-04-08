//Arc Rise Fantasia Common Text Dumper

#include "arf_common_text_dumper.h"


int main(int argc,char** argv)
{
    
printf("Arc Rise Fantasia Common Text Dumper v0.1 by Vash -www.romhacking.it-\n\n");    
//check if all files are availables
filenumb = 2; //this variable will increase while writing the tool and adding support for more files
x=0;
for (i=0;i<filenumb;i++)
{
printf("Checking %s.....",files[i]);    
if (fopen(files[i],"r+b") != 0)
{
x++;
printf("OK\n");    
}else{
printf("Not Found!\n");    
}    
}

if (x!=filenumb)
{
printf("Some files are not found. Check the list above. The program will now close.\n\n");
system("pause");
return(0);    
}else{
mkdir("Dump");
//Operation.bin
printf("Dumping operation.bin...");      
DumpOperation();
printf("Done.\n");
chdir("..");
//Ability.bin
printf("Dumping ability.bin...");
DumpAbility();
printf("Done.\n");
chdir("..");
}//else
}//main
