
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;


typedef struct {
	u32 tag;
	u32 endian;
	u32 file_size;
	u16 header_size;
	u16 section_num;
}BRRES_header;

typedef struct {
	u32 tag;
	u32 size;
}SECTION_header;

typedef struct {
	u32 size;
	u32 object_num;
	u32 unk0;
	u32 unk1;
	u32 unk2;
	u32 unk3;
}DIRECTORY_desc;

typedef struct {
	u16 unk0;
	u16 unk1;
	u16 unk2;
	u16 unk3;
	u32 name_offset;
	u32 data_offset;
}OBJECT_desc;

typedef struct {
	SECTION_header header;
	u32 unk0;
	u32 section_address;
	u32 data_offset;
	u32 name_offset;
	u32 type;
	u16 entry_num;
	u16 unk1;
	u32 unk2[8];
} PLT0_section;

typedef struct {
	SECTION_header header;
	u32 unk0;
	u32 section_address;
	u32 data_offset;
	u32 name_offset;
	u32 have_pal;
	u16 width;
	u16 height;
	u32 type;
	u32 unk1;
	u32 unk2[6];
}TEX0_section;

