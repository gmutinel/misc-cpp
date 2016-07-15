/*

unlzss 0.1
by Luigi Auriemma
e-mail: aluigi@autistici.org
web:    aluigi.org

implementation of the LZSS/LZ77 decompression algorithm

    Copyright 2007 Luigi Auriemma

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA

    http://www.gnu.org/licenses/gpl.txt
*/

//modified version for Tales Of Legendia
#include <stdint.h>
#include <string.h>



uint32_t unlzss(uint8_t *out, uint32_t outsz, uint8_t *in, uint32_t insz) {
    uint16_t    c,
                zg,
                i,
                num,
                e   = 0,
                zp  = 0xfee;
    uint8_t     zmem[0x1000],
                *p,
                *inx,
                *outx;

    p    = out;
    inx  = in  + insz;
    outx = out + outsz; 
    memset(zmem, 0x00, sizeof(zmem));

#define UNLZSS_CGET     if(in == inx) break;    \
                        c = *in++;
#define UNLZSS_CPUT     if(p == outx) break;    \
                        *p++ = c;
#define UNLZSS_ZGET     c = zmem[(zg + i) & 0xfff];
#define UNLZSS_ZPUT     zmem[zp] = c;           \
                        zp = (zp + 1) & 0xfff;

    for(;;) {
        for(;;) {
            e >>= 1;
            if(!((e >> 8) & 1)) {
                UNLZSS_CGET
                e = c | 0xff00;
            }
            if(!(e & 1)) break;

            UNLZSS_CGET
            UNLZSS_CPUT
            UNLZSS_ZPUT
        }

        UNLZSS_CGET
        zg  = c;
        UNLZSS_CGET
        zg |= (c & 0xf0) << 4;
        num = (c & 0x0f) + 2;

        for(i = 0; i <= num; i++) {
            UNLZSS_ZGET
            UNLZSS_CPUT
            UNLZSS_ZPUT
        }
    }

#undef UNLZSS_CGET
#undef UNLZSS_CPUT
#undef UNLZSS_ZGET
#undef UNLZSS_ZPUT

    return(p - out);
}


