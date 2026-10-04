#include "global.h"
#include "m_tag_ovl.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "m_item_name.h"
#include "m_mail.h"
#include "m_npc.h"
#include "m_private.h"
#include "m_submenu.h"
#include "overlays/submenu/submenu_ovl/m_submenu_ovl.h"


#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086F310_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086F35C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086F44C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086F4AC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086F644_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086F66C_jp.s")

//#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086F764_jp.s")

extern mTG_win_data_c D_8087907C_jp[];

//mTG_set_tag_win_scale_p
void func_8086F764_jp(mTG_tag_c* tag, s32 win_type, s32 width, s32 height) {
    mTG_win_data_c* win_data = &D_8087907C_jp[win_type];
    int i;

    tag->unk_04[0] = (f32)(width - win_data->minWidth) / (f32)win_data->widthRange;

    if (height != 0) {
        tag->unk_04[1] = (f32)(height - 2) / 3.0f;
    } else {
        tag->unk_04[1] = tag->unk_04[0];
    }

    for (i = 0; i < 2; i++) {
        tag->bodyScale[i] = win_data->unk_00[i] + tag->unk_04[i] * (1.0f - win_data->unk_00[i]);
        tag->arrowScale[i] = win_data->unk_10 + tag->unk_04[i] * (1.0f - win_data->unk_10);
        tag->textOfs[i] = win_data->unk_1C[i] + win_data->unk_24[i] * tag->unk_04[i] +
                          win_data->unk_08[i] * tag->bodyScale[i];
        tag->bodyOfs[i] = (win_data->unk_34[i] + win_data->unk_2C[i] * tag->unk_04[i]) -
                          win_data->unk_08[i] * tag->bodyScale[i];
    }

    tag->bodyOfs[1] += tag->arrowScale[1] * 0.5f * win_data->unk_3C;
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086F910_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086F960_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086F9D8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086FA30_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086FA88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086FB04_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086FB9C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086FBE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086FCF4_jp.s")

//#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8086FD3C_jp.s")


/* .data / .rodata, not decompiled yet */
extern u8 D_8087913C_jp[5]; /* "Present" (5 bytes) */
extern u8 D_80879144_jp[2]; /* mother mail sender name (2 bytes) */
extern u8 D_80879148_jp[][6]; /* catalog category names, 6 bytes each */


/* struct_8085E9B0 (submenu->unk_2C) isn't decompiled far enough yet, so use raw offsets at the use sites. */
typedef u16 (*SetCollectItemNoProc)(s32 idx, s32 pageOrder);

//mTG_init_tag_data_item_win
void func_8086FD3C_jp(Submenu* submenu) {
    mTG_tag_c* tag = (mTG_tag_c*)(*(u8**)((u8*)submenu->unk_2C + 0x106D0) + 0x8);
    u16 itemNo = 0;
    Mail_c* mail = NULL;
    s32 itemCond = mPr_ITEM_COND_NORMAL;
    s32 idx = func_8086F910_jp(tag);
    s32 width;
    s32 width1;
 
    func_8086F35C_jp(submenu, tag->basePos, tag->table, idx);
    mem_clear(tag->str0, TAG_STR0_LEN, CHAR_SPACE);
    mem_clear(tag->str1, TAG_STR1_LEN, CHAR_SPACE);
 
    /* == mTG_init_tag_data_set_itemNo() */
    switch (tag->table) {
        case mTG_TABLE_ITEM:
            itemNo = COMMON_GET(privateInfo)->inventory.pockets[idx];
            itemCond = mPr_GET_ITEM_COND(COMMON_GET(privateInfo)->inventory.item_conditions, idx);
            break;
 
        case mTG_TABLE_PLAYER:
            itemNo = *(u16*)((u8*)common_data.privateInfo + 0x3EC);
            break;
 
        case mTG_TABLE_HANIWA: {
            u8* menuInfo = (u8*)submenu->unk_2C + 0x10478;
            itemNo = SAVE_GET(homes)[*(s32*)(menuInfo + 0x3C)].haniwa.items[idx].item;
            break;
        }
 
        case mTG_TABLE_COLLECT: {
            u8* inventoryOvl = *(u8**)((u8*)submenu->unk_2C + 0x106DC);
 
            itemNo = (*(SetCollectItemNoProc*)(inventoryOvl + 0x5D8))(
                idx, *(u8*)(inventoryOvl + 0x3EE));
            break;
        }
 
        case mTG_TABLE_MAIL:
        case mTG_TABLE_MBOX:
        case mTG_TABLE_CPMAIL:
            mail = func_8086FBE4_jp(submenu, NULL);
            break;
 
        default:
            break;
    }
 
    if (itemNo != 0 || (mail != NULL && mMl_check_not_used_mail(mail) == FALSE)) {
        /* == mTG_init_tag_data_item_win_sub_mail_item() */
        if (itemNo == 0) {
            /* A letter: str0 = recipient, str1 = sender (or a special sender) */
            mem_copy(tag->str0, (u8*)mail->header.recipient.personalID.playerName, PLAYER_NAME_LEN);
 
            if (mail->content.mailType == 0) {
                mem_copy(tag->str1, (u8*)mail->header.sender.personalID.playerName, PLAYER_NAME_LEN);
 
                if (mail->header.recipient.type == 2) {
                    tag->str2Type = mTG_QSTR_TYPE_TO_MUSEUM;
                } else if (mail->header.sender.type == 2) {
                    tag->str2Type = mTG_QSTR_TYPE_FROM_MUSEUM;
                } else {
                    tag->str2Type = mTG_QSTR_TYPE_MAIL;
                }
            } else if (mail->content.mailType == 1) {
                tag->str2Type = mTG_QSTR_TYPE_XMAS_SNOWMAN_SPNPC;
                mNpc_GetNpcWorldNameP((char*)tag->str1, 0xD00F);
            } else if (mail->content.mailType == 2 || mail->content.mailType == 7) {
                tag->str2Type = mTG_QSTR_TYPE_SHOP;
                mNpc_GetNpcWorldNameP((char*)tag->str1, 0xD008);
            } else if (mail->content.mailType == 3) {
                tag->str2Type = mTG_QSTR_TYPE_SHOP;
                mNpc_GetNpcWorldNameP((char*)tag->str1, 0xD001);
            } else if (mail->content.mailType == 4) {
                tag->str2Type = mTG_QSTR_TYPE_MOTHER;
                mem_copy(tag->str1, D_80879144_jp, sizeof(D_80879144_jp));
            } else if (mail->content.mailType == 5) {
                tag->str2Type = mTG_QSTR_TYPE_ANGLER;
                mNpc_GetNpcWorldNameP((char*)tag->str1, 0xD03D);
            } else if (mail->content.mailType == 8) {
                tag->str2Type = mTG_QSTR_TYPE_XMAS_SNOWMAN_SPNPC;
                mNpc_GetNpcWorldNameP((char*)tag->str1, 0x800D);
            } else {
                tag->str2Type = mTG_QSTR_TYPE_OMIKUJI;
            }
        } else if (tag->table == mTG_TABLE_ITEM) {
            /* quest item: "delivery for X from Y" */
            tag->str2Type = func_8086FB9C_jp(tag, itemCond, idx);
        } else {
            tag->str2Type = mTG_QSTR_TYPE_NONE;
        }
 
        if (tag->str2Type != mTG_QSTR_TYPE_NONE) {
            /* Two-line window (str0 over str1); widths are in characters on N64 */
            width = mMl_strlen((char*)tag->str0, PLAYER_NAME_LEN, CHAR_SPACE) + 4;
            width1 = mMl_strlen((char*)tag->str1, PLAYER_NAME_LEN, CHAR_SPACE) + 4;
 
            if (tag->str2Type == mTG_QSTR_TYPE_TO_MUSEUM) {
                width -= 2;
            } else if (tag->str2Type == mTG_QSTR_TYPE_FROM_MUSEUM || tag->str2Type == mTG_QSTR_TYPE_MOTHER) {
                width1 -= 2;
            } else if (tag->str2Type == mTG_QSTR_TYPE_ANGLER) {
                width1 -= 4;
            } else if (tag->str2Type == mTG_QSTR_TYPE_OMIKUJI) {
                width1 = 7;
            }
 
            if (width < width1) {
                width = width1;
            }
 
            if (tag->str2Type == mTG_QSTR_TYPE_ITEM) {
                if (width < 6) {
                    width = 6;
                }
            } else {
                if (width < 4) {
                    width = 4;
                }
            }
 
            func_8086F764_jp(tag, 1, width, 0);
 
            if (func_8086FCF4_jp(tag) != 0) {
                tag->bodyOfs[1] += 7.0f;
                tag->bodyOfs[0] -= 0.6f + (width - 4) * 0.3f;
            }
        } else {
            /* Plain item name window */
            if (itemCond == mPr_ITEM_COND_PRESENT) {
                mem_copy(tag->str0, D_8087913C_jp, sizeof(D_8087913C_jp));
            } else {
                mIN_copy_name_str(tag->str0, itemNo);
            }
 
            func_8086F764_jp(tag, 0, mMl_strlen((char*)tag->str0, TAG_ITEM_STR_LEN, CHAR_SPACE), 0);
        }
 
        if (func_8086F960_jp(tag) != 0) {
            tag->arrowDir = 1;
        } else {
            tag->arrowDir = 2;
            tag->bodyOfs[0] *= -1.0f;
        }
 
        *(s16*)(*(u8**)((u8*)submenu->unk_2C + 0x106D0) + 0x11C) = func_8086F644_jp(tag);
    } else if (tag->table == mTG_TABLE_CATALOG_WC) {
        /* Catalog category label (Furniture, Wallpaper, ...) */
        mem_copy(tag->str0, D_80879148_jp[idx], 6);
        func_8086F764_jp(tag, 0, mMl_strlen((char*)tag->str0, TAG_STR0_LEN, CHAR_SPACE), 0);
        tag->bodyOfs[0] *= -1.0f;
        tag->arrowDir = 2;
        tag->basePos[0] += -10.0f;
        *(s16*)(*(u8**)((u8*)submenu->unk_2C + 0x106D0) + 0x11C) = func_8086F644_jp(tag);
    } else {
        tag->arrowDir = 0;
    }
}
 

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80870334_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8087047C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8087072C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8087080C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80870974_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80870A1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80870AC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80870B20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80870BA0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80870BCC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80870C6C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871570_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808715C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871664_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871708_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871760_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808717BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871894_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808718E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808719FC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871A60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871B44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871C18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871CF8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871DB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871ECC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80871F74_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8087207C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80872118_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80872580_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808725C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80872684_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808726B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80872748_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808727E0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8087287C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80872A34_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80872B54_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80872DEC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80872E60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80872E84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808731EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873278_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873348_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873428_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8087344C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873498_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873510_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873694_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808736B8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808736DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873700_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873724_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808737F4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808738C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873968_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808739B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873ADC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873C88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873F38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80873FB4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874184_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/D_808742A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874328_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874394_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874444_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874680_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808746A8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808746F8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874720_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874770_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808747D0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808748B0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874B1C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874C8C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874E08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80874EA4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808750DC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875180_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875214_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8087529C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808753A4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875434_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875610_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808757C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875888_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808759C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875A84_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875AB8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875AD0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875B60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875B88_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875BF4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875C60_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875CF0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875D38_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875DB0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875E20_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80875EE4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80876004_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80876204_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808764BC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80876558_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80876A94_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80876B18_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80876C50_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80876D90_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80877290_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808772C8_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_8087792C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80877B0C_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80877EC4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80877FF4_jp.s")

//#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808782A4_jp.s")

extern u8 D_808794DC_jp[5];
extern u8 D_808794D8_jp[];

extern f32 func_80090E98_jp(Game*,u8*,s32,f32,f32,s32,s32,s32,s32,s32,s32,f32,f32,s32);
typedef void (*SetCharMatrixProc)(void*);

//mTG_set_character_item
void func_808782A4_jp(Submenu* submenu, Game* game, void* graph, mTG_tag_c* tag, f32 xOfs, f32 yOfs) {
    f32 scale_rate = tag->scale;
    f32 pos_x;
    f32 pos_y;
    u8* color_p;

    if (fabsf(scale_rate) < 0.008f) return;



    if (tag->table == mTG_TABLE_CATALOG_WC) {
        color_p = D_808794DC_jp;
    } else {
        color_p = D_808794D8_jp;
    }

    pos_x = 160.0f + (tag->basePos[0] + xOfs + scale_rate * (tag->bodyOfs[0] + tag->textOfs[0]));
    pos_y = 120.0f - (tag->basePos[1] + yOfs + scale_rate * (tag->bodyOfs[1] + tag->textOfs[1]));

    ((mTG_SetCharMatrixView*)((u8*)submenu->unk_2C + 0x10000))->set_char_matrix_proc(graph);
    func_80090E98_jp(game, tag->str0, TAG_ITEM_STR_LEN, pos_x, pos_y, color_p[0], color_p[1], color_p[2], 255, 0, 0, scale_rate, scale_rate, 0);
}

//void mTG_pad0(void) {}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_808783F0_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80878508_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/func_80878648_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/mTG_tag_ovl_construct.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/overlays/submenu/tag_ovl/m_tag_ovl/mTG_tag_ovl_destruct.s")
