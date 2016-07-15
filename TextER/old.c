#include <stdio.h>
#include <windows.h>
#include <math.h>

BYTE buffer[10485760];
int main(int argc, char *argv[])
{
      FILE *arch, *tm2, *Gim, *dat, *tmptm2, *log, *tm3, *tmptm3;
      unsigned long int i=0,length,numbers=0,tempz,dim,prova=0,archive,peso=0,pointer,inizio=0,end=0,gim[9999],tim2[9999],tim3[9999],f=0,g=0,r=0,tempoff,off=0x00;
      unsigned long int c,w,s,endfile,times,rest,tot,lunghezza,num,n0=0,n1=0,n2=0,n3=1;
      
      unsigned char  bytes,point1,point2,point3,point4,number,head[16];
      unsigned char temp[500],stringa[500],name[79],path[1000],nomefile[104];
       float pot=0,q;    
       if (argc < 4) printf("\nTextures Extractor/Reinserter v0.9 by Vash\n\n-> TextER [option] [file] [type]\n\nOPTION:\n\n-e file [extract the files]\n-c file [insert the textures extracted in the original file]\n\nTYPE:\n\n-tm [TIM2 & TIM3 (PS2)]\n-gim [GIM (psp)]\n\n");
    else {
    if (strstr(argv[0], argv[2])!=0)
    {
      printf("\nC'mon guy! You can't scan me....What the fuck!\n");                    
      return 0;
}

if (fopen(argv[2], "r+b")==NULL)
{
   printf("\nThe file is read only or is used by another application or it doesn't exist\n");                    
      return 0;
}    

if(strcmpi(argv[1], "-e")!=0 && strcmpi(argv[1], "-c")!=0)
{
   printf("\nTextures Extractor/Reinserter v0.9 by Vash\n\n-> TextER [option] [file] [type]\n\nOPTION:\n\n-e file [extract the files]\n-c file [insert the textures extracted in the original file]\n\nTYPE:\n\n-tm [TIM2 & TIM3 (PS2)]\n-gim [GIM (psp)]\n\n");                    
      return 0;
}
if (strstr(argv[2], "\\")!=0)
{
   printf("\nThe file MUST be in the same directory of the program\n");                    
      return 0;
} 
                
    if(strcmpi(argv[1], "-e")==0)
    {
         arch=fopen(argv[2], "r+b");       
              //inizio ricerca header "TIM2" e "TIM3"
              fseek(arch,0x00,SEEK_END);
              endfile=ftell(arch);
              
              if (endfile==-1)
              {
                   printf("Sorry dude, this file is too big for now...\n");
                   return 0;
                   }
                   fclose(arch);
         
         
         
          if(strcmpi(argv[3], "-tm")==0 || strcmpi(argv[argc-1], "-tm")==0)   
          {   
              arch=fopen(argv[2], "r+b");       
              printf("\nLooking for TIM2 and TIM3\n");
              fseek(arch,0x00,SEEK_END);
              endfile=ftell(arch);
              
                   
              rewind(arch);
              times=endfile/(10485760);
                                          
                      for (c=0;c<times;c++)
                      {
                      fread(buffer,10485760,1,arch);
                      for (s=0;s<10485760;s++)
                      {
                         if (buffer[s]==0x54 && buffer[s+1]==0x49 && buffer[s+2]==0x4D && buffer[s+3]==0x32 && buffer[s+8]==0x00 && buffer[s+9]==0x00 && buffer[s+0x0a]==0x00 && buffer[s+0x0B]==0x00) 
                          {
                             tim2[f]=s+(10485760*c);                
                             //printf("TIM2 trovata a 0x%x\n",tim2[f-1]);
                             f++;
                             tempoff=ftell(arch);
                             fseek(arch,tim2[f-1]+0x10,SEEK_SET);
                             point1=fgetc(arch);
                             point2=fgetc(arch);
                             point3=fgetc(arch);
                             point4=fgetc(arch);
                             length=((point4*16777216+point3*65536+point2*256)+point1);
                            // printf("LENGTH= %x\n",length);
                             if ((length+tim2[f-1])>endfile)
                             {
                               f=f-1;
                               }//else{
                                    // printf("TIM2 trovata a 0x%x\n",tim2[f-1]);}
                               fseek(arch,tempoff,SEEK_SET);                              
                             }
                          if (buffer[s]==0x54 && buffer[s+1]==0x49 && buffer[s+2]==0x4D && buffer[s+3]==0x33  && buffer[s+8]==0x00 && buffer[s+9]==0x00 && buffer[s+0x0A]==0x00 && buffer[s+0x0B]==0x00) 
                          {
                             tim3[g]=s+(10485760*c);                
                             //printf("TIM3 trovata a 0x%x\n",tim3[g]);
                             g++;
                             tempoff=ftell(arch);
                             fseek(arch,tim3[g-1]+0x10,SEEK_SET);
                             point1=fgetc(arch);
                             point2=fgetc(arch);
                             point3=fgetc(arch);
                             point4=fgetc(arch);
                             length=((point4*16777216+point3*65536+point2*256)+point1);
                            // printf("LENGTH= %x\n",length);
                             if ((length+tim3[g-1])>endfile)
                             {
                               g=g-1;
                               }
                               fseek(arch,tempoff,SEEK_SET);
                             }
                          /*if (c>0)
                          {
                          fseek(arch,ftell(arch)-0x30,SEEK_SET);
                          }*/
                          
                          }
                          
                              
                      }
                      rest=dim%10485760;
                      if(rest)
                      {
                      fread(buffer,rest,1,arch);
                      for (s=0;s<rest-3;s++)
                      {
                         if (buffer[s]==0x54 && buffer[s+1]==0x49 && buffer[s+2]==0x4D && buffer[s+3]==0x32  && buffer[s+8]==0x00 && buffer[s+9]==0x00 && buffer[s+0x0A]==0x00 && buffer[s+0x0B]==0x00) 
                          {
                             tim2[f]=s+(10485760*c);                
                             //printf("TIM2 trovata a 0x%x\n",tim2[f]);
                             f++;
                             tempoff=ftell(arch);
                             fseek(arch,tim2[f-1]+0x10,SEEK_SET);
                             point1=fgetc(arch);
                             point2=fgetc(arch);
                             point3=fgetc(arch);
                             point4=fgetc(arch);
                             length=((point4*16777216+point3*65536+point2*256)+point1);
                             //printf("LENGTH= %x\n",length);
                             if ((length+tim2[f-1])>endfile)
                             {
                               f=f-1;
                               }//else{
                                     //printf("TIM2 trovata a 0x%x\n",tim2[f-1]);}
                               fseek(arch,tempoff,SEEK_SET);   
                             }
                          if (buffer[s]==0x54 && buffer[s+1]==0x49 && buffer[s+2]==0x4D && buffer[s+3]==0x33 && buffer[s+8]==0x00 && buffer[s+9]==0x00 && buffer[s+0x0A]==0x00 && buffer[s+0x0B]==0x00) 
                          {
                             tim3[g]=s+(10485760*c);                
                            // printf("TIM3 trovata a 0x%x\n",tim3[g]);
                             g++;
                             tempoff=ftell(arch);
                             fseek(arch,tim3[g-1]+0x10,SEEK_SET);
                             point1=fgetc(arch);
                             point2=fgetc(arch);
                             point3=fgetc(arch);
                             point4=fgetc(arch);
                             length=((point4*16777216+point3*65536+point2*256)+point1);
                             //printf("LENGTH= %x\n",length);
                             if ((length+tim3[g-1])>endfile)
                             {
                               g=g-1;
                               }
                               fseek(arch,tempoff,SEEK_SET);
                             }   
                             
                             }
                      
                      
                      }
              
              
              
              
              //system("pause");
              
              
              if (f==0 && g==0)
              {
                       printf("Sorry pal. No TIM2 nor TIM3 files has been detected\n\n");
                       //return 0;
                       }else{
                             
               printf("Founded %d TIM2 and %d TIM3 in %s.\n\nExtraction in progress\n\n",f,g,argv[2]);              
              //fine ricerca header
              mkdir("TIM2");
              chdir("TIM2");
              mkdir(argv[2]);
              chdir(argv[2]);
              log=fopen("spec.log", "w+b");
              fprintf(log,"%d\n",f);
              //printf("%s",argv[2]);
              //estrazione TIM2
              
              
              for (num=0;num<f;num++)
              {
              sprintf(stringa, "%d%d%d%d.tm2",n0,n1,n2,n3);
              tm2=fopen(stringa,"w+b");
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
              //controllo se il file è un archivio di TIM
              fseek(arch,tim2[num]+6,SEEK_SET);
              number=fgetc(arch);
              
              if (number==0x01)
              {       
              fseek(arch,tim2[num],SEEK_SET);
              fseek(arch,0x10,SEEK_CUR);
              point1=fgetc(arch);
              point2=fgetc(arch);
              point3=fgetc(arch);
              point4=fgetc(arch);
              length=((point4*16777216+point3*65536+point2*256)+point1);
              fprintf(log,"%s:%d:%d:0\n", stringa,tim2[num],length+0x10);
              fseek(arch,tim2[num],SEEK_SET);
              for (c=0;c<length+0x10;c=c+0x01)
          {
              fputc(fgetc(arch),tm2);
              }
              fclose(tm2);
              }
              
              if (number>0x01)
              {
               fseek(arch,tim2[num],SEEK_SET);
               fseek(arch,0x10,SEEK_CUR);
               for(i=0;i<number;i++)
               {
               point1=fgetc(arch);
               point2=fgetc(arch);
               point3=fgetc(arch);
               point4=fgetc(arch);
               pointer=((point4*16777216+point3*65536+point2*256)+point1);
               //printf("pointer %d su %d: %x\n",i,number,pointer);
               fseek(arch,pointer-4,SEEK_CUR);
               }
               length=ftell(arch)-tim2[num];
               fprintf(log,"%s:%d:%d:1\n", stringa,tim2[num],length+0x10);
               //printf("lunghezza: %x",length);
               fseek(arch,tim2[num],SEEK_SET);
               for (c=0;c<length;c=c+0x01)
              {
               fputc(fgetc(arch),tm2);
                }
               fclose(tm2);
                            
                              
                              
                //Inizio Estrazione TIM2 da archivio di TIM2              
                tm2=fopen(stringa,"r+b");
                lunghezza=strlen(stringa);
                stringa[lunghezza-4]=0;
                mkdir(stringa);
                chdir(stringa);                   
                dat=fopen("n.dat","w+b");
                fputc(number,dat);
                fclose(dat);
                rewind(tm2);
                for (i=0;i<16;i++)
                {
                  head[i]=fgetc(tm2); //header saved inside the array
                  
                                      }
                                      head[6]=0x01;
      for (i=0x00;i<number;i=i+0x01)
      {
          point1=fgetc(tm2);
          point2=fgetc(tm2);
          point3=fgetc(tm2);
          point4=fgetc(tm2);
          length=((point4*16777216+point3*65536+point2*256)+point1);
          sprintf(stringa, "%x.tm2", i);
          //printf("%s",stringa);
          tmptm2=fopen(stringa,"w+b");
          for (c=0;c<16;c++)
          {
              fputc(head[c],tmptm2);
          }
          fseek(tm2,ftell(tm2)-4,SEEK_SET);
          for (c=0;c<length;c=c+0x01)
          {
              fputc(fgetc(tm2),tmptm2);
              }
              fclose(tmptm2);
              }
              chdir("..");
              }
              }
              chdir("..");
              chdir("..");
              n0=0;
              n1=0;
              n2=0;
              n3=1;
              //estrazione TIM3
              
              mkdir("TIM3");
              chdir("TIM3");
              mkdir(argv[2]);
              chdir(argv[2]);
              log=fopen("spec.log", "w+b");
              fprintf(log,"%d\n",g);
              //printf("%s",argv[2]);
              
              
              
              for (num=0;num<g;num++)
              {
              sprintf(stringa, "%d%d%d%d.tm3",n0,n1,n2,n3);
              tm3=fopen(stringa,"w+b");
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
              //controllo se il file è un archivio di TIM
              fseek(arch,tim3[num]+6,SEEK_SET);
              number=fgetc(arch);
              
              if (number==0x01)
              {       
              fseek(arch,tim3[num],SEEK_SET);
              fseek(arch,0x10,SEEK_CUR);
              point1=fgetc(arch);
              point2=fgetc(arch);
              point3=fgetc(arch);
              point4=fgetc(arch);
              length=((point4*16777216+point3*65536+point2*256)+point1);
              fprintf(log,"%s:%d:%d:0\n", stringa,tim3[num],length+0x10);
              fseek(arch,tim3[num],SEEK_SET);
              for (c=0;c<length+0x10;c=c+0x01)
          {
              fputc(fgetc(arch),tm3);
              }
              fclose(tm3);
              }
              
              if (number>0x01)
              {
               fseek(arch,tim3[num],SEEK_SET);
               fseek(arch,0x10,SEEK_CUR);
               for(i=0;i<number;i++)
               {
               point1=fgetc(arch);
               point2=fgetc(arch);
               point3=fgetc(arch);
               point4=fgetc(arch);
               pointer=((point4*16777216+point3*65536+point2*256)+point1);
               //printf("pointer %d su %d: %x\n",i,number,pointer);
               fseek(arch,pointer-4,SEEK_CUR);
               }
               length=ftell(arch)-tim3[num];
               fprintf(log,"%s:%d:%d:1\n", stringa,tim3[num],length+0x10);
               //printf("lunghezza: %x",length);
               fseek(arch,tim3[num],SEEK_SET);
               for (c=0;c<length;c=c+0x01)
              {
               fputc(fgetc(arch),tm3);
                }
               fclose(tm3);
                            
                              
                              
                //Inizio Estrazione TIM3 da archivio di TIM3              
                tm3=fopen(stringa,"r+b");
                lunghezza=strlen(stringa);
                stringa[lunghezza-4]=0;
                mkdir(stringa);
                chdir(stringa);                   
                dat=fopen("n.dat","w+b");
                fputc(number,dat);
                fclose(dat);
                rewind(tm3);
                for (i=0;i<16;i++)
                {
                  head[i]=fgetc(tm3); //header saved inside the array
                  
                                      }
                                      head[6]=0x01;
      for (i=0x00;i<number;i=i+0x01)
      {
          point1=fgetc(tm3);
          point2=fgetc(tm3);
          point3=fgetc(tm3);
          point4=fgetc(tm3);
          length=((point4*16777216+point3*65536+point2*256)+point1);
          sprintf(stringa, "%x.tm3", i);
          //printf("%s",stringa);
          tmptm3=fopen(stringa,"w+b");
          for (c=0;c<16;c++)
          {
              fputc(head[c],tmptm3);
          }
          fseek(tm3,ftell(tm3)-4,SEEK_SET);
          for (c=0;c<length;c=c+0x01)
          {
              fputc(fgetc(tm3),tmptm3);
              }
              fclose(tmptm3);
              }
              chdir("..");
              }
              
              }
              
              fclose(arch);
              //fclose(log);
              n0=0;
              n1=0;
              n2=0;
              n3=1;
              chdir("..");
              chdir("..");
              }
              
              }
              
             // printf("%d",argc);
              if(strcmpi(argv[3], "-gim")==0 || strcmpi(argv[argc-1], "-gim")==0)   
          {   
              
              arch=fopen(argv[2], "r+b"); 
              //system("pause");      
              printf("Looking for GIM\n\n");
              fseek(arch,0x00,SEEK_END);
              endfile=ftell(arch);
              
                   
              rewind(arch);
              times=endfile/(10485760);
                                          
                      for (c=0;c<times;c++)
                      {
                      fread(buffer,10485760,1,arch);
                      for (s=0;s<10485760;s++)
                      {
                         if (buffer[s]==0x4D && buffer[s+1]==0x49 && buffer[s+2]==0x47 && buffer[s+3]==0x2E && buffer[s+4]==0x30 && buffer[s+5]==0x30 && buffer[s+6]==0x2E && buffer[s+7]==0x31 && buffer[s+8]==0x50 && buffer[s+9]==0x53 && buffer[s+0x0a]==0x50 && buffer[s+0x0B]==0x00 && buffer[s+0x0C]==0x00 && buffer[s+0x0D]==0x00 && buffer[s+0x0E]==0x00  && buffer[s+0x0F]==0x00) 
                          {
                             gim[r]=s+(10485760*c);                
                             //printf("GIM trovata a 0x%x\n",tim2[f-1]);
                             r++;
                             tempoff=ftell(arch);
                             fseek(arch,gim[r-1]+0x14,SEEK_SET);
                             point1=fgetc(arch);
                             point2=fgetc(arch);
                             point3=fgetc(arch);
                             point4=fgetc(arch);
                             length=((point4*16777216+point3*65536+point2*256)+point1);
                            // printf("LENGTH= %x\n",length);
                             if ((length+gim[r-1])>endfile)
                             {
                               r=r-1;
                               }//else{
                                    // printf("TIM2 trovata a 0x%x\n",tim2[f-1]);}
                               fseek(arch,tempoff,SEEK_SET);                              
                             }
                             //fseek(arch,-0x30,SEEK_CUR);
                          }
                          
                              
                      }
                      rest=dim%10485760;
                      if(rest)
                      {
                      fread(buffer,rest,1,arch);
                      for (s=0;s<rest-3;s++)
                      {
                        if (buffer[s]==0x4D && buffer[s+1]==0x49 && buffer[s+2]==0x47 && buffer[s+3]==0x2E && buffer[s+4]==0x30 && buffer[s+5]==0x30 && buffer[s+6]==0x2E && buffer[s+7]==0x31 && buffer[s+8]==0x50 && buffer[s+9]==0x53 && buffer[s+0x0a]==0x50 && buffer[s+0x0B]==0x00 && buffer[s+0x0C]==0x00 && buffer[s+0x0D]==0x00 && buffer[s+0x0E]==0x00  && buffer[s+0x0F]==0x00)   
                          {
                             gim[r]=s+(10485760*c);                
                             //printf("GIM trovata a 0x%x\n",gim[r]);
                             r++;
                             tempoff=ftell(arch);
                             fseek(arch,gim[r-1]+0x14,SEEK_SET);
                             point1=fgetc(arch);
                             point2=fgetc(arch);
                             point3=fgetc(arch);
                             point4=fgetc(arch);
                             length=((point4*16777216+point3*65536+point2*256)+point1);
                             //printf("LENGTH= %x\n",length);
                             if ((length+tim2[r-1])>endfile)
                             {
                               r=r-1;
                               }//else{
                                     //printf("TIM2 trovata a 0x%x\n",tim2[f-1]);}
                               fseek(arch,tempoff,SEEK_SET);   
                             }
                                                      
                             }
                      
                      
                      }
              
              
              if (r==0)
              {
                       printf("Sorry pal. No GIM has been detected\n\n");
                       //return 0;
                       }else{
              
              printf("Founded %d GIM in %s.\n\nExtraction in progress\n\n",r,argv[2]);              
              //fine ricerca header
              mkdir("GIM");
              chdir("GIM");
              mkdir(argv[2]);
              chdir(argv[2]);
              log=fopen("spec.log", "w+b");
              fprintf(log,"%d\n",r);
			  
			  for (num=0;num<r;num++)
              {
              sprintf(stringa, "%d%d%d%d.gim",n0,n1,n2,n3);
              Gim=fopen(stringa,"w+b");
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
              
			  
			  
			  fseek(arch,gim[num],SEEK_SET);
              fseek(arch,0x14,SEEK_CUR);
              point1=fgetc(arch);
              point2=fgetc(arch);
              point3=fgetc(arch);
              point4=fgetc(arch);
              length=((point4*16777216+point3*65536+point2*256)+point1);
              fprintf(log,"%s:%d:%d:0\n", stringa,gim[num],length);
              fseek(arch,gim[num],SEEK_SET);
              for (c=0;c<length;c=c+0x01)
          {
              fputc(fgetc(arch),Gim);
              }
              fclose(Gim);
              }
              }
              chdir("..");
              chdir("..");
              }
              
              //system("pause");
              }
              
              
              
             
              
              if(strcmpi(argv[1], "-c")==0)
              {
                  arch=fopen(argv[2],"r+b");
                  sprintf(stringa, "TIM2\\%s", argv[2]);
                  if (chdir(stringa)==-1)
                  {
                  printf("The file %s hasn't been extracted, or it's been renamed or something went wrong.\n\nBackup your progresses and extract it again (or try to find out why this message appeared)",argv[2]);
                  return(0);
                  }
                  chdir("..");
                  chdir("..");
                  sprintf(stringa, "TIM3\\%s", argv[2]);
                  if (chdir(stringa)==-1)
                  {
                   printf("The file %s hasn't been extracted, or it's been renamed or something went wrong.\n\nBackup your progresses and extract it again (or try to find out why this message appeared)",argv[2]);
                  return(0);
                  }
                  chdir("..");
                  chdir("..");
                  //TIM2
                  sprintf(stringa, "TIM2\\%s\\spec.log", argv[2]);
                  if (fopen (stringa,"r+b")==NULL)
                  {
                            printf("The file %s doesn't exist or it's in use by another program.\n",stringa);
                            return(0);
                            }
                            
                   log=fopen (stringa,"r+b");                     
                  while (bytes!=0x0A)  
                  {
                        bytes=fgetc(log);
                        pot++;
                        } 
                  fseek(log,ftell(log)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>0;q--)
                  {
                    bytes=fgetc(log)-0x30;
                    numbers=numbers+bytes*pow(10,q-0x01);
                    //printf("%d\n",numbers);
                    }
                   fseek(log,1,SEEK_CUR);
                  //  Recuperato numero di TIM2 presenti nel file
                  prova=0;
                  for (i=0;i<numbers;i++)
                  {
                   *stringa=0x00;
                   prova=0;
                   bytes=0x00;
                   inizio=0;
                   peso=0;
                   tempz=0;
                   while (prova!=1)
                   {
                      bytes=fgetc(log);
                      if (bytes==0x3A)
                      {
                          prova=1;
                          }else{
                   sprintf(stringa,"%s%c",stringa,bytes);
                   }}                
                   //printf("%s ",stringa);
                   //Recuperato nome del file
                   pot=0;
                   bytes=0;
                   while (bytes!=0x3A)  
                  {
                        bytes=fgetc(log);
                        pot++;
                        } 
                  fseek(log,ftell(log)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>1;q--)
                  {
                    bytes=fgetc(log)-0x30;
                    
                    tempz=bytes;
                    for(w=0;w<q-1;w++)
                    {
                    tempz=tempz*10;
                    
                    }
                    inizio=inizio+tempz;
                    
                    }
                    bytes=fgetc(log)-0x30;
                    inizio=inizio+bytes;
                    //printf("%d ",inizio);
                    //Recuperato Offset iniziale del file
                    fseek(log,1,SEEK_CUR);
                    pot=0;
                   bytes=0;
                   while (bytes!=0x3A)  
                  {
                        bytes=fgetc(log);
                        pot++;
                        } 
                  fseek(log,ftell(log)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>0;q--)
                  {
                    bytes=fgetc(log)-0x30;
                    
                    tempz=bytes;
                    for(w=0;w<q-1;w++)
                    {
                    tempz=tempz*10;
                    //printf("%d\n",tempz);
                    }
                    peso=peso+tempz;
                    //printf("%d\n",peso);
                    }
                    //bytes=fgetc(log)-0x30;
                    //peso=peso+bytes;
                    //printf("%d ",peso);
                    fseek(log,1,SEEK_CUR);
                    archive=fgetc(log)-0x30;
                    //printf("%d\n",archive);
                    fseek(log,1,SEEK_CUR);
                   
                   if (archive==0)
                   {
                      fseek(arch,inizio,SEEK_SET);
                      
                      chdir("TIM2");
                      chdir(argv[2]);
                                      
                      
                      tm2=fopen(stringa,"r+b");
                      fseek(tm2,0x00,SEEK_END);
                      dim=ftell(tm2);
                      if (dim!=peso)
                      {
                      
                      printf("\n%s: This tool is not some kind of magic wand! The new TIM2 must be of the same size of the original\n\n",stringa);                    
                      chdir("..");
                      chdir("..");
                      //fclose(tm2);
                      }else{
                      rewind(tm2);
                      times=dim/(131072);
                      //system("pause");
                      
                      for (c=0;c<times;c++)
                      {
                      fread(buffer,131072,1,tm2);
                      fwrite(buffer,131072,1,arch);
                      }
                      rest=dim%131072;
                      if(rest)
                      {
                      fread(buffer,rest,1,tm2);

                      fwrite(buffer,rest,1,arch);
                      }
                      printf("TIM2 reinserted successfully\n");
                      chdir("..");
                      chdir("..");
                      }
                      //system("pause");
                      }
                      if (archive==1)
                   {
                      fseek(arch,inizio,SEEK_SET);
                      
                      chdir("TIM2");
                      chdir(argv[2]);
                      lunghezza=strlen(stringa);
                      strncpy(nomefile, stringa, lunghezza-4);
                      sprintf(temp, "%s\\n.dat",nomefile);                
                  //printf("%s\n",temp);
                  //system("pause");
                  
                  dat=fopen(temp,"r+b");
                  number=fgetc(dat);
                  //system("pause");
                  sprintf(name, "%s\\0.tm2", nomefile);
                  tmptm2=fopen(name,"r+b");            
                  //sprintf(stringa, "%s.tm2", argv[2]);
                  //printf("\n%s\n%s\n\n",stringa,name);
                  tm2=fopen(stringa,"r+b");
                  //system("pause");
                  //fseek(tmptm2,0x00,SEEK_SET);
                  for (c=0;c<16;c++)
              {
                  fputc(fgetc(tmptm2),tm2); //header saved inside the array
                  
                                      }
                                      //system("pause");
                                      fseek(tm2,0x06,SEEK_SET);
                                      fputc(number,tm2);
                                      fseek(tm2,0x10,SEEK_SET);
                                      fclose(tmptm2); 
                                      //system("pause");
                                      for (c=0;c<number;c++)
                                      {
                                          sprintf(name, "%s\\%x.tm2", nomefile,c);
                                          tmptm2=fopen(name,"r+b");             
                                          //printf("%s\n",name);
                                          fseek(tmptm2,0x00,SEEK_END);
                                          length=ftell(tmptm2)-0x10;
                                          //printf("%x",length);
                                          fseek(tmptm2,0x10,SEEK_SET);
                                          for (c=0;c<length;c++)
                                          {
                                          fputc(fgetc(tmptm2),tm2);
                                          }
                                          }                
                      //system("pause");
                      //tm2=fopen(stringa,"r+b");
                      fseek(tm2,0x00,SEEK_END);
                      dim=ftell(tm2);
                      rewind(tm2);
                      if (dim!=peso)
                      {
                      
                      printf("\n%s: This tool is not some kind of magic wand! The new TIM2 must be of the same size of the original\n\n",stringa);                    
                      chdir("..");
                      chdir("..");
                      //fclose(tm2);
                      }else{
                      rewind(tm2);
                      times=dim/(131072);
                      //system("pause");
                      
                      for (c=0;c<times;c++)
                      {
                      fread(buffer,131072,1,tm2);
                      fwrite(buffer,131072,1,arch);
                      }
                      rest=dim%131072;
                      if(rest)
                      {
                      fread(buffer,rest,1,tm2);

                      fwrite(buffer,rest,1,arch);
                      }
                      printf("TIM2 reinserted successfully\n");
                      chdir("..");
                      chdir("..");
                      }}
                      //system("pause");
                      }
                      
                      
                      fclose(log);
                      //fclose(tm2);
                      
                      *stringa=0x00;
                      *temp=0x00;
                      *name=0x00;
                      *nomefile=0x00;
                      prova=0;
                      bytes=0x00;
                      inizio=0;
                      peso=0;
                      tempz=0;
                      numbers=0;
                      pot=0;
                      printf("\n");
                   //TIM3
                   sprintf(stringa, "TIM3\\%s\\spec.log", argv[2]);
                  if (fopen (stringa,"r+b")==NULL)
                  {
                            printf("The file %s doesn't exist or it's in use by another program.\n",stringa);
                            return(0);
                            }
                            
                   log=fopen (stringa,"r+b");                     
                  while (bytes!=0x0A)  
                  {
                        bytes=fgetc(log);
                        pot++;
                        } 
                        
                  fseek(log,ftell(log)-pot,SEEK_SET);  
                  pot=pot-1;
                 // system("pause");
                  for (q=pot;q>0;q--)
                  {
                    bytes=fgetc(log)-0x30;
                    numbers=numbers+bytes*pow(10,q-0x01);
                    //printf("%d\n",numbers);
                    }
                    //printf("%d\n",numbers);
                   fseek(log,1,SEEK_CUR);
                   
                  //  Recuperato numero di TIM3 presenti nel file
                  prova=0;
                  for (i=0;i<numbers;i++)
                  {
                   *stringa=0x00;
                   prova=0;
                   bytes=0x00;
                   inizio=0;
                   peso=0;
                   tempz=0;
                   while (prova!=1)
                   {
                      bytes=fgetc(log);
                      if (bytes==0x3A)
                      {
                          prova=1;
                          }else{
                   sprintf(stringa,"%s%c",stringa,bytes);
                   }}                
                   //printf("%s ",stringa);
                   //Recuperato nome del file
                   pot=0;
                   bytes=0;
                   while (bytes!=0x3A)  
                  {
                        bytes=fgetc(log);
                        pot++;
                        } 
                  fseek(log,ftell(log)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>1;q--)
                  {
                    bytes=fgetc(log)-0x30;
                    
                    tempz=bytes;
                    for(w=0;w<q-1;w++)
                    {
                    tempz=tempz*10;
                    
                    }
                    inizio=inizio+tempz;
                    
                    }
                    bytes=fgetc(log)-0x30;
                    inizio=inizio+bytes;
                    //printf("%d ",inizio);
                    //Recuperato Offset iniziale del file
                    fseek(log,1,SEEK_CUR);
                    pot=0;
                   bytes=0;
                   while (bytes!=0x3A)  
                  {
                        bytes=fgetc(log);
                        pot++;
                        } 
                  fseek(log,ftell(log)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>0;q--)
                  {
                    bytes=fgetc(log)-0x30;
                    
                    tempz=bytes;
                    for(w=0;w<q-1;w++)
                    {
                    tempz=tempz*10;
                    //printf("%d\n",tempz);
                    }
                    peso=peso+tempz;
                    //printf("%d\n",peso);
                    }
                    //bytes=fgetc(log)-0x30;
                    //peso=peso+bytes;
                    //printf("%d ",peso);
                    fseek(log,1,SEEK_CUR);
                    archive=fgetc(log)-0x30;
                    //printf("%d\n",archive);
                    fseek(log,1,SEEK_CUR);
                   
                   if (archive==0)
                   {
                      fseek(arch,inizio,SEEK_SET);
                      
                      chdir("TIM3");
                      chdir(argv[2]);
                                      
                      
                      tm3=fopen(stringa,"r+b");
                      fseek(tm3,0x00,SEEK_END);
                      dim=ftell(tm3);
                      if (dim!=peso)
                      {
                                   
                      printf("\n%s: This tool is not some kind of magic wand! The new TIM3 must be of the same size of the original\n\n",stringa);                    
                      chdir("..");
                      chdir("..");
                      }else{
                      rewind(tm3);
                      times=dim/(131072);
                      //system("pause");
                      
                      for (c=0;c<times;c++)
                      {
                      fread(buffer,131072,1,tm3);
                      fwrite(buffer,131072,1,arch);
                      }
                      rest=dim%131072;
                      if(rest)
                      {
                      fread(buffer,rest,1,tm3);

                      fwrite(buffer,rest,1,arch);
                      }
                      printf("TIM3 reinserted successfully\n");
                      chdir("..");
                      chdir("..");
                      }}
                      
                      if (archive==1)
                   {
                      fseek(arch,inizio,SEEK_SET);
                      
                      chdir("TIM3");
                      chdir(argv[2]);
                      lunghezza=strlen(stringa);
                      strncpy(nomefile, stringa, lunghezza-4);
                      sprintf(temp, "%s\\n.dat",nomefile);                
                  //printf("%s\n",temp);
                  //system("pause");
                  
                  dat=fopen(temp,"r+b");
                  number=fgetc(dat);
                  //system("pause");
                  sprintf(name, "%s\\0.tm3", nomefile);
                  tmptm3=fopen(name,"r+b");            
                  //sprintf(stringa, "%s.tm3", argv[2]);
                  //printf("\n%s\n%s\n\n",stringa,name);
                  tm3=fopen(stringa,"r+b");
                  //system("pause");
                  //fseek(tmptm3,0x00,SEEK_SET);
                  for (c=0;c<16;c++)
              {
                  fputc(fgetc(tmptm3),tm3); //header saved inside the array
                  
                                      }
                                      //system("pause");
                                      fseek(tm3,0x06,SEEK_SET);
                                      fputc(number,tm3);
                                      fseek(tm3,0x10,SEEK_SET);
                                      fclose(tmptm3); 
                                      //system("pause");
                                      for (c=0;c<number;c++)
                                      {
                                          sprintf(name, "%s\\%x.tm3", nomefile,c);
                                          tmptm3=fopen(name,"r+b");             
                                          //printf("%s\n",name);
                                          fseek(tmptm3,0x00,SEEK_END);
                                          length=ftell(tmptm3)-0x10;
                                          //printf("%x",length);
                                          fseek(tmptm3,0x10,SEEK_SET);
                                          for (c=0;c<length;c++)
                                          {
                                          fputc(fgetc(tmptm3),tm3);
                                          }
                                          }                
                      //system("pause");
                      //tm3=fopen(stringa,"r+b");
                      fseek(tm3,0x00,SEEK_END);
                      dim=ftell(tm3);
                      if (dim!=peso)
                      {
                      
                      printf("\n%s: This tool is not some kind of magic wand! The new TIM3 must be of the same size of the original\n\n",stringa);                    
                      chdir("..");
                      chdir("..");
                      }else{
                      rewind(tm3);
                      times=dim/(131072);
                      //system("pause");
                      
                      for (c=0;c<times;c++)
                      {
                      fread(buffer,131072,1,tm3);
                      fwrite(buffer,131072,1,arch);
                      }
                      rest=dim%131072;
                      if(rest)
                      {
                      fread(buffer,rest,1,tm3);

                      fwrite(buffer,rest,1,arch);
                      }
                      printf("TIM3 reinserted successfully\n");
                      chdir("..");
                      chdir("..");
                      }}
                      
                   }
                       
                  
                                  
                                  
                                  
                                  
                                  
                                  
                                  
                                  
                                  
                                  }
              
              }
              
              
          
          
          
}
      
