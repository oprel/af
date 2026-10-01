#ifndef M_WATCH_MY_STEP_H
#define M_WATCH_MY_STEP_H

#include "ultra64.h"
#include "m_item_name.h"

struct Game_Play;

typedef struct watch_my_step_s {
    f32 pos_x;
    f32 pos_y;

    f32 opacity;

    f32 trans_x;
    f32 trans_y;

    f32 scale;

    s16 timer;

    u16 item_no;

    u8 mode;
    u8 item_name[ITEM_NAME_LEN];
    u8 draw_type;
} mWt_watch_my_step_c;

typedef struct navigate_s {
    f32 opacity;
    s16 timer;
    u8 mode;
    u8 draw_type;
} mWt_navigate_c;

typedef struct mybell_confirmation_s {
    f32 opacity;
    u32 all_money;
    s16 coin_sfx_timer;
    u8 mode;
    u8 draw_type;
    u8 update_money;
    u8 play_finish_sfx;
} mWt_mybell_confirmation_c;

void func_800CBF80_jp(void);
void watch_my_step_move(struct Game_Play* game_play);
void watch_my_step_draw(struct Game_Play* game_play);
void func_800CC9C4_jp();
void func_800CC9EC_jp(struct Game_Play* game_play);
void func_800CCB44_jp();
void func_800CCE08_jp();
void func_800CCE40_jp(struct Game_Play* game_play);
void func_800CD194_jp();
u32 func_800CD59C_jp();

#endif
