/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *
 *  simple BRRES texture extractor
 *  based on tplx
 *
 *  Copyright (c) 2009 tpu
 *  Copyright (c) 2004 monk
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

#include <libpng12/png.h>

#include "brres.h"

#define MASK_ALPHA		0xff000000
#define MIN(a, b)  ((a)<(b)?(a):(b))

u16 BE16(u16 data)
{
	return ( (data<<8) | (data>>8) );
}

u32 BE32(u32 data)
{
	return ( (data<<24) | ((data<<8)&0x00ff0000) |
			 ((data>>8)&0x0000ff00) | (data>>24) );
}


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

u8 texbuff[1024*1024*4];
u8 pltbuff[1024*4];

char dname[64];

// RGB565: rrrr rggg gggb bbbb
u32 color_unpack_rgb565 (u32 X)
{
	return (((X&0xf800)<<8) | ((X&0x07e0)<<5) | ((X&0x001f)<<3) | 0xFF000000);
}

//RGB555: 1rrr rrgg gggb bbbb
u32 color_unpack_rgb555 (u32 X)
{
	return ((X&0x7c00)<<9) | ((X&0x03e0)<<6) | ((X&0x001f)<<3);
}

// RGB4A3  0aaa rrrr gggg bbbb
u32 color_unpack_rgb4a3 (u32 X)
{
	return (((X&0x0f00)<<12) | ((X&0x00f0)<<8) | ((X&0x000f)<<4) | ((X&0x7000)<<17));
}

u32 color_unpack_rgb5a3 (u32 X)
{
	if (X&0x8000)
		return (color_unpack_rgb555 (X) | 0xFF000000);
	else
		return color_unpack_rgb4a3 (X);
}

//IA8: aa ii
u32 color_unpack_ia8 (u32 X)
{
	u32 a = (X&0xff00)>>8;
	X = (X&0x00ff);
	return (X | (X<<8) | (X<<16) | (a<<24));
}


////////////////////////////////////////////////////////////////////////////////////////////////

int save_png(char *base_name, int format, int bpp, char *data, int llen, int width, int height, char *plt, int nplt)
{
	png_structp png_ptr;
	png_infop info_ptr;
	char png_name[256];
	FILE *fp;

	int i;

	sprintf(png_name, "%s/%s.png", dname, base_name);
	fp = fopen(png_name, "wb");

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(png_ptr==NULL){
		printf("PNG error create png_ptr!\n");
		return -1;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr==NULL){
		printf("PNG error create info_ptr!\n");
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		return (-1);
	}

	png_init_io(png_ptr, fp);

	/* write header */
	png_set_IHDR(png_ptr, info_ptr, width, height, bpp,
				format, PNG_INTERLACE_NONE,
				PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	if(nplt) {
		png_colorp pcolor;
		char *palpha;
		int alpha;

		/* write palette */
		pcolor = (png_colorp)malloc(nplt*sizeof(png_color));
		for(i=0; i<nplt; i++){
			pcolor[i].red   = plt[i*4+0];
			pcolor[i].green = plt[i*4+1];
			pcolor[i].blue  = plt[i*4+2];
		}
		png_set_PLTE(png_ptr, info_ptr, pcolor, nplt);
		free(pcolor);

		/* write alpha of palette */
		alpha = 0;
		palpha = (char*)malloc(nplt);
		for(i=0; i<nplt; i++){
			palpha[i] = plt[i*4+3];
			alpha += plt[i*4+3];
		}
		if(alpha){
			png_set_tRNS(png_ptr, info_ptr, (png_bytep)palpha, nplt, (png_color_16p)0);
		}
		free(palpha);
	}

	png_write_info(png_ptr, info_ptr);

	/* write image data */
	for(i=0; i<height; i++){
		png_write_row(png_ptr, data+i*llen);
	}
	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////

void I4_to_png(char *name, u8 *src, int width, int height, char *plt, int ptype, int entry)
{
	u8 *dst = texbuff;
	int h, v, x, y, ofs;

	int tw=8, th=8, bpp=4;
	int format = PNG_COLOR_TYPE_GRAY;
	int llen = ((width+tw-1)&~(tw-1))/2;

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=2){
					dst[ofs+x/2] = *src++;
				}
                ofs += llen;
            }
            dst += tw*bpp/8;
        }
        dst += llen*(th-1);
    }

	save_png(name, format, bpp, texbuff, llen, width, height, NULL, 0);
}

void I8_to_png(char *name, u8 *src, int width, int height, char *plt, int ptype, int entry)
{
	u8 *dst = texbuff;
	int h, v, x, y, ofs;

	int tw=8, th=4, bpp=8;
	int format = PNG_COLOR_TYPE_GRAY;
	int llen = ((width+tw-1)&~(tw-1));

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					dst[ofs+x] = *src++;
				}
                ofs += llen;
            }
            dst += tw*bpp/8;
        }
        dst += llen*(th-1);
    }

	save_png(name, format, bpp, texbuff, llen, width, height, NULL, 0);
}

