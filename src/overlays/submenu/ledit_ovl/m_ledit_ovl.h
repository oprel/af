#ifndef M_LEDIT_OVL_H
#define M_LEDIT_OVL_H

#include "ultra64.h"
#include "unk.h"

struct Submenu;

typedef struct ledit_win_data_s {
    f32 edit_ofs[2];
    f32 edit_scale;
    f32 title_ofs[2];
    f32 title_scale;
    u8* title_str;
    s32 title_len;
    s32 edit_max;
    s32 edit_col_max;
    Color_RGBA8 edit_color;
    Gfx* gfx_mode;
    Gfx* gfx_model;
} mLE_win_data_c;

void mLE_ledit_ovl_construct(struct Submenu* submenu);
void mLE_ledit_ovl_destruct(struct Submenu* submenu);
void mLE_ledit_ovl_set_proc(struct Submenu* submenu);

#endif
