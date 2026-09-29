#ifndef AC_GYOEI_H
#define AC_GYOEI_H

#include "ultra64.h"
#include "m_actor.h"
#include "unk.h"

struct Game_Play;
struct Gyoei;

enum fish_type {
    aGYO_TYPE_CRUCIAN_CARP,
    aGYO_TYPE_BROOK_TROUT,
    aGYO_TYPE_CARP,
    aGYO_TYPE_KOI,
    aGYO_TYPE_CATFISH,
    aGYO_TYPE_SMALL_BASS,
    aGYO_TYPE_BASS,
    aGYO_TYPE_LARGE_BASS,
    aGYO_TYPE_BLUEGILL,
    aGYO_TYPE_GIANT_CATFISH,
    aGYO_TYPE_GIANT_SNAKEHEAD,
    aGYO_TYPE_BARBEL_STEED,
    aGYO_TYPE_DACE,
    aGYO_TYPE_PALE_CHUB,
    aGYO_TYPE_BITTERLING,
    aGYO_TYPE_LOACH,
    aGYO_TYPE_POND_SMELT,
    aGYO_TYPE_SWEETFISH,
    aGYO_TYPE_CHERRY_SALMON,
    aGYO_TYPE_LARGE_CHAR,
    aGYO_TYPE_RAINBOW_TROUT,
    aGYO_TYPE_STRINGFISH,
    aGYO_TYPE_SALMON,
    aGYO_TYPE_GOLDFISH,
    aGYO_TYPE_PIRANHA,
    aGYO_TYPE_AROWANA,
    aGYO_TYPE_EEL,
    aGYO_TYPE_FRESHWATER_GOBY,
    aGYO_TYPE_ANGELFISH,
    aGYO_TYPE_GUPPY,
    aGYO_TYPE_POPEYED_GOLDFISH,
    aGYO_TYPE_COELACANTH,
    aGYO_TYPE_NUM
};

typedef void (*GyoeiActionFunc)(struct Gyoei*, struct Game_Play*);

typedef struct Gyoei {
    /* 0x000 */ Actor actor;
    /* 0x174 */ UNK_TYPE1 unk_174[0x4C8];
} Gyoei; // size = 0x63C

#endif
