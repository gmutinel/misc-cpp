	typedef struct FileInfo
	{
		unsigned long int pointer;
		unsigned long int nulled1;
		unsigned char unk1[4];
		unsigned long int nulled2;
		unsigned long int size;
		int NameLen;
		char *filename;
	} DarkHead;