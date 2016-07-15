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
#include "squish.h"

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



////////////////////////////////////////////////////////////////////////////////////////////////

int load_png(char *base_name, int *format, int *bpp, u8 *data, int *llen, int *width, int *height, u8 *plt, int *nplt)
{
	png_structp png_ptr;
	png_infop info_ptr, end_ptr;
	png_colorp pcolor;
	png_bytep *rows, ptrans;
	int i;

	char png_name[256];
	FILE *fp;

	sprintf(png_name, "%s/%s.png", dname, base_name);
	fp = fopen(png_name, "rb");
	if(fp==NULL){
		printf("Can't open %s!\n", png_name);
		return -1;
	}

	/* create info */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(png_ptr==NULL){
		printf("PNG error create png_ptr!\n");
		return -1;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr==NULL){
		printf("PNG error create info_ptr!\n");
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
		return -1;
	}

	end_ptr = png_create_info_struct(png_ptr);
	if(info_ptr==NULL){
		printf("PNG error create info_ptr!\n");
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
		return -1;
	}

	/* read info chunks */
	png_init_io(png_ptr, fp);
	png_read_info(png_ptr, info_ptr);

	/* read header */
	png_get_IHDR(png_ptr, info_ptr, (png_uint_32*)width, (png_uint_32*)height, bpp, format, NULL, NULL, NULL);

	if(*format==PNG_COLOR_TYPE_PALETTE) {
		/* read palette */
		png_get_PLTE(png_ptr, info_ptr, &pcolor, nplt);
		for(i=0; i<*nplt; i++){
			plt[i*4+0] = pcolor[i].red;
			plt[i*4+1] = pcolor[i].green;
			plt[i*4+2] = pcolor[i].blue;
			plt[i*4+3] = 0xff;
		}

		/* read alpha of palette */
		if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)){
			png_get_tRNS(png_ptr, info_ptr, (png_bytep*)&ptrans, NULL, NULL);
			for(i=0; i<*nplt; i++){
				plt[i*4+3] = ptrans[i];
			}
		}
	}else{
		*nplt = 0;
	}

	/* read image data */
	*llen = png_get_rowbytes(png_ptr, info_ptr);
	rows = (png_bytep*)malloc(*height*sizeof(char*));
	for(i=0; i<*height; i++){
		rows[i] = (png_bytep)(data+(*llen)*i);
	}
	png_read_image(png_ptr, rows);
	free(rows);

	png_read_end(png_ptr, info_ptr);
	png_destroy_read_struct(&png_ptr, &info_ptr, &end_ptr);

	return 0;
}

u8 fixbuff[1024*1024*4];

void fix_pitch(int llen, int pitch, int height)
{
	int v;
	u8 *dst = texbuff;
	u8 *src = fixbuff;

	if(llen==pitch)
		return;

	memcpy(fixbuff, texbuff, 1024*1024*4);
	memset(texbuff, 0, 1024*1024*4);

	for(v=0; v<height; v++){
		memcpy(dst, src, pitch);
		dst += llen;
		src += pitch;
	}

	return;
}

////////////////////////////////////////////////////////////////////////////////////////////////

int I4_from_png(char *name, u8 *dst, int width, int height, u8 *plt, int ptype, int entry)
{
	u8 *src = texbuff;
	int h, v, x, y, ofs;
	int retv;

	int tw=8, th=8, bpp=4;
	int format = PNG_COLOR_TYPE_GRAY;
	int llen = ((width+tw-1)&~(tw-1))/2;

	int pw, ph, pbpp, pformat, pitch, nplt;

	retv = load_png(name, &pformat, &pbpp, texbuff, &pitch, &pw, &ph, pltbuff, &nplt);
	if(retv){
		printf("Error loading %s!\n", name);
		return -1;
	}
	if(pformat!=format || pbpp!=bpp || pw!=width || ph!=height){
		printf("%s: wrong format! expect: format=%08x bpp=%d %dx%d\n", name, format, bpp, width, height);
		printf("                          read: format=%08x bpp=%d %dx%d\n", pformat, pbpp, pw, ph);
		return -1;
	}
	if(entry!=nplt){
		printf("%s: wrong palete entrys! entry=%d read=%d\n", name, entry, nplt);
		return -1;
	}

	fix_pitch(llen, pitch, height);

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=2){
					*dst++ = src[ofs+x/2];
				}
                ofs += llen;
            }
            src += tw*bpp/8;
        }
        src += llen*(th-1);
    }

	return 0;
}