void IA4_to_png(char *name, u8 *src, int width, int height, char *plt, int ptype, int entry)
{
	u8 *dst = texbuff;
	int h, v, x, y, ofs;

	int tw=8, th=4, bpp=32;
	int format = PNG_COLOR_TYPE_RGB_ALPHA;
	int llen = ((width+tw-1)&~(tw-1))*4;

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					dst[ofs+x*4+0] = src[0]<<4;
					dst[ofs+x*4+1] = src[0]<<4;
					dst[ofs+x*4+2] = src[0]<<4;
					dst[ofs+x*4+3] = src[0]&0xf0;
					src++;
				}
                ofs += llen;
            }
            dst += tw*bpp/8;
        }
        dst += llen*(th-1);
    }

	save_png(name, format, bpp/4, texbuff, llen, width, height, NULL, 0);
}

void IA8_to_png(char *name, u8 *src, int width, int height, char *plt, int ptype, int entry)
{
	u8 *dst = texbuff;
	int h, v, x, y, ofs;

	int tw=4, th=4, bpp=32;
	int format = PNG_COLOR_TYPE_RGB_ALPHA;
	int llen = ((width+tw-1)&~(tw-1))*4;

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					dst[ofs+x*4+0] = src[0];
					dst[ofs+x*4+1] = src[0];
					dst[ofs+x*4+2] = src[0];
					dst[ofs+x*4+3] = src[1];
					src += 2;
				}
                ofs += llen;
            }
            dst += tw*bpp/8;
        }
        dst += llen*(th-1);
    }

	save_png(name, format, bpp/4, texbuff, llen, width, height, NULL, 0);
}


void RGB565_to_png(char *name, u8 *src, int width, int height, char *plt, int ptype, int entry)
{
	u8 *dst = texbuff;
	int h, v, x, y, ofs;

	int tw=4, th=4, bpp=24;
	int format = PNG_COLOR_TYPE_RGB;
	int llen = ((width+tw-1)&~(tw-1))*3;

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					dst[ofs+x*3+0] = src[0]&0xf8;
					dst[ofs+x*3+1] = ((src[0]&0x07)<<5) | (src[1]&0xe0)>>3;
					dst[ofs+x*3+2] = (src[1]&0x1f)<<3;
					src += 2;
				}
                ofs += llen;
            }
            dst += tw*bpp/8;
        }
        dst += llen*(th-1);
    }

	save_png(name, format, bpp/3, texbuff, llen, width, height, NULL, 0);
}

void RGB5A3_to_png(char *name, u8 *src, int width, int height, char *plt, int ptype, int entry)
{
	u8 *dst = texbuff;
	int h, v, x, y, ofs;

	int tw=4, th=4, bpp=32;
	int format = PNG_COLOR_TYPE_RGB_ALPHA;
	int llen = ((width+tw-1)&~(tw-1))*4;

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					if(src[0]&0x80){
						dst[ofs+x*4+0] = (src[0]&0x7c)<<1;
						dst[ofs+x*4+1] = ((src[0]&0x03)<<6) | (src[1]&0xe0)>>2;
						dst[ofs+x*4+2] = (src[1]&0x1f)<<3;
						dst[ofs+x*4+3] = 0xff;
					}else{
						dst[ofs+x*4+0] = (src[0]&0x0f)<<4;
						dst[ofs+x*4+1] = (src[1]&0xf0);
						dst[ofs+x*4+2] = (src[1]&0x0f)<<4;
						dst[ofs+x*4+3] = (src[0]&0xe0)<<1;
					}
					src += 2;
				}
                ofs += llen;
            }
            dst += tw*bpp/8;
        }
        dst += llen*(th-1);
    }

	save_png(name, format, bpp/4, texbuff, llen, width, height, NULL, 0);
}


void RGBA8_to_png(char *name, u8 *src, int width, int height, char *plt, int ptype, int entry)
{
	u8 *dst = texbuff;
	int h, v, x, y, ofs;

	int tw=4, th=4, bpp=32;
	int format = PNG_COLOR_TYPE_RGB_ALPHA;
	int llen = ((width+tw-1)&~(tw-1))*4;

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					dst[ofs+x*4+0] = src[1];
					dst[ofs+x*4+1] = src[32];
					dst[ofs+x*4+2] = src[33];
					dst[ofs+x*4+3] = src[0];
					src += 2;
				}
                ofs += llen;
            }
            dst += tw*bpp/8;
			src += 32;
        }
        dst += llen*(th-1);
    }

	save_png(name, format, bpp/4, texbuff, llen, width, height, NULL, 0);
}

