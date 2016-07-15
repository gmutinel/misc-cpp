
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

#include "brres.h"

char color_type[][16] = {
	"0 : I4",
	"1 : I8",
	"2 : IA4",
	"3 : IA8",
	"4 : RGB565",
	"5 : RGB5A3",
	"6 : RGBA8",
	"7 : -",
	"8 : C4",
	"9 : C8",
	"10: C14x2",
	"11: -",
	"12: -",
	"13: -",
	"14: CMP",
	"15: -",
};

char plt_type[][16] = {
	"0: IA8",
	"1: RGB565",
	"2: RGB5A3",
};

int section_offset[65536];
int nsec;

void put_space(int level)
{
	int i;

	for(i=0; i<level; i++){
		printf("    ");
	}
}

u16 BE16(u16 data)
{
	return ( (data<<8) | (data>>8) );
}

u32 BE32(u32 data)
{
	return ( (data<<24) | ((data<<8)&0x00ff0000) |
			 ((data>>8)&0x0000ff00) | (data>>24) );
}

void dump_root_dir(char *buf, int base, int end, int level)
{
	DIRECTORY_desc *dir;
	OBJECT_desc *obj;
	int i;

	int unk0;
	int unk1;
	int unk2;
	int unk3;
	int name_offset;
	int data_offset;

	dir = (DIRECTORY_desc*)(buf+base);
	obj = (OBJECT_desc *)(buf+base+sizeof(DIRECTORY_desc));

	unk0 = BE32(dir->unk0);
	unk1 = BE32(dir->unk1);
	unk2 = BE32(dir->unk2);
	unk3 = BE32(dir->unk3);
	put_space(level); printf("%08x %08x %08x %08x\n", unk0, unk1, unk2, unk3);


	for(i=0; i<BE32(dir->object_num); i++){
		unk0 = BE16(obj[i].unk0);
		unk1 = BE16(obj[i].unk1);
		unk2 = BE16(obj[i].unk2);
		unk3 = BE16(obj[i].unk3);
		name_offset = BE32(obj[i].name_offset)+base;
		data_offset = BE32(obj[i].data_offset)+base;

		put_space(level); printf("%-16s    %04x %04x  %04x %04x  %08x\n",
				buf+name_offset, unk0, unk1, unk2, unk3, data_offset);

		if(data_offset<end){
			dump_root_dir(buf, data_offset, end, level+1);
		}else{
			section_offset[nsec] = data_offset;
			nsec++;
		}
	}
}

void dump_root(char *buf, int base)
{
	SECTION_header *section;
	int offset, end;

	section = (SECTION_header*)(buf+base);
	offset = base+sizeof(SECTION_header);
	end = base+BE32(section->size);

	dump_root_dir(buf, offset, end, 1);

	printf("\n");
}

void dump_PLT0(char *buf, int base)
{
	PLT0_section *plt;
	char *name;
	int type, n;

	plt = (PLT0_section*)(buf+base);
	name = buf+base+BE32(plt->name_offset);
	type = BE32(plt->type);
	n = BE16(plt->entry_num);

	printf("for %-16s : type %-16s  entries %d\n", name, plt_type[type], n);
}

void dump_TEX0(char *buf, int base)
{
	TEX0_section *tex;
	char *name;
	int type, have_pal, width, height;

	tex = (TEX0_section*)(buf+base);
	name = buf+base+BE32(tex->name_offset);
	type = BE32(tex->type);
	width = BE16(tex->width);
	height = BE16(tex->height);
	have_pal = BE32(tex->have_pal);

	put_space(1); printf("%-16s : type %-16s  %3dx%3d  %s\n", name, color_type[type], width, height, have_pal?"have pal":"");
}

void brres_dump(char *buf)
{
	BRRES_header *brres;
	SECTION_header *section;
	int name[2];
	int i, base;

	brres = (BRRES_header*)buf;
	if(brres->tag!=0x73657262){
		printf("Not a brres file!\n");
		return;
	}

	base = BE16(brres->header_size);

	nsec = 0;

	printf("\n");

	dump_root(buf, base);

	for(i=0; i<nsec; i++){
		base = section_offset[i];
		section = (SECTION_header*)(buf+base);
		name[0] = section->tag;
		name[1] = 0;
		printf("[%s]:\n", (char*)&name[0]);

		if(section->tag==0x746f6f72){
		}else if(section->tag==0x30544c50){
			dump_PLT0(buf, base);
		}else if(section->tag==0x30584554){
			dump_TEX0(buf, base);
		}

		printf("\n");
	}

}

int process_file(char *infname)
{
	FILE *fp;
	char *buf;
	int fsize;

	printf("process <%s> ...\n", infname);

	fp = fopen(infname, "rb");
	if(fp==NULL){
		printf("Open %s failed!\n", infname);
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buf = malloc(fsize);
	fread(buf, fsize, 1, fp);
	fclose(fp);

	brres_dump(buf);

	free(buf);
	return 0;
}

int process_dir(char *dname)
{
	DIR *pdir;
	struct dirent *d;
	struct stat statbuf;
	char fname[256];

	pdir = opendir(dname);
	if(pdir==NULL){
		printf("Can't open directory <%s>\n", dname);
		return -1;
	}

	//printf("Enter directory <%s> ...\n", dname);
	while((d=readdir(pdir))){
		if( d->d_name[0]=='.' &&( d->d_name[1] =='\0' || (d->d_name[1] == '.' && d->d_name[2] == '\0') ))
			continue;

		if(dname[0]=='.'){
			sprintf(fname, "%s", d->d_name);
		}else{
			sprintf(fname, "%s/%s", dname, d->d_name);
		}

		memset(&statbuf, 0, sizeof(statbuf));
		stat(fname, &statbuf);
		if((statbuf.st_mode&S_IFMT) == S_IFDIR){
#if 0
			// don't process sub-directory
			printf("Skip directory <%s> ...\n", dname);
#else
			process_dir(fname);
#endif
		}else{
			process_file(fname);
		}
	}

	//printf("Leave directory <%s>\n\n", dname);
	closedir(pdir);
	return 0;
}

int main(int argc, char *argv[])
{
	struct stat statbuf;

	if(argc==1){
		return process_dir(".");
	}

	memset(&statbuf, 0, sizeof(statbuf));
	stat(argv[1], &statbuf);
	if((statbuf.st_mode&S_IFMT) == S_IFDIR){
		return process_dir(argv[1]);
	}else{
		return process_file(argv[1]);
	}

}