int I8_from_png(char *name, u8 *dst, int width, int height, u8 *plt, int ptype, int entry)
{
	u8 *src = texbuff;
	int h, v, x, y, ofs;
	int retv;

	int tw=8, th=4, bpp=8;
	int format = PNG_COLOR_TYPE_GRAY;
	int llen = ((width+tw-1)&~(tw-1));

	int pw, ph, pbpp, pformat, pitch, nplt;

	retv = load_png(name, &pformat, &pbpp, texbuff, &pitch, &pw, &ph, pltbuff, &nplt);
	if(retv){
		printf("Error loading %s!\n", name);
		return -1;
	}
	if(pformat!=format || pbpp!=bpp || pw!=width || ph!=height){
		printf("%s: wrong format! expect: format=%08x bpp=%d %dx%d\n", name, format, bpp, width, height);
		printf("                          read: format=%08x bpp=%d %dx%d\n", pformat, pbpp, pw, ph);
		return -1;
	}
	if(entry!=nplt){
		printf("%s: wrong palete entrys! entry=%d read=%d\n", name, entry, nplt);
		return -1;
	}

	fix_pitch(llen, pitch, height);

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					*dst++ = src[ofs+x];
				}
                ofs += llen;
            }
            src += tw*bpp/8;
        }
        src += llen*(th-1);
    }

	return 0;
}

int IA4_from_png(char *name, u8 *dst, int width, int height, u8 *plt, int ptype, int entry)
{
	u8 *src = texbuff;
	int h, v, x, y, ofs;
	int retv;

	int tw=8, th=4, bpp=32;
	int format = PNG_COLOR_TYPE_RGB_ALPHA;
	int llen = ((width+tw-1)&~(tw-1))*4;

	int pw, ph, pbpp, pformat, pitch, nplt;

	retv = load_png(name, &pformat, &pbpp, texbuff, &pitch, &pw, &ph, pltbuff, &nplt);
	if(retv){
		printf("Error loading %s!\n", name);
		return -1;
	}
	if(pformat!=format || (pbpp*4)!=bpp || pw!=width || ph!=height){
		printf("%s: wrong format! expect: format=%08x bpp=%d %dx%d\n", name, format, bpp, width, height);
		printf("                          read: format=%08x bpp=%d %dx%d\n", pformat, pbpp*4, pw, ph);
		return -1;
	}
	if(entry!=nplt){
		printf("%s: wrong palete entrys! entry=%d read=%d\n", name, entry, nplt);
		return -1;
	}

	fix_pitch(llen, pitch, height);

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					dst[0]  = (src[ofs+x*4+0]&0xf0)>>4;
					dst[0] |= (src[ofs+x*4+3]&0xf0);
					dst++;
				}
                ofs += llen;
            }
            src += tw*bpp/8;
        }
        src += llen*(th-1);
    }

	return 0;
}