u32 (*tlut_unpack[]) (u32 c) =
{
	color_unpack_ia8,
	color_unpack_rgb565,
	color_unpack_rgb5a3,
};

void plt_to_rgba(char *plt, int ptype, int entry)
{
	int i;
	u8 *dst = (u8*)pltbuff;
	u16 *src = (u16*)plt;
	u32 color;

	ptype &= 0x03;

	for(i=0; i<entry; i++){
		color = tlut_unpack[ptype](BE16(src[i]));
		dst[i*4+0] = (color>>16)&0xff;
		dst[i*4+1] = (color>> 8)&0xff;
		dst[i*4+2] = (color>> 0)&0xff;
		dst[i*4+3] = (color>>24)&0xff;
	}
}

void CI4_to_png(char *name, u8 *src, int width, int height, char *plt, int ptype, int entry)
{
	u8 *dst = texbuff;
	int h, v, x, y, ofs;

	int tw=8, th=8, bpp=4;
	int format = PNG_COLOR_TYPE_PALETTE;
	int llen = ((width+tw-1)&~(tw-1))/2;

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=2){
					dst[ofs+x/2] = *src++;
				}
                ofs += llen;
            }
            dst += tw*bpp/8;
        }
        dst += llen*(th-1);
    }

	plt_to_rgba(plt, ptype, entry);

	save_png(name, format, bpp, texbuff, llen, width, height, pltbuff, entry);
}

void CI8_to_png(char *name, u8 *src, int width, int height, char *plt, int ptype, int entry)
{
	u8 *dst = texbuff;
	int h, v, x, y, ofs;

	int tw=8, th=4, bpp=8;
	int format = PNG_COLOR_TYPE_PALETTE;
	int llen = ((width+tw-1)&~(tw-1));

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					dst[ofs+x] = *src++;
				}
                ofs += llen;
            }
            dst += tw*bpp/8;
        }
        dst += llen*(th-1);
    }

	plt_to_rgba(plt, ptype, entry);

	save_png(name, format, bpp, texbuff, llen, width, height, pltbuff, entry);
}

u32 icolor (u32 a, u32 b, u32 fa, u32 fb, u32 fc)
{
	u8 *aa = (u8 *) &a;
	u8 *bb = (u8 *) &b;
	u8 cc[4];
	int i;

	for (i = 0; i < 4; i++)
		cc[i] = ((u32) aa[i]*fa + (u32) bb[i]*fb) / fc;

	return (*(u32 *) cc);
}

void rgb32_cp(char *dst, char *src)
{
	dst[0] = src[2];
	dst[1] = src[1];
	dst[2] = src[0];
	dst[3] = src[3];
}

void CMP_to_png(char *name, u8 *src, int width, int height, char *plt, int ptype, int entry)
{
	char *dst = texbuff;
	int h, v, x, y, ofs;

	int tw=8, th=8, bpp=32;
	int format = PNG_COLOR_TYPE_RGB_ALPHA;
	int llen = ((width+tw-1)&~(tw-1))*4;

	int n;
	u32 rgb[4];
	char *cm;

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){

			for (y=0; y<th; y+=4){
				for (x=0; x<tw; x+=4){

					rgb[0] = color_unpack_rgb565((src[0]<<8)|src[1]);
					rgb[1] = color_unpack_rgb565((src[2]<<8)|src[3]);
					if(rgb[0]>rgb[1]){
						rgb[2] = icolor(rgb[0], rgb[1], 2, 1, 3);
						rgb[3] = icolor(rgb[0], rgb[1], 1, 2, 3);
					}else{
						rgb[2] = icolor(rgb[0], rgb[1], 1, 1, 2);
						rgb[3] = icolor(rgb[0], rgb[1], 1, 2, 3)&0x00ffffff;
					}

					cm = src+4;
					ofs = x;
					for(n=0; n<4; n++){
						rgb32_cp(dst+(ofs+0)*4, (char*)&rgb[(cm[n]&0xc0)>>6]);
						rgb32_cp(dst+(ofs+1)*4, (char*)&rgb[(cm[n]&0x30)>>4]);
						rgb32_cp(dst+(ofs+2)*4, (char*)&rgb[(cm[n]&0x0c)>>2]);
						rgb32_cp(dst+(ofs+3)*4, (char*)&rgb[(cm[n]&0x03)>>0]);
						ofs += llen/4;
					}
					src += 8;
				}
				dst += llen*4;
            }
			dst += tw*bpp/8 - llen*8;
        }
        dst += llen*(th-1);
    }

	save_png(name, format, bpp/4, texbuff, llen, width, height, NULL, 0);
}


////////////////////////////////////////////////////////////////////////////////////////////////

