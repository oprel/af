#include "m_item_name.h"
#include "m_lib.h"
#include "m_room_type.h"
#include "m_std_dma.h"

#define ITEM_NAME_SEG 0x06000000

extern u8 D_10F4000[];
extern u16 D_6001D98[];
extern u8* D_801076BC_jp[16];
extern u8 D_801076B0_jp[];

extern u16 mRmTp_FtrItemNo2Item1ItemNo(u16 item);

void func_80096710_jp(u8* dst, RomOffset src) {
    DmaMgr_RequestSyncDebug(dst, src, ITEM_NAME_LEN, "../m_item_name.c", 0x55);
}

void mIN_copy_name_str(char* buf, u32 item) {
    u16 item_arg;
    u16 item_no;
    s32 type;
    s32 addend;
    char name[ITEM_NAME_LEN];
    RomOffset base;

    item_arg = item;
    item_no = mRmTp_FtrItemNo2Item1ItemNo(item_arg);
    type = (item_no & 0xF000) >> 12;

    switch (type) {
        case 2:
            base = (RomOffset)D_801076BC_jp[(item_no & 0xF00) >> 8] +
                   (item_no & 0xFF) * ITEM_NAME_LEN;
            addend = base - ITEM_NAME_SEG;
            func_80096710_jp(name, addend + (RomOffset)D_10F4000);
            mem_copy(buf, name, ITEM_NAME_LEN);
            break;

        case 1:
            base = (RomOffset)&D_6001D98 +
                   (item_no & 0xFFF) * ITEM_NAME_LEN;
            addend = base - ITEM_NAME_SEG;
            func_80096710_jp(name, addend + (RomOffset)D_10F4000);
            mem_copy(buf, name, ITEM_NAME_LEN);
            break;

        default:
            if (item_no == 0) {
                mem_copy(buf, D_801076B0_jp, ITEM_NAME_LEN);
            }
            break;
    }
}