int IA8_from_png(char *name, u8 *dst, int width, int height, u8 *plt, int ptype, int entry)
{
	u8 *src = texbuff;
	int h, v, x, y, ofs;
	int retv;

	int tw=4, th=4, bpp=32;
	int format = PNG_COLOR_TYPE_RGB_ALPHA;
	int llen = ((width+tw-1)&~(tw-1))*4;

	int pw, ph, pbpp, pformat, pitch, nplt;

	retv = load_png(name, &pformat, &pbpp, texbuff, &pitch, &pw, &ph, pltbuff, &nplt);
	if(retv){
		printf("Error loading %s!\n", name);
		return -1;
	}
	if(pformat!=format || (pbpp*4)!=bpp || pw!=width || ph!=height){
		printf("%s: wrong format! expect: format=%08x bpp=%d %dx%d\n", name, format, bpp, width, height);
		printf("                          read: format=%08x bpp=%d %dx%d\n", pformat, pbpp*4, pw, ph);
		return -1;
	}
	if(entry!=nplt){
		printf("%s: wrong palete entrys! entry=%d read=%d\n", name, entry, nplt);
		return -1;
	}

	fix_pitch(llen, pitch, height);

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					dst[0]  = src[ofs+x*4+0];
					dst[1] |= src[ofs+x*4+3];
					dst += 2;
				}
                ofs += llen;
            }
            src += tw*bpp/8;
        }
        src += llen*(th-1);
    }

	return 0;
}

int RGB565_from_png(char *name, u8 *dst, int width, int height, u8 *plt, int ptype, int entry)
{
	u8 *src = texbuff;
	int h, v, x, y, ofs;
	int retv;

	int tw=4, th=4, bpp=24;
	int format = PNG_COLOR_TYPE_RGB;
	int llen = ((width+tw-1)&~(tw-1))*3;

	int pw, ph, pbpp, pformat, pitch, nplt;

	retv = load_png(name, &pformat, &pbpp, texbuff, &pitch, &pw, &ph, pltbuff, &nplt);
	if(retv){
		printf("Error loading %s!\n", name);
		return -1;
	}
	if(pformat!=format || (pbpp*3)!=bpp || pw!=width || ph!=height){
		printf("%s: wrong format! expect: format=%08x bpp=%d %dx%d\n", name, format, bpp, width, height);
		printf("                          read: format=%08x bpp=%d %dx%d\n", pformat, pbpp*3, pw, ph);
		return -1;
	}
	if(entry!=nplt){
		printf("%s: wrong palete entrys! entry=%d read=%d\n", name, entry, nplt);
		return -1;
	}

	fix_pitch(llen, pitch, height);

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					u32 r = src[ofs+x*3+0];
					u32 g = src[ofs+x*3+1];
					u32 b = src[ofs+x*3+2];
					dst[0] = (r&0xf8) | ((g>>5)&0x07);
					dst[1] = ((g<<3)&0xe0) | ((b>>3)&0x1f);
					dst += 2;
				}
                ofs += llen;
            }
            src += tw*bpp/8;
        }
        src += llen*(th-1);
    }

	return 0;
}

int RGB5A3_from_png(char *name, u8 *dst, int width, int height, u8 *plt, int ptype, int entry)
{
	u8 *src = texbuff;
	int h, v, x, y, ofs;
	int retv;

	int tw=4, th=4, bpp=32;
	int format = PNG_COLOR_TYPE_RGB_ALPHA;
	int llen = ((width+tw-1)&~(tw-1))*4;

	int pw, ph, pbpp, pformat, pitch, nplt;

	retv = load_png(name, &pformat, &pbpp, texbuff, &pitch, &pw, &ph, pltbuff, &nplt);
	if(retv){
		printf("Error loading %s!\n", name);
		return -1;
	}
	if(pformat!=format || (pbpp*4)!=bpp || pw!=width || ph!=height){
		printf("%s: wrong format! expect: format=%08x bpp=%d %dx%d\n", name, format, bpp, width, height);
		printf("                          read: format=%08x bpp=%d %dx%d\n", pformat, pbpp*4, pw, ph);
		return -1;
	}
	if(entry!=nplt){
		printf("%s: wrong palete entrys! entry=%d read=%d\n", name, entry, nplt);
		return -1;
	}

	fix_pitch(llen, pitch, height);

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					u32 r = src[ofs+x*4+0];
					u32 g = src[ofs+x*4+1];
					u32 b = src[ofs+x*4+2];
					u32 a = src[ofs+x*4+3];
					if(a==0xff){
						dst[0] = 0x80 | ((r&0xf8)>>1) | ((g>>6)&0x03);
						dst[1] = ((g&0x38)<<2) | ((b&0xf8)>>3);
					}else{
						dst[0] = (r>>4) | ((a&0xe0)>>1);
						dst[1] = (g&0xf0) | (b>>4);
					}
					dst += 2;
				}
                ofs += llen;
            }
            src += tw*bpp/8;
        }
        src += llen*(th-1);
    }

	return 0;
}

