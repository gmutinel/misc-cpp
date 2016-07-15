//Dissidia Final Fantasy Bin Extractor
#include <stdio.h>
#include <windows.h>

BYTE buffer[10485760];

//void fillheaders(void);
main()
{
    FILE *bin,*tbl,*ext,*table,*table2/*,*log*/;
    unsigned long int q,i,pointer[5500],ordin[5500],realdim[5500],realdimord[5500],j,app,c,n0=0,n1=0,n2=0,n3=1,dim,times,resto,t,tableorder[5500],realtableorder[5500];
    long int rest;
    unsigned char stringa[8],head[16],temp[8],shit[5500][16],temptable[5500][0x19],realtable[5500][0x19];
    unsigned char headers[1000][16]={{0x4d, 0x50, 0x4b, 0x20},
                                     {0x89, 0x50, 0x4e, 0x47},
                                     {0x41, 0x52, 0x43, 0x01},
                                     {0x52, 0x49, 0x46, 0x46},
                                     {0x53, 0x53, 0x43, 0x46, 0x10, 0x02, 0x07, 0x02},
                                     {0x4d, 0x49, 0x47, 0x2e, 0x30, 0x30, 0x2e, 0x31},
                                     {0x54, 0x49, 0x4d, 0x32, 0x04, 0x00, 0x01},
                                     {0x6d, 0x65, 0x6e, 0x75, 0x20, 0x70, 0x61, 0x6b},
                                     {0x72, 0x6d, 0x66, 0x64, 0x02, 0x00, 0x04, 0x00},
                                     {0x6d, 0x65, 0x73, 0x73, 0x20, 0x70, 0x61, 0x6b},
                                     {0x4f, 0x4d, 0x47, 0x2e, 0x30, 0x30, 0x2e, 0x31, 0x50, 0x53, 0x50},
                                     {0x70, 0x72, 0x6f, 0x67},
                                     {0x44, 0x45, 0x53, 0x34},
                                     {0x0, 0x50, 0x53, 0x46}};      


unsigned char extension[1000][16]={{'.','m','p','k',' '},
                                   {'.','p','n','g',' '},
                                   {'.','a','r','c',' '},
                                   {'.','a','t','3',' '},
                                   {'.','s','s','c','f'},
                                   {'.','g','i','m',' '},
                                   {'.','t','m','2',' '},
                                   {'.','p','a','k',' '},
                                   {'.','r','m','f','d'},
                                   {'.','p','a','k',' '},
                                   {'.','g','m','o',' '},
                                   {'.','p','r','o','g'},
                                   {'.','d','e','s','4'},
                                   {'.','s','f','o',' '}};                      
unsigned long int tothead=14,lenhead[1000]={4,4,4,4,8,8,7,8,8,8,11,4,4,4};
    printf("Dissidia: Final Fantasy PACKAGE.BIN Extractor by Vash v0.82 -www.romhacking.it-\n\n");
    
   if (fopen("PACKAGE.BIN","r+b")==NULL) 
    {
    printf("I need the file PACKAGE.BIN\n");
    return(0);
     }
   if (fopen("PACKAGE_INFO.BIN","r+b")==NULL) 
    {
    printf("I need the file PACKAGE_INFO.BIN\n");
    return(0);
     }
     //system("pause");
     
     //fillheaders();
     
     
     
     
     
     
     bin=fopen("PACKAGE.BIN","r+b");
     tbl=fopen("PACKAGE_INFO.BIN","r+b");
     //log=fopen("headers.log","w+b");
     fseek(tbl,0x10,SEEK_SET);
      for (i=0;i<0x14B9;i++)
     {
         fread(shit[i],16,1,tbl);
         }   
     
     fseek(tbl,0x18,SEEK_SET);
     
     for (i=0;i<0x14B9;i++)
     {
         fread(&pointer[i],4,1,tbl);
         fread(&realdim[i],3,1,tbl);
         fseek(tbl,0x9,SEEK_CUR);
         }
        
        /* for (i=0;i<0x14AA;i++)
     {
        printf("%x\n",pointer[i]);
        }
        printf("\n\nORDINATO:\n\n");*/
        //system("pause");
         //ordinamento
         for (i=0; i<0x14B9; i++) 
         {
    app=pointer[i];
    c=0;
    for (j=0; j<0x14B9; j++) 
         {
              if (app>pointer[j])
              {
                c++;
                }
                
                }   
                ordin[c]=app;              
                realdimord[c]=realdim[i];
                }   
                          
//fine ordinamento 

//fseek(bin,0x00,SEEK_END);
//ordin[0x14AA]=ftell(bin);  
//rewind(bin);
mkdir("Package");
chdir("Package");
table=fopen("table","w+b");
table2=fopen("table2","w+b");
for (i=0;i<0x14B9;i++)
     {
        //dim=ordin[i+1]-ordin[i];
        fseek(bin,ordin[i],SEEK_SET);
        times=realdimord[i]/10485760;
        resto=realdimord[i]%10485760;
        sprintf(stringa, "%d%d%d%d.dat ",n0,n1,n2,n3);
        sprintf(temp, "%d%d%d%d.dat ",n0,n1,n2,n3);
        //ext=fopen(stringa,"r+b");
        fread(head,0x10,1,bin);
        
        for (q=0;q<tothead;q++)
        {
            if (memcmp(head,headers[q],lenhead[q])==0)
            {
               stringa[4]=0;
               sprintf(stringa,"%s%s",stringa,extension[q]);
               }
        }                                        
        
        /*if (strncmp(stringa,temp,8)==0)
        {
        fprintf(log,"%s   [0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x]\n", head,head[0],head[1],head[2],head[3],head[4],head[5],head[6],head[7],head[8],head[9],head[10],head[11],head[12],head[13],head[14],head[15]);
        }*/
        
        //fclose(ext);
        //system("pause");
        fseek(bin,-0x10,SEEK_CUR);
        ext=fopen(stringa,"w+b");
        printf("\rExtracting %s",stringa);
        fprintf(table2,"%s",stringa);
        for (t=0;t<0x14B9;t++)
     {
        if (pointer[t]==ordin[i])
        {
          fprintf(table,"%s%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",stringa,shit[t][0],shit[t][1],shit[t][2],shit[t][3],shit[t][4],shit[t][5],shit[t][6],shit[t][7],shit[t][8],shit[t][9],shit[t][10],shit[t][11],shit[t][12],shit[t][13],shit[t][14],shit[t][15]);
          }
          }                           
        for (j=0;j<times;j++)
        {
            fread(buffer,10485760,1,bin);              
            fwrite(buffer,10485760,1,ext);          
        }              
        if (resto > 0)
        {
            fread(buffer,resto,1,bin);              
            fwrite(buffer,resto,1,ext);     
        }
        
        //system("pause");
        fclose(ext);
        //rest=0;
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
     }
fclose(table);
table=fopen("table","r+b");
for (t=0;t<0x14B9;t++)
     {
       fread(temptable[t],0x19,1,table);
       }
rewind(table);
fseek(table,9,SEEK_SET);
for (t=0;t<0x14B9;t++)
     {                      
        fread(&tableorder[t],4,1,table);                    
        fseek(table,0x15,SEEK_CUR);
        
        }
//inizio ordinamenteo table
for (i=0; i<0x14B9; i++) 
         {
    app=tableorder[i];
    c=0;
    for (j=0; j<0x14B9; j++) 
         {
              if (app>tableorder[j])
              {
                c++;
                }
                
                }   
                realtableorder[c]=app;              
                
                realtable[c][0]=temptable[i][0];
                realtable[c][1]=temptable[i][1];
                realtable[c][2]=temptable[i][2];
                realtable[c][3]=temptable[i][3];
                realtable[c][4]=temptable[i][4];
                realtable[c][5]=temptable[i][5];
                realtable[c][6]=temptable[i][6];
                realtable[c][7]=temptable[i][7];
                realtable[c][8]=temptable[i][8];
                realtable[c][9]=temptable[i][9];
                realtable[c][10]=temptable[i][10];
                realtable[c][11]=temptable[i][11];
                realtable[c][12]=temptable[i][12];
                realtable[c][13]=temptable[i][13];
                realtable[c][14]=temptable[i][14];
                realtable[c][15]=temptable[i][15];
                realtable[c][16]=temptable[i][16];
                realtable[c][17]=temptable[i][17];
                realtable[c][18]=temptable[i][18];
                realtable[c][19]=temptable[i][19];
                realtable[c][20]=temptable[i][20];
                realtable[c][21]=temptable[i][21];
                realtable[c][22]=temptable[i][22];
                realtable[c][23]=temptable[i][23];
                realtable[c][24]=temptable[i][24];
                }   
//fine ordinamento table
fclose(table);
table=fopen("table","w+b");
for (c=0;c<0x14B9;c++)
{   
fprintf(table,"%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",realtable[c][0],realtable[c][1],realtable[c][2],realtable[c][3],realtable[c][4],realtable[c][5],realtable[c][6],realtable[c][7],realtable[c][8],realtable[c][9],realtable[c][10],realtable[c][11],realtable[c][12],realtable[c][13],realtable[c][14],realtable[c][15],realtable[c][16],realtable[c][17],realtable[c][18],realtable[c][19],realtable[c][20],realtable[c][21],realtable[c][22],realtable[c][23],realtable[c][24]);
}
printf("\nExtraction Complete. Have Fun\n");
}   





                     
