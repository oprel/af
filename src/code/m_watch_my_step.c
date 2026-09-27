#include "global.h"
#include "m_common_data.h"
#include "m_watch_my_step.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_player_lib.h"
#include "src/overlays/gamestates/ovl_play/m_play.h"
#include "src/overlays/actors/player_actor/m_player.h"

#define CHAR_SPACE 32

extern void func_800CC9C4_jp(void);
extern void func_800CCE08_jp(void);
extern void func_800CC9EC_jp(s32 eligible);
extern void func_800CCE40_jp(struct Game_Play* game_play);
extern s32 func_800B5C60_jp(void);
extern void Game_play_Projection_Trans(struct Game_Play* game_play, xyz_t* src, xyz_t* dst);

extern mWt_watch_my_step_c S_watch_my_step;

//#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CBF80_jp.s")
//*
void func_800CBF80_jp(void) {
    bzero(&S_watch_my_step, sizeof(mWt_watch_my_step_c));
    S_watch_my_step.item_no = 0;
    func_800CC9C4_jp(); //navigate_camera_ct
    func_800CCE08_jp(); //mWt_mybell_confirmation_ct
}
//*/
//#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/watch_my_step_move.s")
//*
void watch_my_step_move(Game_Play* game_play) {
    u16 window_item;
    Actor* player_actor = (Actor*)get_player_actor_withoutCheck(game_play);
    s32 can_show = FALSE;
    
    if (*(s32*)((u8*)game_play + 0x1AC0) == 1 && *(s32*)((u8*)game_play + 0x1AE4) >= 0x15) {
        can_show = TRUE;
    }
    
    
    func_800CC9EC_jp(game_play); //navigate_camera_move
    func_800CCE40_jp(game_play); //mWt_mybell_confirmation_move

    S_watch_my_step.draw_type = 0;

    if (mEv_CheckTitleDemo()>0) return;

    window_item = func_800B5C60_jp(); //mPlib_Get_itemNo_forWindow();

    switch (S_watch_my_step.mode) {
        case 0: {
            if (window_item != 0 && !can_show) {
                S_watch_my_step.opacity = 0.0f;
                S_watch_my_step.timer = 1;
                S_watch_my_step.mode++;
            }
            break;
        }

        case 1:
        case 2: {
            if (S_watch_my_step.timer-- == 0) {
                S_watch_my_step.timer = 1;
                S_watch_my_step.mode++;
            }
            break;
        }

        case 3: {
            add_calc(&S_watch_my_step.opacity, 1.0f, 0.5f, 0.5f, 0.15f);
            if (window_item == 0 || can_show == TRUE) {
                S_watch_my_step.mode++;
            }
            break;
        }

        case 4: {
            add_calc(&S_watch_my_step.opacity, 0.0f, 0.5f, 0.2f, 0.05f);
            add_calc(&S_watch_my_step.opacity, 0.0f, 0.5f, 0.005f, 0.005f);

            if (S_watch_my_step.opacity < 0.01f) {
                S_watch_my_step.mode = 0;
            }
            break;
        }

        default: {
            S_watch_my_step.mode = 0;
            break;
        }
    }

    if (S_watch_my_step.mode != 0) {
        xyz_t screen_pos;
        xyz_t position = player_actor->world.pos;
        position.y += 30.0f;

        Game_play_Projection_Trans(game_play, &position, &screen_pos);

        if (S_watch_my_step.mode < 4) {
            S_watch_my_step.trans_x = 1.0f;

            if (screen_pos.x > 200.0f) {
                S_watch_my_step.trans_x = -1.0f;
            } else if (screen_pos.x > 120.0f && *(s16*)((u8*)player_actor + 0xDE) >= 0) { //player_actor->actor.shape_info.rotation.y
                S_watch_my_step.trans_x = -1.0f;
            }

            S_watch_my_step.trans_y = 1.0f;
            if (screen_pos.y < 68.0f) {
                S_watch_my_step.trans_y = -1.0f;
            }

            S_watch_my_step.pos_x = screen_pos.x - (S_watch_my_step.trans_x * -40.0f + 160.0f);
            S_watch_my_step.pos_y = screen_pos.y - (S_watch_my_step.trans_y * 42.0f + 120.0f);
        }

        
        if (window_item != 0) {
            s32 len;
            if (S_watch_my_step.item_no != window_item || S_watch_my_step.item_no == 0) {
                S_watch_my_step.item_no = window_item;
                mIN_copy_name_str(S_watch_my_step.item_name, (u16)window_item);
            }
            len = mMl_strlen(S_watch_my_step.item_name, ITEM_NAME_LEN, CHAR_SPACE);
            S_watch_my_step.scale = ((f32)len - 2.0f) / 8;
        } else {
            S_watch_my_step.item_no = 0;
        }
    
        if (S_watch_my_step.mode  == 0) {
            return;
        }
    
        if (((mFI_GetFieldId() & 0xF000) == 0 && mEv_CheckFirstIntro() != TRUE) ||
            (common_data.field_type == 1 && (window_item < 0x1000 || window_item >= 0x1ECD))) {
            S_watch_my_step.draw_type = 1;
        }
    }
}
//*/

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/watch_my_step_draw.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CC9C4_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CC9EC_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CCB44_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CCE08_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CCE40_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CD194_jp.s")

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CD59C_jp.s")
