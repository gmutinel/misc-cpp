
void tmsearch(void)
{
    fseeko64(arch,0x00,SEEK_END);
              endfile=ftello64(arch);
              
                   
              rewind(arch);
              times=endfile/(10485760);
                                          
                      for (c=0;c<times;c++)
                      {
                      fread(buffer,10485760,1,arch);
                      for (s=0;s<10485760;s++)
                      {
                         if (buffer[s]==0x54 && buffer[s+1]==0x49 && buffer[s+2]==0x4D && buffer[s+3]==0x32 && buffer[s+0x04]==0x04 && buffer[s+0x05]==0x01) 
                          {
                             tim2[f]=s+(10485760*c);                
                             
                             f++;
                             tempoff=ftello64(arch);
                             fseeko64(arch,tim2[f-1]+0x80,SEEK_SET);
                             point1=fgetc(arch);
                             point2=fgetc(arch);
                             point3=fgetc(arch);
                             point4=fgetc(arch);
                             length=((point4*16777216+point3*65536+point2*256)+point1);
                            
                             if ((length+tim2[f-1])>endfile)
                             {
                               f=f-1;
                               }
                               fseeko64(arch,tempoff,SEEK_SET);                              
                             }
                          if (buffer[s]==0x54 && buffer[s+1]==0x49 && buffer[s+2]==0x4D && buffer[s+3]==0x33 && buffer[s+0x04]==0x04 && buffer[s+0x05]==0x01) 
                          {
                             tim3[g]=s+(10485760*c);                
                            
                             g++;
                             tempoff=ftello64(arch);
                             fseeko64(arch,tim3[g-1]+0x80,SEEK_SET);
                             point1=fgetc(arch);
                             point2=fgetc(arch);
                             point3=fgetc(arch);
                             point4=fgetc(arch);
                             length=((point4*16777216+point3*65536+point2*256)+point1);
                            
                             if ((length+tim3[g-1])>endfile)
                             {
                               g=g-1;
                               }
                               fseeko64(arch,tempoff,SEEK_SET);
                             }
                          
                          
                          }
                          
                              
                      }
                      rest=dim%10485760;
                      if(rest)
                      {
                      fread(buffer,rest,1,arch);
                      for (s=0;s<rest-3;s++)
                      {
                         if (buffer[s]==0x54 && buffer[s+1]==0x49 && buffer[s+2]==0x4D && buffer[s+3]==0x32 && buffer[s+0x04]==0x04 && buffer[s+0x05]==0x01) 
                          {
                             tim2[f]=s+(10485760*c);                
                             
                             f++;
                             tempoff=ftello64(arch);
                             fseeko64(arch,tim2[f-1]+0x80,SEEK_SET);
                             point1=fgetc(arch);
                             point2=fgetc(arch);
                             point3=fgetc(arch);
                             point4=fgetc(arch);
                             length=((point4*16777216+point3*65536+point2*256)+point1);
                             
                             if ((length+tim2[f-1])>endfile)
                             {
                               f=f-1;
                               }
                               fseeko64(arch,tempoff,SEEK_SET);   
                             }
                          if (buffer[s]==0x54 && buffer[s+1]==0x49 && buffer[s+2]==0x4D && buffer[s+3]==0x33 && buffer[s+0x04]==0x04 && buffer[s+0x05]==0x01) 
                          {
                             tim3[g]=s+(10485760*c);                
                            
                             g++;
                             tempoff=ftell(arch);
                             fseeko64(arch,tim3[g-1]+0x80,SEEK_SET);
                             point1=fgetc(arch);
                             point2=fgetc(arch);
                             point3=fgetc(arch);
                             point4=fgetc(arch);
                             length=((point4*16777216+point3*65536+point2*256)+point1);
                             
                             if ((length+tim3[g-1])>endfile)
                             {
                               g=g-1;
                               }
                               fseeko64(arch,tempoff,SEEK_SET);
                             }   
                             
                             }
                             }}
                      
                      


