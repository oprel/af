#ifndef tag_ovl_H
#define tag_ovl_H

#include "ultra64.h"
#include "unk.h"

#define TAG_STR0_LEN 10 //originally 10
#define TAG_STR1_LEN 6 //originally 6

#define TAG_ITEM_STR_LEN 16 //str0 + str1

#define CHAR_SPACE 32

typedef enum mTG_Table {
    /*  0 */ mTG_TABLE_ITEM,
    /*  1 */ mTG_TABLE_MAIL,
    /*  2 */ mTG_TABLE_MONEY,
    /*  3 */ mTG_TABLE_PLAYER,
    /*  4 */ mTG_TABLE_BG,
    /*  5 */ mTG_TABLE_MBOX,
    /*  6 */ mTG_TABLE_HANIWA,
    /*  7 */ mTG_TABLE_COLLECT,
    /*  8 */ mTG_TABLE_WCHANGE,
    /*  9 */ mTG_TABLE_CPMAIL,
    /* 15 */ mTG_TABLE_CATALOG_WC = 15
} mTG_Table;
 

typedef enum mTG_QstrType {
    /* 0 */ mTG_QSTR_TYPE_NONE,
    /* 1 */ mTG_QSTR_TYPE_ITEM,
    /* 2 */ mTG_QSTR_TYPE_MAIL,
    /* 3 */ mTG_QSTR_TYPE_FROM_MUSEUM,
    /* 4 */ mTG_QSTR_TYPE_TO_MUSEUM,
    /* 5 */ mTG_QSTR_TYPE_XMAS_SNOWMAN_SPNPC,
    /* 6 */ mTG_QSTR_TYPE_SHOP,
    /* 7 */ mTG_QSTR_TYPE_MOTHER,
    /* 8 */ mTG_QSTR_TYPE_ANGLER,
    /* 9 */ mTG_QSTR_TYPE_OMIKUJI
} mTG_QstrType;

// size = 0x54
typedef struct mTG_tag_c {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 arrowDir;  // 0 = none, 1 = right, 2 = left (confirmed values)
    /* 0x02 */ u8 str2Type;  // mTG_QstrType
    /* 0x03 */ u8 flags;
    /* 0x04 */ f32 unk_04[2];
    /* 0x0C */ f32 basePos[2];
    /* 0x14 */ f32 bodyScale[2];
    /* 0x1C */ f32 arrowScale[2];
    /* 0x24 */ f32 bodyOfs[2]; 
    /* 0x2C */ f32 textOfs[2];
    /* 0x34 */ s32 table; // mTG_Table
    /* 0x38 */ s32 tagCol;
    /* 0x3C */ s32 tagRow;
    /* 0x40 */ f32 scale;
    /* 0x44 */ u8 str0[TAG_STR0_LEN];
    /* 0x4E */ u8 str1[TAG_STR1_LEN];
} mTG_tag_c; // size = 0x54

typedef struct mTG_win_data_c{
    /* 0x00 */ f32 unk_00[2];
    /* 0x08 */ f32 unk_08[2];
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s32 minWidth;
    /* 0x18 */ s32 widthRange;
    /* 0x1C */ f32 unk_1C[2];
    /* 0x24 */ f32 unk_24[2];
    /* 0x2C */ f32 unk_2C[2];
    /* 0x34 */ f32 unk_34[2];
    /* 0x3C */ f32 unk_3C;
} mTG_win_data_c; // size = 0x40

typedef struct mTG_SetCharMatrixView{
    u8 unk_0000[0x6B4];
    void (*set_char_matrix_proc)(void*);
} mTG_SetCharMatrixView;

struct Submenu;

void mTG_tag_ovl_construct(struct Submenu* submenu);
void mTG_tag_ovl_destruct(struct Submenu* submenu);

void func_8086FD3C_jp(struct Submenu* submenu);

#endif
