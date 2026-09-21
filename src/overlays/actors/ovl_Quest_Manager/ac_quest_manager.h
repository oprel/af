#ifndef AC_QUEST_MANAGER_H
#define AC_QUEST_MANAGER_H

#include "ultra64.h"
#include "m_actor.h"
#include "m_choice_main.h"
#include "unk.h"

struct Game_Play;
struct Quest_Manager;

typedef void (*Quest_ManagerActionFunc)(struct Quest_Manager*, struct Game_Play*);

typedef struct Quest_Manager_Choice {
    s32 choice_ids[Choice_CHOICE_MAX];
    s32 choice_num;
    s32 talk_action;
} QMgr_Choice;

typedef struct Quest_Manager {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x14];
    /* 0x188 */ QMgr_Choice choice;
    /* 0x1A0 */ UNK_TYPE1 unk_1A0[0x738];
} Quest_Manager; // size = 0x8D8

#endif
