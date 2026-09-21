#ifndef AC_HANDOVERITEM_H
#define AC_HANDOVERITEM_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct HandOverItem;

typedef void (*HandOverItemActionFunc)(struct HandOverItem*, struct Game_Play*);

typedef struct HandOverItem {
    UNK_TYPE1 unk_00[0x10];
    Actor* masterActor;
} HandOverItem; // size = 0x1F8

#endif
