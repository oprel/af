#ifndef AC_NPC_P_SEL2_H
#define AC_NPC_P_SEL2_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Npc_P_Sel2;

typedef void (*Npc_P_Sel2ActionFunc)(struct Npc_P_Sel2*, struct Game_Play*);

typedef struct Npc_P_Sel2 {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x7D0];
    /* 0x944 */ s32 card_player_next_choice_idx;
    /* 0x94C */ s32 passport_slot;
} Npc_P_Sel2; // size = 0x954

#endif