int RGBA8_from_png(char *name, u8 *dst, int width, int height, u8 *plt, int ptype, int entry)
{
	u8 *src = texbuff;
	int h, v, x, y, ofs;
	int retv;

	int tw=4, th=4, bpp=32;
	int format = PNG_COLOR_TYPE_RGB_ALPHA;
	int llen = ((width+tw-1)&~(tw-1))*4;

	int pw, ph, pbpp, pformat, pitch, nplt;

	retv = load_png(name, &pformat, &pbpp, texbuff, &pitch, &pw, &ph, pltbuff, &nplt);
	if(retv){
		printf("Error loading %s!\n", name);
		return -1;
	}
	if(pformat!=format || (pbpp*4)!=bpp || pw!=width || ph!=height){
		printf("%s: wrong format! expect: format=%08x bpp=%d %dx%d\n", name, format, bpp, width, height);
		printf("                          read: format=%08x bpp=%d %dx%d\n", pformat, pbpp*4, pw, ph);
		return -1;
	}
	if(entry!=nplt){
		printf("%s: wrong palete entrys! entry=%d read=%d\n", name, entry, nplt);
		return -1;
	}

	fix_pitch(llen, pitch, height);

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					dst[ 1] = src[ofs+x*4+0];
					dst[32] = src[ofs+x*4+1];
					dst[33] = src[ofs+x*4+2];
					dst[ 0] = src[ofs+x*4+3];
					dst += 2;
				}
                ofs += llen;
            }
            src += tw*bpp/8;
			dst += 32;
        }
        src += llen*(th-1);
    }

	return 0;
}



// RGB565: rrrr rggg gggb bbbb
u32 color_pack_rgb565 (u32 X)
{
	return ((X>>8)&0xf800) | ((X>>5)&0x07e0) | ((X>>3)&0x001f);
}

//RGB555: 1rrr rrgg gggb bbbb
u32 color_pack_rgb555 (u32 X)
{
	return ((X>>9)&0x7c00) | ((X>>6)&0x03e0) | ((X>>3)&0x001f) | 0x8000;
}

// RGB4A3  0aaa rrrr gggg bbbb
u32 color_pack_rgb4a3 (u32 X)
{
	return ((X>>12)&0x0f00) | ((X>>8)&0x00f0) | ((X>>4)&0x000f) | ((X>>17)&0x7000);
}

u32 color_pack_rgb5a3 (u32 X)
{
	u32 a = X>>24;
	if(a==0xff)
		return color_pack_rgb555(X);
	else
		return color_pack_rgb4a3(X);
}

//IA8: aa ii
u32 color_pack_ia8 (u32 X)
{
	return (X>>16)&0xffff;
}

u32 (*tlut_pack[]) (u32 c) =
{
	color_pack_ia8,
	color_pack_rgb565,
	color_pack_rgb5a3,
};

void plt_from_rgba(u8 *plt, int ptype, int entry)
{
	int i;
	u8 *src = (u8*)pltbuff;
	u16 *dst = (u16*)plt;
	u32 color, r, g, b, a;

	ptype &= 0x03;

	for(i=0; i<entry; i++){
		r = src[i*4+0];
		g = src[i*4+1];
		b = src[i*4+2];
		a = src[i*4+3];
		color = (a<<24) | (r<<16) | (g<<8) | b;
		color = tlut_pack[ptype](color);
		color = BE16(color);
		dst[i] = color;
	}
}


