#include "global.h"
#include "mED_editor_ovl.h"
#include "m_mail.h"


#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885140_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808851D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_8088537C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808854CC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885530_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808855DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885608_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885690_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808857F8_jp.s")

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/mEditor_init.s")
//*
extern s16 mED_edit_line[];

void mEditor_init(Submenu* submenu, u8* menu) {
    struct editor_ovl_s* edit_ovl = *(struct editor_ovl_s**)((u8*)submenu->overlay + 0x106E0);

    edit_ovl->stick_area = 8;
    edit_ovl->last_stick_area = 8;
    edit_ovl->stick_area_changed = 0;

    edit_ovl->shift_mode = 0;
    edit_ovl->page_top_num = 0;
    edit_ovl->consonant_num = -1;
    edit_ovl->command = 0;
    edit_ovl->output_code = 0;
    edit_ovl->anim_frame = 0;
    edit_ovl->max_line = mED_edit_line[*(s32*)(menu + 0x38)];
    edit_ovl->input_str = *(char**)(menu + 0x40);

    if (*(s32*)(menu + 0x3C) > 0) {
        edit_ovl->max_col = *(s32*)(menu + 0x3C);
        edit_ovl->input_num = mMl_strlen(edit_ovl->input_str, edit_ovl->max_col * edit_ovl->max_line, ' ');
    } else if (*(s32*)(menu + 0x38) == 0) {
        edit_ovl->max_col = 16;
        edit_ovl->input_num = *(u8*)(*(u8**)((u8*)submenu->overlay + 0x106E4) + 6);
    }

    edit_ovl->cursor_idx = 0;
#if 1
    //temporary hack to make character set start at ABC's
    //can't be defined where shift_mode is set to 0, because it causes overlay errors and mismatched instruction counts
    edit_ovl->shift_mode = 3;
#else
    edit_ovl->cursor_col = 0;
    edit_ovl->cursor_row = 0;
#endif
    edit_ovl->exchange_code = -1;
}
//*/

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_8088596C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885A74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885AEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885CBC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885D2C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885D94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885DD4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885EC8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885F4C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885F6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80885FCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808860A0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808860FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80886168_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808861AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808861E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808862EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808863B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80886490_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80886588_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80886674_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808866F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80886724_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_808869C0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/mED_editor_ovl_move.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/mED_editor_draw_init.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80886C78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80886CC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80887768_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_8088798C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80887A78_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80887BF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80887D5C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80887DF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80887F48_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/func_80888024_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/mED_endCode_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/mED_cursol_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/mED_editor_ovl_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/mED_editor_ovl_set_proc.s")

typedef void (*mEDMoveChgBaseProc)(void* menu, s32 move_type);

void mED_editor_ovl_init(Submenu* submenu) {
    u8* menu = (u8*)submenu->overlay + 0x10358;

    (*(mEDMoveChgBaseProc*)((u8*)submenu->overlay + 0x106B0))(menu, 7);

    switch (*(s32*)(menu + 0x38)) {
        case mED_TYPE_CP_TITLE:
        case mED_TYPE_LEDIT:
        case mED_TYPE_HBOARD:
            sAdo_SysTrgStart(0x59);
            break;
    }
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/mED_editor_ovl_construct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/editor_ovl/mED_editor_ovl/mED_editor_ovl_destruct.s")