int tmextr(char *nuovoargv2)
{
    if (f==0 && g==0)
              {
                       printf("Sorry pal. No TIM2 nor TIM3 files has been detected\n\n");
                       //return 0;
                       }else{
                             
               printf("Founded %d TIM2 and %d TIM3 in %s.\n\nExtraction in progress\n\n",f,g,nuovoargv2);              
              //fine ricerca header
              mkdir("TIM2");
              chdir("TIM2");
              mkdir(nuovoargv2);
              chdir(nuovoargv2);
              lolg=fopen("spec.log", "w+b");
              fprintf(lolg,"%d\n",f);
              //printf("%s",argv[2]);
              //estrazione TIM2
              
              
              for (num=0;num<f;num++)
              {
              printf("\rTIM2: [%d%%]",((num+1)*100)/f);
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
              fseeko64(arch,tim2[num]+6,SEEK_SET);
              number=fgetc(arch);
              
              if (number==0x01)
              {       
              fseeko64(arch,tim2[num],SEEK_SET);
              fseeko64(arch,0x80,SEEK_CUR);
              point1=fgetc(arch);
              point2=fgetc(arch);
              point3=fgetc(arch);
              point4=fgetc(arch);
              length=((point4*16777216+point3*65536+point2*256)+point1);
              fprintf(lolg,"%s:%u:%d:0\n", stringa,tim2[num],length+0x80);
              fseeko64(arch,tim2[num],SEEK_SET);
              fread(buffer,0x10,1,arch);
              fwrite(buffer,0x10,1,tm2);
              fseeko64(arch,0x70,SEEK_CUR);
              fread(buffer,length,1,arch);
              fwrite(buffer,length,1,tm2);
              /*for (c=0;c<length+0x80;c=c+0x01)
          {
              fputc(fgetc(arch),tm2);
              }*/
              fclose(tm2);
              }
              
              if (number>0x01)
              {
               fseeko64(arch,tim2[num],SEEK_SET);
               fseeko64(arch,0x80,SEEK_CUR);
               for(i=0;i<number;i++)
               {
               point1=fgetc(arch);
               point2=fgetc(arch);
               point3=fgetc(arch);
               point4=fgetc(arch);
               pointer=((point4*16777216+point3*65536+point2*256)+point1);
               //printf("pointer %d su %d: %x\n",i,number,pointer);
               fseeko64(arch,pointer-4,SEEK_CUR);
               }
               length=ftell(arch)-tim2[num];
               fprintf(lolg,"%s:%u:%d:1\n", stringa,tim2[num],length+0x80);
               //printf("lunghezza: %x",length);
               fseeko64(arch,tim2[num],SEEK_SET);
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
              mkdir(nuovoargv2);
              chdir(nuovoargv2);
              lolg=fopen("spec.log", "w+b");
              fprintf(lolg,"%d\n",g);
              printf("\n");
              
              
              
              for (num=0;num<g;num++)
              {
              printf("\rTIM3: [%d%%]",((num+1)*100)/g);
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
              fseeko64(arch,tim3[num]+6,SEEK_SET);
              number=fgetc(arch);
              
              if (number==0x01)
              {       
              fseeko64(arch,tim3[num],SEEK_SET);
              fseeko64(arch,0x80,SEEK_CUR);
              point1=fgetc(arch);
              point2=fgetc(arch);
              point3=fgetc(arch);
              point4=fgetc(arch);
              length=((point4*16777216+point3*65536+point2*256)+point1);
              fprintf(lolg,"%s:%u:%d:0\n", stringa,tim3[num],length+0x80);
              fseeko64(arch,tim3[num],SEEK_SET);
              for (c=0;c<length+0x80;c=c+0x01)
          {
              fputc(fgetc(arch),tm3);
              }
              fclose(tm3);
              }
              
              if (number>0x01)
              {
               fseeko64(arch,tim3[num],SEEK_SET);
               fseeko64(arch,0x80,SEEK_CUR);
               for(i=0;i<number;i++)
               {
               point1=fgetc(arch);
               point2=fgetc(arch);
               point3=fgetc(arch);
               point4=fgetc(arch);
               pointer=((point4*16777216+point3*65536+point2*256)+point1);
               //printf("pointer %d su %d: %x\n",i,number,pointer);
               fseeko64(arch,pointer-4,SEEK_CUR);
               }
               length=ftell(arch)-tim3[num];
               fprintf(lolg,"%s:%u:%d:1\n", stringa,tim3[num],length+0x80);
               //printf("lunghezza: %x",length);
               fseeko64(arch,tim3[num],SEEK_SET);
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
              
             
             
int timins(char *nuovoargv4)
{
    sprintf(stringa, "TIM2\\%s", nuovoargv4);
                  if (chdir(stringa)==-1)
                  {
                  printf("The file %s hasn't been extracted, or it's been renamed or something went wrong.\n\nBackup your progresses and extract it again (or try to find out why this message appeared)",nuovoargv4);
                  return(0);
                  }
                  chdir("..");
                  chdir("..");
                  sprintf(stringa, "TIM3\\%s", nuovoargv4);
                  if (chdir(stringa)==-1)
                  {
                   printf("The file %s hasn't been extracted, or it's been renamed or something went wrong.\n\nBackup your progresses and extract it again (or try to find out why this message appeared)",nuovoargv4);
                  return(0);
                  }
                  chdir("..");
                  chdir("..");
                  //TIM2
                  sprintf(stringa, "TIM2\\%s\\spec.log", nuovoargv4);
                  if (fopen (stringa,"r+b")==NULL)
                  {
                            printf("The file %s doesn't exist or it's in use by another program.\n",stringa);
                            return(0);
                            }
                            
                   lolg=fopen (stringa,"r+b");                     
                  while (bytes!=0x0A)  
                  {
                        bytes=fgetc(lolg);
                        pot++;
                        } 
                  fseek(lolg,ftell(lolg)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>0;q--)
                  {
                    bytes=fgetc(lolg)-0x30;
                    numbers=numbers+bytes*pow(10,q-0x01);
                    //printf("%d\n",numbers);
                    }
                   fseek(lolg,1,SEEK_CUR);
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
                      bytes=fgetc(lolg);
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
                        bytes=fgetc(lolg);
                        pot++;
                        } 
                  fseek(lolg,ftell(lolg)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>1;q--)
                  {
                    bytes=fgetc(lolg)-0x30;
                    
                    tempz=bytes;
                    for(w=0;w<q-1;w++)
                    {
                    tempz=tempz*10;
                    
                    }
                    inizio=inizio+tempz;
                    
                    }
                    bytes=fgetc(lolg)-0x30;
                    inizio=inizio+bytes;
                    //printf("%d ",inizio);
                    //Recuperato Offset iniziale del file
                    fseek(lolg,1,SEEK_CUR);
                    pot=0;
                   bytes=0;
                   while (bytes!=0x3A)  
                  {
                        bytes=fgetc(lolg);
                        pot++;
                        } 
                  fseek(lolg,ftell(lolg)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>0;q--)
                  {
                    bytes=fgetc(lolg)-0x30;
                    
                    tempz=bytes;
                    for(w=0;w<q-1;w++)
                    {
                    tempz=tempz*10;
                    //printf("%d\n",tempz);
                    }
                    peso=peso+tempz;
                    //printf("%d\n",peso);
                    }
                    //bytes=fgetc(lolg)-0x30;
                    //peso=peso+bytes;
                    //printf("%d ",peso);
                    fseek(lolg,1,SEEK_CUR);
                    archive=fgetc(lolg)-0x30;
                    //printf("%d\n",archive);
                    fseek(lolg,1,SEEK_CUR);
                   
                   if (archive==0)
                   {
                      fseeko64(arch,inizio,SEEK_SET);
                      
                      chdir("TIM2");
                      chdir(nuovoargv4);
                                      
                      
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
                      printf("\rTIM2 reinserted successfully[%d%%]",((i+1)*100)/numbers);
                      fclose(tm2);
                      chdir("..");
                      chdir("..");
                      }
                      //system("pause");
                      }
                      if (archive==1)
                   {
                      fseeko64(arch,inizio,SEEK_SET);
                      
                      chdir("TIM2");
                      chdir(nuovoargv4);
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
                  //sprintf(stringa, "%s.tm2", nuovoargv4);
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
                      fclose(tm2);
                      chdir("..");
                      chdir("..");
                      }}
                      //system("pause");
                      }
                      
                      
                      fclose(lolg);
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
                   sprintf(stringa, "TIM3\\%s\\spec.log", nuovoargv4);
                  if (fopen (stringa,"r+b")==NULL)
                  {
                            printf("The file %s doesn't exist or it's in use by another program.\n",stringa);
                            return(0);
                            }
                            
                   lolg=fopen (stringa,"r+b");                     
                  while (bytes!=0x0A)  
                  {
                        bytes=fgetc(lolg);
                        pot++;
                        } 
                        
                  fseek(lolg,ftell(lolg)-pot,SEEK_SET);  
                  pot=pot-1;
                 // system("pause");
                  for (q=pot;q>0;q--)
                  {
                    bytes=fgetc(lolg)-0x30;
                    numbers=numbers+bytes*pow(10,q-0x01);
                    //printf("%d\n",numbers);
                    }
                    //printf("%d\n",numbers);
                   fseek(lolg,1,SEEK_CUR);
                   
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
                      bytes=fgetc(lolg);
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
                        bytes=fgetc(lolg);
                        pot++;
                        } 
                  fseek(lolg,ftell(lolg)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>1;q--)
                  {
                    bytes=fgetc(lolg)-0x30;
                    
                    tempz=bytes;
                    for(w=0;w<q-1;w++)
                    {
                    tempz=tempz*10;
                    
                    }
                    inizio=inizio+tempz;
                    
                    }
                    bytes=fgetc(lolg)-0x30;
                    inizio=inizio+bytes;
                    //printf("%d ",inizio);
                    //Recuperato Offset iniziale del file
                    fseek(lolg,1,SEEK_CUR);
                    pot=0;
                   bytes=0;
                   while (bytes!=0x3A)  
                  {
                        bytes=fgetc(lolg);
                        pot++;
                        } 
                  fseek(lolg,ftell(lolg)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>0;q--)
                  {
                    bytes=fgetc(lolg)-0x30;
                    
                    tempz=bytes;
                    for(w=0;w<q-1;w++)
                    {
                    tempz=tempz*10;
                    //printf("%d\n",tempz);
                    }
                    peso=peso+tempz;
                    //printf("%d\n",peso);
                    }
                    //bytes=fgetc(lolg)-0x30;
                    //peso=peso+bytes;
                    //printf("%d ",peso);
                    fseek(lolg,1,SEEK_CUR);
                    archive=fgetc(lolg)-0x30;
                    //printf("%d\n",archive);
                    fseek(lolg,1,SEEK_CUR);
                   
                   if (archive==0)
                   {
                      fseeko64(arch,inizio,SEEK_SET);
                      
                      chdir("TIM3");
                      chdir(nuovoargv4);
                                      
                      
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
                      printf("\rTIM3 reinserted successfully[%d%%]",((i+1)*100)/numbers);
                      fclose(tm3);
                      chdir("..");
                      chdir("..");
                      }}
                      
                      if (archive==1)
                   {
                      fseeko64(arch,inizio,SEEK_SET);
                      
                      chdir("TIM3");
                      chdir(nuovoargv4);
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
                  //sprintf(stringa, "%s.tm3", nuovoargv4);
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
                      fclose(tm3);
                      chdir("..");
                      chdir("..");
                      }}
                      
                   }}
