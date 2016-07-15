void gimsearch(void)
{
     fseeko64(arch,0x00,SEEK_END);
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
                             tempoff=ftello64(arch);
                             fseeko64(arch,gim[r-1]+0x14,SEEK_SET);
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
                               fseeko64(arch,tempoff,SEEK_SET);                              
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
                             tempoff=ftello64(arch);
                             fseeko64(arch,gim[r-1]+0x14,SEEK_SET);
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
                               fseeko64(arch,tempoff,SEEK_SET);   
                             }
                                                      
                             }}}
                             
                             
int gimextr(char *nuovoargv3)
{
    if (r==0)
              {
                       printf("Sorry pal. No GIM has been detected\n\n");
                       //return 0;
                       }else{
              
              printf("Founded %d GIM in %s.\n\nExtraction in progress\n",r,nuovoargv3);              
              //fine ricerca header
              mkdir("GIM");
              chdir("GIM");
              mkdir(nuovoargv3);
              chdir(nuovoargv3);
              lolg=fopen("spec.log", "w+b");
              fprintf(lolg,"%d\n",r);
			  
			  for (num=0;num<r;num++)
              {
              printf("\r[%d%%]",((num+1)*100)/r);
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
              
			  
			  
			  fseeko64(arch,gim[num],SEEK_SET);
              fseeko64(arch,0x14,SEEK_CUR);
              point1=fgetc(arch);
              point2=fgetc(arch);
              point3=fgetc(arch);
              point4=fgetc(arch);
              length=((point4*16777216+point3*65536+point2*256)+point1);
              fprintf(lolg,"%s:%u:%d:0\n", stringa,gim[num],length);
              fseeko64(arch,gim[num],SEEK_SET);
              for (c=0;c<length;c=c+0x01)
          {
              fputc(fgetc(arch),Gim);
              }
              fclose(Gim);
              }
              }
              chdir("..");
              chdir("..");
              printf("\n\n");
              }
              
              
int gimins(char *nuovoargv5)
{
    sprintf(stringa, "GIM\\%s", nuovoargv5);
                  if (chdir(stringa)==-1)
                  {
                  printf("The file %s hasn't been extracted, or it's been renamed or something went wrong.\n\nBackup your progresses and extract it again (or try to find out why this message appeared)",nuovoargv5);
                  return(0);
                  }
                  chdir("..");
                  chdir("..");
                  sprintf(stringa, "GIM\\%s\\spec.log", nuovoargv5);
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
                  //  Recuperato numero di GIM presenti nel file
                  prova=0;
                  for (i=0;i<numbers;i++)
                  {
                   //system("pause");
                   *stringa=0x00;
                   prova=0;
                   bytes=0x00;
                   inizio=0;
                   peso=0;
                   tempz=0;
                   //system("pause");
                   while (prova!=1)
                   {
                      bytes=fgetc(lolg);
                      //printf("%x:  %x\n",ftell(lolg)-1,bytes);
                      //system("pause"); 
                      if (bytes==0x3A)
                      {
                          prova=1;
                          }else{
                   sprintf(stringa,"%s%c",stringa,bytes);
                   }} 
                   //system("pause");               
                   //printf("%s ",stringa);
                   //Recuperato nome del file
                  //system("pause");
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
                    //Recuperato Offset iniziale del file
                    fseek(lolg,1,SEEK_CUR);
                    pot=0;
                   bytes=0;
                   while (bytes!=0x3A)  
                  {
                        bytes=fgetc(lolg);
                        pot++;
                        } 
                        //system("pause");
                  fseek(lolg,ftell(lolg)-pot,SEEK_SET);  
                  pot=pot-1;
                  for (q=pot;q>0;q--)
                  {
                    bytes=fgetc(lolg)-0x30;
                    
                    tempz=bytes;
                    for(w=0;w<q-1;w++)
                    {
                    tempz=tempz*10;
                    
                    }
                    peso=peso+tempz;
                    
                    }
                    
                    fseek(lolg,1,SEEK_CUR);
                    archive=fgetc(lolg)-0x30;
                    fseek(lolg,1,SEEK_CUR);
                   if (archive==0)
                   {
                      fseeko64(arch,inizio,SEEK_SET);
                      
                      chdir("GIM");
                      chdir(nuovoargv5);
                      Gim=fopen(stringa,"r+b");
                      fseek(Gim,0x00,SEEK_END);
                      dim=ftell(Gim);
                      if (dim!=peso)
                      {
                      printf("\n%s: This tool is not some kind of magic wand! The new GIM must be of the same size of the original\n\n",stringa);                    
                      chdir("..");
                      chdir("..");
                      }else{
                      rewind(Gim);
                      
                      times=dim/(131072);
                      for (c=0;c<times;c++)
                      {
                      fread(buffer,131072,1,Gim);
                      fwrite(buffer,131072,1,arch);
                      }
                      rest=dim%131072;
                      //system("pause");
                      if(rest)
                      {
                      fread(buffer,rest,1,Gim);
                      fwrite(buffer,rest,1,arch);
                      }
                      //system("pause");
                      printf("\rGIM reinserted successfully[%d%%]",((i+1)*100)/numbers);
                      //system("pause");
                      fclose(Gim);
                      chdir("..");
                      chdir("..");
                      //system("pause");
                      }
                      //system("pause");
                      }
                      
                      
                      
                      //fclose(lolg);
                      
                      
                   }
                   printf("\n");
                   }
