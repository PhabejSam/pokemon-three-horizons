#include "global.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "event_data.h"
#include "item.h"
#include "field_move.h"

#if THREE_HORIZONS
bool32 TH_IsHMFieldMove(enum FieldMove move)
{
    return move <= FIELD_MOVE_WATERFALL || move == FIELD_MOVE_ROCK_CLIMB || move == FIELD_MOVE_DEFOG;
}

bool32 TH_FieldMoveUnlocked(enum FieldMove move)
{
    // The remaining Kanto HMs are deliberately unavailable in this chapter.
    // Cut is a Cascade Badge action, rather than Emerald's Boulder Badge gate.
    return move == FIELD_MOVE_CUT && FlagGet(FLAG_BADGE02_GET) && CheckBagHasItem(ITEM_HM01, 1);
}

bool32 TH_CanUseFieldMove(struct Pokemon *mon, enum FieldMove move)
{
    if (!TH_FieldMoveUnlocked(move)
     || !GetMonData(mon, MON_DATA_SPECIES)
     || GetMonData(mon, MON_DATA_IS_EGG)
     || !GetMonData(mon, MON_DATA_HP))
        return FALSE;
    return CanLearnTeachableMove(GetMonData(mon, MON_DATA_SPECIES), FieldMove_GetMoveId(move));
}

u8 TH_FindFieldMoveUser(enum FieldMove move)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
        if (TH_CanUseFieldMove(&gPlayerParty[i], move))
            return i;
    return PARTY_SIZE;
}
#endif
