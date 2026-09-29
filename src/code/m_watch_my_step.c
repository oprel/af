#include "global.h"
#include "m_common_data.h"
#include "m_watch_my_step.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_player_lib.h"
#include "m_scene_table.h"
#include "src/overlays/gamestates/ovl_play/m_play.h"
#include "src/overlays/actors/player_actor/m_player.h"

#define CHAR_SPACE 32

extern void Game_play_Projection_Trans(struct Game_Play* game_play, xyz_t* src, xyz_t* dst);

static mWt_watch_my_step_c S_watch_my_step;
extern mWt_mybell_confirmation_c S_mybell_conf;

//#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CBF80_jp.s")
//*
//100% matching
void func_800CBF80_jp(void) {
    bzero(&S_watch_my_step, sizeof(mWt_watch_my_step_c));
    S_watch_my_step.item_no = 0;
    func_800CC9C4_jp(); //navigate_camera_ct
    func_800CCE08_jp(); //mWt_mybell_confirmation_ct
}
//*/
//#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/watch_my_step_move.s")
//*
// 87.7% matching
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

enum {
    FADE_TYPE_NONE,
    FADE_TYPE_IN,
    FADE_TYPE_OUT,
    FADE_TYPE_OUT_START_EMU,
    FADE_TYPE_OUT_RETURN_TITLE,
    FADE_TYPE_OUT_GAME_END_TRAIN,
    FADE_TYPE_OUT_GAME_END,
    FADE_TYPE_LOCK,
    FADE_TYPE_SELECT,
    FADE_TYPE_DEMO,
    FADE_TYPE_SELECT_END,
    FADE_TYPE_EVENT,
    FADE_TYPE_OTHER_ROOM,
    FADE_TYPE_OUT_NO_RESTART,

    FADE_TYPE_NUM
};

enum {
  mSP_TANUKI_SHOP_STATUS_NORMAL,
  mSP_TANUKI_SHOP_STATUS_EVENT,
  mSP_TANUKI_SHOP_STATUS_HALLOWEEN,
  mSP_TANUKI_SHOP_STATUS_FUKUBIKI,
  mSP_TANUKI_SHOP_STATUS_HUKUBUKURO_SALE,

  mSP_TANUKI_SHOP_STATUS_NUM
};


#define GRAPH_ALLOC_TYPE(graph, type, num) (GRAPH_ALLOC(graph, sizeof(type) * (num)))
#define SE_COIN 0x4C
#define SE_REGISTER 0x50

extern Gfx D_400C3D8[];
extern Gfx D_400C250[];
extern Gfx D_400C358[];
extern Gfx D_400C2D8[];
extern Gfx D_400C1D0[];
extern D_4000220;
extern D_4000300;
extern D_4000470;
extern D_400B360;
extern D_400B3E0;
extern D_400B458;

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/watch_my_step_draw.s")

//from: 6B3DC0.h
extern void func_80090E98_jp(Game_Play* play, u8* str, s32 len, f32 x, f32 y,
                              s32 r, s32 g, s32 b, s32 a, s32 unk1, s32 unk2,
                              f32 scaleX, f32 scaleY, s32 mode);