int CI4_from_png(char *name, u8 *dst, int width, int height, u8 *plt, int ptype, int entry)
{
    u8 *src = texbuff;
    int h, v, x, y, ofs;
    int retv;

    int tw=8, th=8, bpp=4;
    int format = PNG_COLOR_TYPE_PALETTE;
    int llen = ((width+tw-1)&~(tw-1))/2;

    int pw, ph, pbpp, pformat, pitch, nplt;

    retv = load_png(name, &pformat, &pbpp, texbuff, &pitch, &pw, &ph, pltbuff, &nplt);
    if(retv){
        printf("Error loading %s!\n", name);
        return -1;
    }
    if(pformat!=format || pbpp!=bpp || pw!=width || ph!=height){
        printf("%s: wrong format! expect: format=%08x bpp=%d %dx%d\n", name, format, bpp, width, height);
        printf("                          read: format=%08x bpp=%d %dx%d\n", pformat, pbpp, pw, ph);
        return -1;
    }
    if(entry!=nplt){
        printf("%s: wrong palete entrys! entry=%d read=%d\n", name, entry, nplt);
        return -1;
    }

	fix_pitch(llen, pitch, height);

    for(v=0; v<height; v+=th){
        for(h=0; h<width; h+=tw){
            for (y=0,ofs=0; y<th; y++){
                for (x=0; x<tw; x+=2){
                    *dst++ = src[ofs+x/2];
                }
                ofs += llen;
            }
            src += tw*bpp/8;
        }
        src += llen*(th-1);
    }

	plt_from_rgba(plt, ptype, entry);

	return 0;
}

int CI8_from_png(char *name, u8 *dst, int width, int height, u8 *plt, int ptype, int entry)
{
	u8 *src = texbuff;
	int h, v, x, y, ofs;
	int retv;

	int tw=8, th=4, bpp=8;
	int format = PNG_COLOR_TYPE_PALETTE;
	int llen = ((width+tw-1)&~(tw-1));

	int pw, ph, pbpp, pformat, pitch, nplt;

	retv = load_png(name, &pformat, &pbpp, texbuff, &pitch, &pw, &ph, pltbuff, &nplt);
	if(retv){
		printf("Error loading %s!\n", name);
		return -1;
	}
	if(pformat!=format || pbpp!=bpp || pw!=width || ph!=height){
		printf("%s: wrong format! expect: format=%08x bpp=%d %dx%d\n", name, format, bpp, width, height);
		printf("                          read: format=%08x bpp=%d %dx%d\n", pformat, pbpp, pw, ph);
		return -1;
	}
	if(entry!=nplt){
		printf("%s: wrong palete entrys! entry=%d read=%d\n", name, entry, nplt);
		return -1;
	}

	fix_pitch(llen, pitch, height);

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){
			for (y=0,ofs=0; y<th; y++){
				for (x=0; x<tw; x+=1){
					*dst++ = src[ofs+x];
				}
                ofs += llen;
            }
            src += tw*bpp/8;
        }
        src += llen*(th-1);
    }

	plt_from_rgba(plt, ptype, entry);

	return 0;
}

u8 brev(u8 data)
{
	return ((data>>6)&0x03) | ((data>>2)&0x0c) | ((data<<2)&0x30) | ((data<<6)&0xc0) ;
}

