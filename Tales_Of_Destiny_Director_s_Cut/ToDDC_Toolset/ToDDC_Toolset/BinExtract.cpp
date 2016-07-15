#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include "vars.h"
#include "complib.h"

char* AssignExtension(BYTE *buffer, int n0, int n1, int n2, int n3,unsigned long int len);
int CheckForArch(BYTE *buffer);
int CheckForArch2(BYTE *buffer, unsigned long int tlen);

int ExtractBin(char *filename)
{

	FILE *bin, *ext, *exe, *tbl;
    int compression=0;
    char *finalname,name[17];
    unsigned long int x,numpoint, pointer, fpoints[18000],i,rpoints[18000],c,temp,padding[18000],dim[18000],n0=0,n1=0,n2=0,n3=0; 
    unsigned int comprbyte;
    int err,declen,complen;      
      

	bin=fopen(filename,"rb");
      
      
     if ((strcmp(filename,"DAT.BIN") == 0))
     {
		//numpoint=14982;
        //pointer=0xD76B0;        
        exe=fopen("DAT.TBL","rb");
		_mkdir("DAT");
        _chdir("DAT");
        //makedirs per estensioni
		_mkdir("SCPK");
		_mkdir("TIM2");
		_mkdir("IECS");
		_mkdir("EBG");
		//_mkdir("MISC");
		_mkdir("ELF");
		_mkdir("SKT");
		_mkdir("ARCH");
		_mkdir("AUDIO");
		_mkdir("DUMMY");
      } 
    
	 if (strcmp(filename,"MOV.BIN") == 0)
      {
          //numpoint=21;
          //pointer=0xE60D0;        
          exe=fopen("MOV.TBL","rb");

		  _mkdir("MOV");
          _chdir("MOV");
      }
      
	  

		if (!(exe))
	{
		printf("Can't find or open SLPS_254.50. The file MUST be in the same dir as the BIN");
		return(0);
	}
	
     tbl=fopen("table.bin","w+b");
     fseek(exe,0,SEEK_END);
	 numpoint = (ftell(exe) / 4) / 2;
	 rewind(exe);
	 for (i=0;i<numpoint;i++)
     {
		fread(&fpoints[i],4,1,exe);
		fseek(exe,4,SEEK_CUR);
     }
    
    for (i=0;i<numpoint-1;i++)
    {
		temp=fpoints[i]; 
        for(c=0;c<0x40;c++)
        {
                       
          if (((temp%64) == 0) || (temp == 0) )
          {
               rpoints[i]=temp;
               c=0x41;
               }else{
                     temp--;
           
                     }                   
                     } 
         //                             
         //printf("%x = %x\n",fpoints[i],rpoints[i]);
         padding[i]=fpoints[i]-rpoints[i];
         }    
         rpoints[numpoint-1]=fpoints[numpoint-1];
         //printf("%x\n",fpoints[numpoint-1]);
         for (i=0;i<numpoint-1;i++)
         {
		     dim[i]=rpoints[i+1]-rpoints[i]-padding[i];      
                      
			 sprintf(name,"%d%d%d%d.dat\0",n0,n1,n2,n3);
       
       //ext=fopen(name,"w+b");
       fseek(bin,rpoints[i],SEEK_SET);
       printf("%s",name);
       //test compressione
       compression=0;
       comprbyte=fgetc(bin);
	   if (comprbyte == 0x01 || comprbyte == 0x02 || comprbyte == 0x03)
       {
        fread(&complen,4,1,bin);    
        if (complen==dim[i]-9)
        {
        printf("...compression type %X found.\n",comprbyte);    
        compression=1;
		fread(&declen,4,1,bin);
		dec=(BYTE *)malloc(declen);
        }else{
         printf("\n");
	     fseek(bin,rpoints[i],SEEK_SET);
	     complen=dim[i];
		}
       }else{
       printf("\n");
	   fseek(bin,rpoints[i],SEEK_SET);
	   complen=dim[i];
       }    
           
       //fine test compressione
       
      comp=(BYTE *)malloc(complen);
	  fread(comp,complen,1,bin);
       //se è compresso
       if (compression == 1)
       {
        if (comprbyte == 0x01)
        {
         x=1;   
        } 
        if (comprbyte == 0x02)
        {
         x=2;   
        }
        if (comprbyte == 0x03)
        {
         x=3;   
        }
         err=Decode(x, comp, complen, dec, &declen);      
         if (err == 0)
		 {
			 finalname=AssignExtension(dec,n0,n1,n2,n3,declen);
	         ext=fopen(finalname,"wb");
			 fwrite(dec,declen,1,ext);
			 free(dec);
			 fclose(ext);
		 } else {
         
         fseek(bin,rpoints[i],SEEK_SET);
	     free(comp);
		 comp=(BYTE *)malloc(dim[i]);
		 fread(comp,dim[i],1,bin);
		 finalname=AssignExtension(comp,n0,n1,n2,n3,dim[i]);
	     ext=fopen(finalname,"wb");
		 fwrite(comp,dim[i],1,ext);
		 free(comp);
	     fclose(ext);		 
		 }
        }else{
         comprbyte = 0xFF;
         finalname=AssignExtension(comp,n0,n1,n2,n3,dim[i]);

	
	   
	         ext=fopen(finalname,"wb");
			 fwrite(comp,dim[i],1,ext);
		 free(comp);
			 fclose(ext);
	         }

	   
       
        
	  // fclose(ext);
        //table
        fwrite(finalname,17,1,tbl);
        fputc(comprbyte,tbl);
            
        //aumento variabili del nome
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
return(1);
	   }

char* AssignExtension( BYTE *buffer, int n0, int n1, int n2, int n3,unsigned long int len)
{
    char thei[9],*name;
	unsigned char est[5];
	int check=0;


	   //controllo dell'estensione
        est[0]=buffer[0];
        est[1]=buffer[1];
		est[2]=buffer[2];
		est[3]=buffer[3];
		est[4]=0;
        name=(char *)malloc(50);
        
		
       sprintf(name,"%d%d%d%d.dat\0",n0,n1,n2,n3);
       
	   //AUDIO
	   if (buffer[0] == 0x00 && buffer[1] == 0x00 && buffer[2] == 0x00 && buffer[3] == 0x00 && buffer[4] == 0x00 && buffer[5] == 0x00 && buffer[6] == 0x00 && buffer[7] == 0x00 && buffer[8] == 0x00 && buffer[9] == 0x00 && buffer[10] == 0x00 && buffer[11] == 0x00 && buffer[12] == 0x00 && buffer[13] == 0x00 && buffer[14] == 0x00 && buffer[15] == 0x00 /*&& buffer[16] == 0x0C*/)
	   {
		   sprintf(name,"AUDIO\\%d%d%d%d.snd\0",n0,n1,n2,n3);
		 return(name);

	   }

	   if (est[0] == 0x53 && est[1]==0x43 && est[2] == 0x50 && est[3] == 0x4B)
        {
         sprintf(name,"SCPK\\%d%d%d%d.scpk\0",n0,n1,n2,n3);
		 return(name);
        }   
       // printf("\n%s\n",est);     
       //
       if (len == 0)
       {
         sprintf(name,"DUMMY\\%d%d%d%d.null\0",n0,n1,n2,n3); 
		 return(name);
       }    
       // if (strcmp(est,"TIM2")==0)
        if (est[0] == 0x54 && est[1]==0x49 && est[2] == 0x4D && est[3] == 0x32)
        {
         
         sprintf(name,"TIM2\\%d%d%d%d.tm2\0",n0,n1,n2,n3);
		 return(name);
        }
        
               
        if (est[0] == 0x45 && est[1]==0x42 && est[2] == 0x47 && est[3] == 0x00)
        {
         
         sprintf(name,"EBG\\%d%d%d%d.ebg\0",n0,n1,n2,n3);
		 return(name);
        }
        
        
        
        if (est[0] == 0x7F && est[1]==0x45 && est[2] == 0x4C && est[3] == 0x46)
        {
         
         sprintf(name,"ELF\\%d%d%d%d.elf\0",n0,n1,n2,n3);
		 return(name);
        }
        
               
        if (est[0] == 0x20 && est[1]== 0x00 && est[2] == 0x00 && est[3] == 0x00)
        {
         
	     
		 thei[0]=buffer[0x20];
         thei[1]=buffer[0x21];
		 thei[2]=buffer[0x22];
		 thei[3]=buffer[0x23];
		 thei[4]=buffer[0x24];
		 thei[5]=buffer[0x25];
		 thei[6]=buffer[0x26];
		 thei[7]=buffer[0x27];
		 thei[8]=0;
         if (strcmp(thei,"THEIRSCE")==0)  
         {
         
         sprintf(name,"SKT\\%d%d%d%d.skt\0",n0,n1,n2,n3);
        }
		 return(name);
        }
        
        if (buffer[0] == 0x49 && buffer[1] == 0x45 && buffer[2] == 0x43 && buffer[3] == 0x53 && buffer[4] == 0x73 && buffer[5] == 0x72 && buffer[6] == 0x65 && buffer[7] == 0x56)
		{
			sprintf(name,"IECS\\%d%d%d%d.iecs\0",n0,n1,n2,n3);
			return(name);
		}

		check=CheckForArch(buffer);
     

		if (check == 1)
		{
			sprintf(name,"ARCH\\%d%d%d%d.arch\0",n0,n1,n2,n3);
			return(name);
		}

		/*if (strcmp(name,"0013.dat\0")==0)
		{
			sprintf(name,"MISC\\%d%d%d%d.dat\0",n0,n1,n2,n3);
			return(name);
		}*/
		
		/*check=0;

		check=CheckForArch2(buffer,len);

		if (check == 1)
		{
			sprintf(name,"ARCH2\\%d%d%d%d.arch2\0",n0,n1,n2,n3);
			return(name);
		}*/

		return(name);
		}



		int CheckForArch(BYTE *buffer)
		{
          unsigned long int num,pos;
		  int check=0;
		 
		  
		  num=buffer[3]*0x1000000+buffer[2]*0x10000+buffer[1]*0x100+buffer[0];
		  pos=buffer[7]*0x1000000+buffer[6]*0x10000+buffer[5]*0x100+buffer[4];
		 
		  
		  if (pos == ((num*8)+4))
			  check=1;

		  return(check);
		}

		
		int CheckForArch2(BYTE *buffer,unsigned long int tlen)
		{
          unsigned long int num,len,sum=0,c;
		  unsigned int i;
		  int check=0;
		  num=buffer[3]*0x1000000+buffer[2]*0x10000+buffer[1]*0x100+buffer[0];
		  c=3;
		  sum=4+(num*4);
		  if (num < 0x100)
		  {
		   for (i=0;i<num;i++)
		    {

				len=buffer[c+3]*0x1000000+buffer[c+2]*0x10000+buffer[c+1]*0x100+buffer[c];
                c=c+4;
				sum=sum+len;

		    }

		   if (sum == tlen)
			   check=1;

		  }
		  return(check);
		}