//99% matching
void watch_my_step_draw(Game_Play* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    Mtx* font_mtx = GRAPH_ALLOC_TYPE(gfxCtx, Mtx, 1);
    Gfx* font_gfx;
    
    
    func_800CCB44_jp(play);
    func_800CD194_jp(play);

    if (S_watch_my_step.draw_type == 0) {
        return;
    }
    OPEN_DISPS(gfxCtx);

    if (font_mtx != NULL) {
        guOrtho(font_mtx, -2560.0f, 2560.0f, -1920.0f, 1920.0f, 1.0f, 2000.0f, 1.0f);
        gSPMatrix(FONT_DISP++, font_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    }

    Matrix_scale(16.0f, 16.0f, 16.0f, 0);
    Matrix_translate(S_watch_my_step.pos_x, -S_watch_my_step.pos_y, 0.0f, 1);

    font_gfx = FONT_DISP;
    gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(font_gfx++, D_400C3D8); //fki_win_mode
    gDPPipeSync(font_gfx++);
    gDPSetRenderMode(font_gfx++, G_RM_PASS, G_RM_CLD_SURF2);

    switch (S_watch_my_step.mode) {
        case 3: {
            Matrix_push();
            Matrix_scale(S_watch_my_step.opacity *
                        (0.6666669846f * S_watch_my_step.scale + 0.3333329856f),
                         S_watch_my_step.opacity, S_watch_my_step.opacity, 1);
            gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            Matrix_pull();
            gSPDisplayList(font_gfx++, D_400C250); // fki_win_w3T_model-equivalent
        }
        // fallthrough 3 -> 2
        case 2: {
            Matrix_push();
            Matrix_translate(S_watch_my_step.trans_x * -1.0f, S_watch_my_step.trans_y * -20.0f, 0.0f, 1);
            gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            Matrix_pull();
            gSPDisplayList(font_gfx++, D_400C358); // fki_win_w2T_model-equivalent
        }
        // fallthrough 2 -> 1
        case 1: {
            Matrix_push();
            Matrix_translate(S_watch_my_step.trans_x * -13.0f, S_watch_my_step.trans_y * -30.0f, 0.0f, 1);
            gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            Matrix_pull();
            gSPDisplayList(font_gfx++, D_400C2D8); // fki_win_w1T_model-equivalent
            break;
        }

        case 4: {
            u8 a = (u8)(S_watch_my_step.opacity * 255.0f);
            gDPPipeSync(font_gfx++);
            gDPSetPrimColor(font_gfx++, 0, a, 255, 255, 215, a);

            Matrix_push();
            Matrix_scale(0.6666669846f * S_watch_my_step.scale + 0.3333329856f,
                         1.0f, 1.0f, 1);
            gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            Matrix_pull();
            gSPDisplayList(font_gfx++, D_400C1D0); // fki_win_w4_model-equivalent
            break;
        }
    }

    // Reset font matrix scale
    Matrix_scale(1.0f, 1.0f, 1.0f, 0);
    gSPMatrix(font_gfx++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    FONT_DISP = font_gfx;
    
    CLOSE_DISPS(gfxCtx);

    if (S_watch_my_step.mode >= 3) {
        f32 text_opacity = (S_watch_my_step.opacity - 0.5f) * 2.0f;

        if (text_opacity > 0.0f) {
            func_80090E98_jp(play, S_watch_my_step.item_name, ITEM_NAME_LEN,
                              (S_watch_my_step.pos_x + 107.0f) + (1.0f - S_watch_my_step.scale) * 43.0f,
                              S_watch_my_step.pos_y + 113.0f,
                              45, 45, 35, (s32)(255.0f * text_opacity),
                              FALSE, FALSE, 0.875f, 0.875f, 1);
        }
    }
}

// #pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CC9C4_jp.s")

// ---- navigate_camera_ct (func_800CC9C4_jp) ------------------------------
//100% matching
void func_800CC9C4_jp(void) {
    bzero(&S_navigate, sizeof(mWt_navigate_c));
}

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CC9EC_jp.s")

/*
// ---- navigate_camera_move (func_800CC9EC_jp) ----------------------------
// N64 has no ACME-style field-type gate and no "light switch guide" second
// draw_type; both are GC/ACME-only additions. Constants (timer=0x4B=75,
// fraction=0.2, step=0.15/0.1, minStep=0.01, threshold=0.0001) read directly
// from the ROM, not copied from GC (which uses different values).
//99% matching
void func_800CC9EC_jp(Game_Play* play) {
    S_navigate.draw_type = 0;

    switch (S_navigate.mode) {
        case 0: {
            if (func_800B5D34_jp() != 0 && //mPlib_check_able_change_camera_normal_index
                play->unk_1ECC == FADE_TYPE_NONE) {
                S_navigate.timer = 0x4B;
                S_navigate.mode++;
            }
            break;
        }

        case 1: {
            add_calc(&S_navigate.opacity, 1.0f, 0.2f, 0.15f, 0.01f);
            S_navigate.timer--;

            if (S_navigate.timer == 0 || play->submenu.moveProcIndex != MSM_MOVE_PROC_WAIT) {
                S_navigate.mode++;
            }
            S_navigate.draw_type = 1;
            break;
        }

        case 2: {
            add_calc(&S_navigate.opacity, 0.0f, 0.2f, 0.1f, 0.01f);

            if (S_navigate.opacity < 0.0001f) {
                S_navigate.mode++;
            } else {
                S_navigate.draw_type = 1;
            }
            break;
        }

        case 3:
        default:
            break;
    }
}
*/

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CCB44_jp.s")


/*
// /* ============================================================================
//  * navigate_camera_draw (func_800CCB44_jp) -- the "hold C to look around /
//  * press up to change camera" hint balloon, unrelated to item pickups.
//  * Colors and D_ addresses below are read directly from the ROM; N64 doesn't
//  * have GC's light-switch-guide second draw_type (S_navigate.draw_type is
//  * never set to 2 anywhere in navigate_camera_move), so that branch doesn't
//  * exist here.
//  * ==========================================================================
//29% matching
void func_800CCB44_jp(Game_Play* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
     Mtx* font_mtx;
    Gfx* font_gfx = GRAPH_ALLOC_TYPE(gfxCtx, Mtx, 1);


    if (S_navigate.draw_type == 0) {
        return;
    }

    OPEN_DISPS(gfxCtx);

    if (font_mtx != NULL) {
        guOrtho(font_mtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
        gSPMatrix(FONT_DISP++, font_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    }

    Matrix_scale(16.0f, 16.0f, 16.0f, 0);
    gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(FONT_DISP++, D_400C3D8);

    {
        u8 a = (u8)(S_navigate.opacity * 255.0f);

        gDPPipeSync(FONT_DISP++);
        gDPSetPrimColor(FONT_DISP++, 0, a, 40, 40, 140, a);
        gSPDisplayList(FONT_DISP++, D_4000220);

        gDPPipeSync(FONT_DISP++);
        gDPSetPrimColor(FONT_DISP++, 0, a, 255, 255, 30, a);
        gSPDisplayList(FONT_DISP++, D_4000300);

        gDPPipeSync(FONT_DISP++);
        gDPSetPrimColor(FONT_DISP++, 0, a, 155, 30, 30, a);
        gSPDisplayList(FONT_DISP++, D_4000470);
    }

    CLOSE_DISPS(gfxCtx);
}
*/

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CCE08_jp.s")
/*
// /* ---- mWt_mybell_confirmation_ct (func_800CCE08_jp) ----------------------
// /* N64's struct is only 12 bytes {opacity, all_money, coin_sfx_timer, mode,
//  * draw_type} -- no update_money/play_finish_sfx fields exist, so there's no
//  * mWt_set_coin_se(FALSE) call here at all.
//100% matching
void func_800CCE08_jp(void) {
    bzero(&S_mybell_conf, sizeof(mWt_mybell_confirmation_c));
    S_mybell_conf.all_money = func_800CD59C_jp();
}
*/
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CCE40_jp.s")

/*
// /* ---- mWt_mybell_confirmation_move (func_800CCE40_jp) --------------------
// /* place_chk[] is 7 entries here (0x1C bytes / 4), not GC's 8 -- N64 has one
//  * fewer shop scene in this list. The "S_se_play_flg" static bool that GC
//  * wraps in mWt_set_coin_se() is a lone static right after place_chk[] here
//  * (D_8010EF2C_jp) and is poked directly; sound calls are inlined rather than
//  * going through a helper, matching the simpler struct.
//98% matching
void func_800CCE40_jp(Game_Play* play) {
    static s32 place_chk[7] = {
        SCENE_SHOP0, SCENE_CONVENI, SCENE_SUPER, SCENE_DEPART,
        SCENE_DEPART_2, SCENE_BROKER_SHOP, SCENE_POST_OFFICE,
    };
    static u8 S_se_play_flg;
    s32 i;

    S_mybell_conf.draw_type = 0;

    if (S_mybell_conf.coin_sfx_timer == 1) {
        sAdo_SysLevStop(SE_COIN);
    }
    if (S_mybell_conf.coin_sfx_timer != 0) {
        S_mybell_conf.coin_sfx_timer--;
    }

    for (i = 0; i < 7; i++) {
        if (SAVE_GET(sceneNo) == place_chk[i]) {
            break;
        }
    }

    if (i == 7) {
        return;
    }
    if (mEv_CheckFirstJob() == TRUE) {
        return;
    }
    if (i <= 4 && COMMON_GET(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
        return;
    }

    switch (S_mybell_conf.mode) {
        case 0: {
            if (play->submenu.moveProcIndex == MSM_MOVE_PROC_WAIT) {
                S_mybell_conf.mode++;
            }
            break;
        }

        case 1: {
            f32 money = S_mybell_conf.all_money;
            u32 now_money = func_800CD59C_jp();

            if (now_money != S_mybell_conf.all_money) {
                if (S_se_play_flg == FALSE) {
                    S_se_play_flg = TRUE;
                    S_mybell_conf.coin_sfx_timer = 0x96;
                    sAdo_SysLevStart(SE_COIN);
                }
            }

            if (play->submenu.moveProcIndex != MSM_MOVE_PROC_WAIT) {
                S_mybell_conf.mode++;
            }

            if (now_money == S_mybell_conf.all_money && S_mybell_conf.mode == 2 && S_se_play_flg == TRUE) {
                S_se_play_flg = FALSE;
                sAdo_SysLevStop(SE_COIN);
                S_mybell_conf.coin_sfx_timer = 0;
                if (now_money == S_mybell_conf.all_money) {
                    sAdo_SysTrgStart(SE_REGISTER);
                }
            }

            add_calc(&money, now_money, 0.2f, 10000.0f, 1.0f);
            S_mybell_conf.all_money = money;
            add_calc(&S_mybell_conf.opacity, 1.0f, 0.2f, 0.15f, 0.01f);
            S_mybell_conf.draw_type = 1;
            break;
        }

        case 2: {
            add_calc(&S_mybell_conf.opacity, 0.0f, 0.2f, 0.1f, 0.01f);

            if (S_mybell_conf.opacity < 0.0001f) {
                S_mybell_conf.mode = 0;
            } else {
                S_mybell_conf.draw_type = 1;
            }
            break;
        }

        case 3:
        default:
            break;
    }
}
*/
#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CD194_jp.s")

/*
// /* ============================================================================
//  * mWt_mybell_confirmation_draw (func_800CD194_jp) -- the bell/money counter
//  * popup, also unrelated to item pickups. Digit formatting is a hand-inlined
//  * base-10 loop in the actual N64 code (no separate mFont_UnintToString call
//  * exists here), so it's written inline below to match the real asm.
//  * ==========================================================================
//26% matching
void func_800CD194_jp(Game_Play* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
     Mtx* font_mtx;
    Gfx* font_gfx = GRAPH_ALLOC_TYPE(gfxCtx, Mtx, 1);


    if (S_mybell_conf.draw_type == 0) {
        return;
    }

    OPEN_DISPS(gfxCtx);

    if (font_mtx != NULL) {
        guOrtho(font_mtx, -160.0f, 160.0f, -120.0f, 120.0f, 1.0f, 2000.0f, 1.0f);
        gSPMatrix(FONT_DISP++, font_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    }

    Matrix_scale(16.0f, 16.0f, 16.0f, 0);
    gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(FONT_DISP++, D_400C3D8);

    {
        u8 a = (u8)(S_mybell_conf.opacity * 255.0f);

        gDPPipeSync(FONT_DISP++);
        gDPSetRenderMode(FONT_DISP++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        gDPSetPrimColor(FONT_DISP++, 0, a, 95, 50, 175, a);
        gSPDisplayList(FONT_DISP++, D_400B360);

        gDPPipeSync(FONT_DISP++);
        gDPSetRenderMode(FONT_DISP++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        gDPSetPrimColor(FONT_DISP++, 0, a, 255, 245, 255, a);
        gSPDisplayList(FONT_DISP++, D_400B3E0);

        gDPPipeSync(FONT_DISP++);
        gDPSetPrimColor(FONT_DISP++, 0, a, 255, 245, 255, a);
        gSPDisplayList(FONT_DISP++, D_400B458);
    }

    Matrix_scale(1.0f, 1.0f, 1.0f, 0);
    gSPMatrix(FONT_DISP++, _Matrix_to_Mtx_new(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    CLOSE_DISPS(gfxCtx);

    //  * Format S_mybell_conf.all_money as a fixed 6-digit string with leading
    //  * zeroes suppressed (replaced by spaces), base-10, no separate helper
    //  * function -- matches the inlined division loop in the real asm. Position
    //  * is a fixed (214, 48) here; N64 doesn't call mFont_GetStringWidth to
    //  * right-align it against a fixed right edge the way GC does.
    {
        static u32 place_values[6] = { 100000, 10000, 1000, 100, 10, 1 };
        u8 bell_str[7];
        u32 value = S_mybell_conf.all_money;
        s32 leadingZero = TRUE;
        s32 i;
        u8 a = (u8)(S_mybell_conf.opacity * 255.0f);

        for (i = 0; i < 6; i++) {
            u32 digit = value / place_values[i];
            value -= digit * place_values[i];

            if (digit != 0) {
                bell_str[i] = '0' + digit;
                leadingZero = FALSE;
            } else if (!leadingZero) {
                bell_str[i] = '0';
            } else if (i == 5) {
                bell_str[i] = '0';
            } else {
                bell_str[i] = CHAR_SPACE;
            }
        }
        bell_str[6] = 0;

        func_80090E98_jp(play, bell_str, 6, 214.0f, 48.0f, 255, 245, 0, a,
                          FALSE, FALSE, 0.75f, 0.75f, 1);
    }
}
*/

#pragma GLOBAL_ASM("asm/jp/nonmatchings/code/m_watch_my_step/func_800CD59C_jp.s")

/*
// /* ---- get_all_money (func_800CD59C_jp) ----------------------------------- 
// /* Item/amount table lengths aren't visible from this function alone (the
//  * loop runs until it hits the address of the next unrelated symbol,
//  * sFlashromIsInit) -- leaving that as the literal bound rather than
//  * guessing a MONEY_NUM. 
//92% matching
extern u16 D_8010EF48_jp[];
extern u32 D_8010EF50_jp[];
extern void* sFlashromIsInit;

u32 func_800CD59C_jp(void) {
    PrivateInfo* priv = COMMON_GET(privateInfo);
    u16* itemPtr = D_8010EF48_jp;
    u32* amountPtr = D_8010EF50_jp;
    u32 money = priv->inventory.wallet;

    do {
        s32 sum = mPr_GetPossessionItemSumWithCond(priv, *itemPtr, mPr_ITEM_COND_NORMAL);
        money += sum * (*amountPtr);
        amountPtr++;
        itemPtr++;
    } while ((void*)amountPtr != sFlashromIsInit);

    return money;
}
    //*/