int CMP_from_png(char *name, u8 *dst, int width, int height, u8 *plt, int ptype, int entry)
{
    u8 *src = texbuff;
    int h, v, x, y, ofs;
    int retv;

    int tw=8, th=8, bpp=32;
    int format = PNG_COLOR_TYPE_RGB_ALPHA;
    int llen = ((width+tw-1)&~(tw-1))*4;

    int pw, ph, pbpp, pformat, pitch, nplt;

    retv = load_png(name, &pformat, &pbpp, texbuff, &pitch, &pw, &ph, pltbuff, &nplt);
    if(retv){
        printf("Error loading %s!\n", name);
        return -1;
    }
    if(pformat!=format || (pbpp*4)!=bpp || pw!=width || ph!=height){
        printf("%s: wrong format! expect: format=%08x bpp=%d %dx%d\n", name, format, bpp, width, height);
        printf("                          read: format=%08x bpp=%d %dx%d\n", pformat, pbpp*4, pw, ph);
        return -1;
    }
    if(entry!=nplt){
        printf("%s: wrong palete entrys! entry=%d read=%d\n", name, entry, nplt);
        return -1;
    }

    fix_pitch(llen, pitch, height);

	u8 pbuf[16*4];
	u8 block[8];
	int n;

	for(v=0; v<height; v+=th){
		for(h=0; h<width; h+=tw){

			for (y=0; y<th; y+=4){
				for (x=0,ofs=0; x<tw; x+=4){

					for(n=0; n<4; n++){
						memcpy(pbuf+n*16, src+ofs+n*llen, 16);
					}
					Compress(pbuf, block, squish::kDxt1);

					dst[0] = block[1];
					dst[1] = block[0];
					dst[2] = block[3];
					dst[3] = block[2];
					dst[4] = brev(block[4]);
					dst[5] = brev(block[5]);
					dst[6] = brev(block[6]);
					dst[7] = brev(block[7]);

					dst += 8;
					ofs += 16;
				}
				src += llen*4;
            }
			src += tw*bpp/8 - llen*8;
        }
        src += llen*(th-1);
    }

	return 0;
}

#if 0
#endif

////////////////////////////////////////////////////////////////////////////////////////////////

int (*tex_from_png[]) (char *name, u8 *src, int width, int height, u8 *plt, int ptype, int entry) =
{
	I4_from_png,        // 0
	I8_from_png,        // 1
	IA4_from_png,       // 2
	IA8_from_png,       // 3
	RGB565_from_png,    // 4
	RGB5A3_from_png,    // 5
	RGBA8_from_png,     // 6
	NULL,     // 7
	CI4_from_png,        // 8
	CI8_from_png,        // 9
	NULL,     // 10
	NULL,     // 11
	NULL,     // 12
	NULL,     // 13
	CMP_from_png,       // 14
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

int brres_import(char *buf)
{
	PLT0_section *plt;
	TEX0_section *tex;
	char *name;
	u8 *tex_buf, *plt_buf;
	int type, have_pal, width, height;
	int ptype, entry;
	int i, retv, imports;

	imports = 0;

	for(i=0; i<tex0_num; i++){
		tex = (TEX0_section*)(buf+tex0_index[i]);

		name = (char*)(tex)+BE32(tex->name_offset);
		type = BE32(tex->type);
		width = BE16(tex->width);
		height = BE16(tex->height);
		have_pal = BE32(tex->have_pal);
		tex_buf = (u8*)(tex)+BE32(tex->data_offset);

		plt = find_plt(buf, name);
		if(plt){
			ptype = BE32(plt->type);
			entry = BE16(plt->entry_num);
			plt_buf = (u8*)(plt)+BE32(plt->data_offset);
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

		if (!tex_from_png[type]){
			continue;
		}
		retv = tex_from_png[type] (name, tex_buf, width, height, plt_buf, ptype, entry);
		if(retv==0)
			imports++;
	}

	return imports;
}

void scan_root(char *buf, int base, int end)
{
	DIRECTORY_desc *dir;
	OBJECT_desc *obj;
	SECTION_header *section;
	u32 i;

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

	if(brres_import(buf)){
		fp = fopen(infname, "wb");
		fwrite(buf, 1, size, fp);
		fclose(fp);
	}

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


