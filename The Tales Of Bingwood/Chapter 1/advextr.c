/*The Tales Of Bingwood ADV Extractor by Vash*/
#include <stdio.h>
#include <windows.h>
#include <string.h>

BYTE buffer[10485760];
int main(int argc, char *argv[])
{
    FILE *ext,*adv,*shit,*tbl;
    unsigned long int lunghezza,num,len,i,c=0,sum=0,z,match[220],off,end;
    unsigned char stringa[50],direfile[500], *pch,dir[150];
    if (argc < 2) printf("The Tales Of Bingwood ADV Extractor by Vash v0.9 by Vash\n\nadvext file.adv \n\n");
     else {
          
        adv=fopen(argv[1],"r+b");
        lunghezza=strlen(argv[1]);
        sprintf(stringa, "%s",argv[1]);
        stringa[lunghezza-4]=0;
        mkdir(stringa);
        chdir(stringa);
        tbl=fopen("table.dat","w+b");
        sprintf(stringa, "%s.shit",stringa);
        shit=fopen(stringa,"w+b");
        fseek(adv,8,SEEK_SET);
        fread(&num,4,1,adv);
        num=num+15;
        for (i=0;i<num;i++)
        {
            fread(&len,4,1,adv);
            len=len-0x012;
            fwrite(&len,4,1,tbl);
            fseek(adv,0x12,SEEK_CUR);
            fread(direfile,len,1,adv);
            fseek(adv,-len,SEEK_CUR);
            direfile[len]=0;
            pch=strchr(direfile,0x5C);
             while (pch!=NULL)
             {
             //printf ("found at %x\n",pch-direfile+1);
             match[c]=pch-direfile+1;
             pch=strchr(pch+1,0x5C);
             c++;
             }
             
             //printf ("founded: %x\n",c);
             
             for (z=0;z<c;z++)
             {
             fread(dir,match[z]-sum-1,1,adv);
             dir[match[z]-sum-1]=0;
             sum=match[z];
             fseek(adv,1,SEEK_CUR);
             printf("%s\\",dir);
             fprintf(tbl,"%s\\",dir);
             mkdir(dir);
             chdir(dir);
             }
             
             fread(dir,len-sum,1,adv);
             dir[len-sum]=0;
             printf("%s\n",dir);
             fprintf(tbl,"%s",dir);
             ext=fopen(dir,"w+b");    
             fread(&len,4,1,adv);
             fread(buffer,len,1,adv);
             fwrite(buffer,len,1,ext);
             fclose(ext);
            // system("pause");
             //fseek(adv,len,SEEK_CUR);
             for (z=0;z<c;z++)
             {
                 chdir("..");
                 }
             c=0;
             sum=0;
             pch=0;
             //system("pause");
             if (i==(num-16))
             {
                 fread(buffer,0xf84c,1,adv);
                 fwrite(buffer,0xf84c,1,shit);
                 }
             
             }
             off=ftell(adv);
             fseek(adv,0x00,SEEK_END);
             end=ftell(adv);
             fseek(adv,off,SEEK_SET);
             fread(buffer,(end-off),1,adv);
             fwrite(buffer,(end-off),1,shit);
             }}