void (*tex_to_png[]) (char *name, u8 *src, int width, int height, char *plt, int ptype, int entry) =
{
	I4_to_png,        // 0
	I8_to_png,        // 1
	IA4_to_png,       // 2
	IA8_to_png,       // 3
	RGB565_to_png,    // 4
	RGB5A3_to_png,    // 5
	RGBA8_to_png,     // 6
	NULL,     // 7
	CI4_to_png,       // 8
	CI8_to_png,       // 9
	NULL,     // 10
	NULL,     // 11
	NULL,     // 12
	NULL,     // 13
	CMP_to_png,     // 14
	NULL,     // 15
};

////////////////////////////////////////////////////////////////////////////////////////////////


int tex0_index[65536];
int tex0_num;
int plt0_index[65536];
int plt0_num;

PLT0_section * find_plt(char *buf, char *fname)
{
	PLT0_section *plt;
	char *name;
	int i;

	for(i=0; i<plt0_num; i++){
		plt = (PLT0_section*)(buf+plt0_index[i]);
		name = (char*)(plt)+BE32(plt->name_offset);
		if(strcmp(name, fname)==0)
			return plt;
	}

	return NULL;
}

void brres_extract(char *buf)
{
	PLT0_section *plt;
	TEX0_section *tex;
	char *name;
	char *tex_buf, *plt_buf;
	int type, have_pal, width, height;
	int ptype, entry;
	int i;

	for(i=0; i<tex0_num; i++){
		tex = (TEX0_section*)(buf+tex0_index[i]);

		name = (char*)(tex)+BE32(tex->name_offset);
		type = BE32(tex->type);
		width = BE16(tex->width);
		height = BE16(tex->height);
		have_pal = BE32(tex->have_pal);
		tex_buf = (char*)(tex)+BE32(tex->data_offset);

		plt = find_plt(buf, name);
		if(plt){
			ptype = BE32(plt->type);
			entry = BE16(plt->entry_num);
			plt_buf = (char*)(plt)+BE32(plt->data_offset);
		}else{
			ptype = 0;
			entry = 0;
			plt_buf = NULL;
		}

		printf("%-16s : type %-16s  %3dx%3d ", name, color_type[type], width, height);
		if(plt){
			printf("  plt_type: %s\n", plt_type[ptype]);
		}else{
			printf("\n");
		}

		if (!tex_to_png[type]){
			continue;
		}
		tex_to_png[type] (name, tex_buf, width, height, plt_buf, ptype, entry);
	}
}

void scan_root(char *buf, int base, int end)
{
	DIRECTORY_desc *dir;
	OBJECT_desc *obj;
	SECTION_header *section;
	int i;

	int name_offset;
	int data_offset;

	dir = (DIRECTORY_desc*)(buf+base);
	obj = (OBJECT_desc *)(buf+base+sizeof(DIRECTORY_desc));

	for(i=0; i<BE32(dir->object_num); i++){
		name_offset = BE32(obj[i].name_offset)+base;
		data_offset = BE32(obj[i].data_offset)+base;

		if(data_offset<end){
			scan_root(buf, data_offset, end);
		}else{
			section = (SECTION_header*)(buf+data_offset);
			if(section->tag==0x30544c50){
				plt0_index[plt0_num] = data_offset;
				plt0_num++;
			}else if(section->tag==0x30584554){
				tex0_index[tex0_num] = data_offset;
				tex0_num++;
			}
		}
	}
}

void brres_scan(char *buf)
{
	BRRES_header *brres;
	SECTION_header *section;
	int end;

	brres = (BRRES_header*)buf;
	if(brres->tag!=0x73657262){
		printf("Not a brres file!\n");
		return;
	}

	tex0_num = 0;
	plt0_num = 0;

	section = (SECTION_header*)(buf+0x10);
	end = 0x10+BE32(section->size);

	scan_root(buf, 0x18, end);
}

int process_file(char *infname)
{
	FILE *fp;
	char *buf, *p;
	int size;
	BRRES_header *brres;


	fp = fopen(infname, "rb");
	if(fp==NULL){
		printf ("couldn't open file %s\n", infname);
		perror ("");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	buf = (char*)malloc(size);
	fread(buf, 1, size, fp);
	fclose(fp);

	brres = (BRRES_header*)buf;
	if(brres->tag!=0x73657262){
		goto _exit;
	}

	brres_scan(buf);
	if(tex0_num==0){
		goto _exit;
	}

	printf("process <%s> ...\n", infname);

	/* Make directory */
	strcpy(dname, infname);
	p = strchr(dname, '.');
	if(p)
		*p = '_';
	else
		strcat(dname, "_");
	mkdir(dname, 0777);

	brres_extract(buf);

_exit:
	free (buf);
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////

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

	printf("Enter directory <%s> ...\n", dname);
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

	printf("Leave directory <%s>\n\n", dname);
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

