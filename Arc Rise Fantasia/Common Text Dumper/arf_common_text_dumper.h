#ifndef __ARF_COMMON_TEXT_DUMPER__
#define __ARF_COMMON_TEXT_DUMPER__

#include <stdio.h>
#include <windows.h>

#ifdef __cplusplus 
extern "C"{
#endif
/*Prototipi funzioni*/
void DumpOperation(void);
void DumpAbility(void);
/*Fine Prototipi Funzioni*/
#ifdef __cplusplus 
}
#endif


/*Variabili Globali*/
static BYTE buffer[102400];
static FILE *text,*dump,*shit;
static unsigned long int filenumb,x,i,len;
static const unsigned char files[2][100]={
{'o','p','e','r','a','t','i','o','n','.','b','i','n'},
{'a','b','i','l','i','t','y','.','b','i','n'}
};    

/*Fine Variabili Globali*/
#endif
