#include <stdio.h>
#include <windows.h>
#include <math.h>


/*Prototipi funzioni*/
void tmsearch(void);
int tmextr(char *nuovoargv2);
void gimsearch(void);
int gimextr(char *nuovoargv3);
int timins(char *nuovoargv4);
int gimins(char *nuovoargv5);
//void tplsearch(void);
/*Fine Prototipi Funzioni*/


/*Variabili Globali*/
BYTE buffer[10485760];
FILE *arch, *tm2, *Gim, *dat, *tmptm2, *lolg, *tm3, *tmptm3;
unsigned long int i=0,length,numbers=0,tempz,dim,prova=0,archive,peso=0,pointer,end=0,tpl[9999],gim[9999],tim2[9999],tim3[9999],f=0,g=0,r=0,t=0,tempoff,off=0x00;
unsigned long int c,w,s,endfile,times,rest,tot,lunghezza,num,n0=0,n1=0,n2=0,n3=1;
unsigned char  bytes,point1,point2,point3,point4,number,head[16];
unsigned char temp[500],stringa[500],name[79],path[1000],nomefile[104];
float pot=0,q;
long long unsigned int inizio=0;
/*Fine Variabili Globali*/


/*My Files*/
#include "Tim2.c"
#include "Gim.c"
//#include "Tpl.c"
