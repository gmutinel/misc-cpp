#include <stdio.h>
#include <Windows.h>

#include <stdlib.h>
#include <time.h>

typedef int (CALLBACK* FindKey)(char*);

int main(int argc, char *argv[])
{
FILE *log;
FindKey addr = NULL;
HINSTANCE dllHandle = NULL;
int result;
unsigned long int num, count,index,bigindex;

if (argc < 2) 
	num = 9999;
else
	num = (int)argv[1];

dllHandle = LoadLibraryA("WepChkId.dll");
addr = (FindKey)GetProcAddress(dllHandle,"CheckSerialId");

log = fopen("keys.log","a+b");
char *Key = NULL;//(LPCSTR)"AAA0-AAAA-AAAA-AAAA";
Key = (char*)malloc(25);
char keys[36]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
srand(time(NULL));

//while (result != 0)
//printf("No keys found so far...");
index = 0;
bigindex = 0;
while (num < count)
{
	sprintf(Key,"%c%c%c%c-%c%c%c%c-%c%c%c%c-%c%c%c%c-%c%c%c%c\0",keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36]);
	//sprintf(Key,"AAA%c-%c%c%c%c-%c%c%c%c-%c%c%c%c-%c%c%c%c\0",keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36],keys[rand() % 36]);
	//system("pause");
		
	result = addr(Key);	
	index = index+1;
	printf("\rTested %d000 keys...",bigindex);
	if (index == 1000)
	{
		srand(time(NULL));
		bigindex = bigindex +1;
		index= 0;
	}
	if (result == 0)
	{
		count = count+1;
		fwrite(log,36,1,log);
		fprintf(log,"\n");
		//system("cls");
		printf("\nFounded a key! Logged: %s\n",count,Key);
	}
}

fclose(log);
FreeLibrary(dllHandle);
return(1);
}