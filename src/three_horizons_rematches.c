#include "global.h"
#include "three_horizons.h"
#include "three_horizons_rematches.h"
#include "event_data.h"
#include "battle_setup.h"
#include "data.h"
#include "pokemon.h"
#include "random.h"
#include "trainer_util.h"
#include "constants/maps.h"
#include "constants/opponents.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
#include "data/three_horizons_rematches.h"

// EWRAM_DATA is the zero-initialized .sbss section. TH maps are in groups 75/76;
// the zero startup key cannot inherit their saved readiness.
static EWRAM_DATA u16 sReadinessMap = 0;
static EWRAM_DATA u16 sActiveTrainer = TRAINER_NONE;

static u16 CurrentMap(void)
{
    return ((u8)gSaveBlock1Ptr->location.mapGroup << 8) | (u8)gSaveBlock1Ptr->location.mapNum;
}

s32 TH13_ResolveRematchSlot(const struct TH13RematchEntry *entries, u32 count, u16 map, u16 trainerId)
{
    s32 found = -1;
    for (u32 i = 0; i < count; i++)
    {
        if (entries[i].map != map || entries[i].trainerId != trainerId)
            continue;
        if (found != -1 || !entries[i].localId || entries[i].localId > MAX_REMATCH_ENTRIES)
            return -1;
        found = i;
    }
    if (found == -1)
        return -1;
    for (u32 i = 0; i < count; i++)
    {
        if (i != found && entries[i].map == map && entries[i].localId == entries[found].localId)
            return -1;
    }
    return entries[found].localId - 1;
}

void TH13_ResetRematches(void)
{
    memset(gSaveBlock1Ptr->trainerRematches, 0, sizeof(gSaveBlock1Ptr->trainerRematches));
    gSaveBlock1Ptr->trainerRematchStepCounter = 0;
    FlagClear(FLAG_TH13_VS_SEEKER_ACTIVE);
    sReadinessMap = MAP_UNDEFINED;
    sActiveTrainer = TRAINER_NONE;
}

static s32 CurrentSlot(u16 trainerId)
{
    u16 map = CurrentMap();
    if (map != sReadinessMap)
    {
        TH13_ResetRematches();
        sReadinessMap = map;
    }
    return TH13_ResolveRematchSlot(sRematchEntries, ARRAY_COUNT(sRematchEntries), map, trainerId);
}

u16 TH14_ResolveMapTrainer(const struct TH13RematchEntry *entries, u32 count,
    const struct TH14RematchAlias *aliases, u32 aliasCount, u16 map, u8 localId)
{
    u16 trainer = TRAINER_NONE;
    const struct TH14RematchAlias *alias = NULL;
    if (!localId || localId > MAX_REMATCH_ENTRIES)
        return TRAINER_NONE;
    for (u32 i = 0; i < count; i++)
    {
        if (entries[i].map != map || entries[i].localId != localId)
            continue;
        if (trainer != TRAINER_NONE || TH13_ResolveRematchSlot(entries, count, map, entries[i].trainerId) < 0)
            return TRAINER_NONE;
        trainer = entries[i].trainerId;
    }
    for (u32 i = 0; i < aliasCount; i++)
    {
        if (aliases[i].map != map || aliases[i].localId != localId)
            continue;
        // A visual alias cannot shadow an ordinary trainer or another alias.
        if (trainer != TRAINER_NONE || alias != NULL)
            return TRAINER_NONE;
        alias = &aliases[i];
    }
    if (alias == NULL)
        return trainer;
    if (!alias->canonicalLocalId || alias->canonicalLocalId > MAX_REMATCH_ENTRIES
        || alias->canonicalLocalId == localId)
        return TRAINER_NONE;
    s32 slot = TH13_ResolveRematchSlot(entries, count, map, alias->trainerId);
    return slot == alias->canonicalLocalId - 1 ? alias->trainerId : TRAINER_NONE;
}

u16 TH13_GetMapTrainer(u8 localId)
{
    u16 trainer = TH14_ResolveMapTrainer(sRematchEntries, ARRAY_COUNT(sRematchEntries),
        sRematchAliases, ARRAY_COUNT(sRematchAliases), CurrentMap(), localId);
    return trainer != TRAINER_NONE && CurrentSlot(trainer) >= 0 ? trainer : TRAINER_NONE;
}

bool32 TH13_MapHasRematchTrainers(void)
{
    for (u32 i = 0; i < ARRAY_COUNT(sRematchEntries); i++)
        if (sRematchEntries[i].map == CurrentMap() && CurrentSlot(sRematchEntries[i].trainerId) >= 0)
            return TRUE;
    return FALSE;
}

bool32 TH13_SetRematchReady(u16 trainerId)
{
    s32 slot = CurrentSlot(trainerId);
    if (slot < 0 || !HasTrainerBeenFought(trainerId))
        return FALSE;
    gSaveBlock1Ptr->trainerRematches[slot] = 1;
    return TRUE;
}

bool32 TH13_IsRematchReady(u16 trainerId)
{
    s32 slot = CurrentSlot(trainerId);
    return slot >= 0 && gSaveBlock1Ptr->trainerRematches[slot] == 1 && HasTrainerBeenFought(trainerId);
}

bool32 TH13_BeginRematch(u16 trainerId)
{
    sActiveTrainer = TH13_IsRematchReady(trainerId) ? trainerId : TRAINER_NONE;
    return sActiveTrainer != TRAINER_NONE;
}

void TH13_ScriptCheckRematch(void)
{
    gSpecialVar_Result = TH13_IsRematchReady(gSpecialVar_0x8004);
}

u8 TH13_GetRematchLevel(u8 highestLevel, u8 originalHighest, u8 badges)
{
    static const u8 caps[] = {24, 24, 24, 35, 45, 55, 65, 75, 100};
    u32 stage = min(badges, ARRAY_COUNT(caps) - 1);
    s32 floor = max(1, min(originalHighest, MAX_LEVEL));
    s32 cap = max(floor, caps[stage]);
    // Subtract before clamping using a signed value, including parties below 10.
    s32 target = (s32)highestLevel - 10;
    if (target < floor)
        return floor;
    if (target > cap)
        return cap;
    return target;
}

u8 TH13_HighestNonEggPartyLevel(void)
{
    u8 highest = 1;
    for (u32 i = 0; i < PARTY_SIZE; i++)
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG))
            highest = max(highest, GetMonData(&gPlayerParty[i], MON_DATA_LEVEL));
    return highest;
}

u16 TH14_GetAuthoredRematchEvolution(u16 trainerId, u8 slot, u16 species, u8 scaledLevel, u8 badges)
{
    for (u32 i = 0; i < ARRAY_COUNT(sRematchEvolutions); i++)
    {
        const struct TH14RematchEvolution *row = &sRematchEvolutions[i];
        if (row->trainerId == trainerId && row->partySlot == slot && row->baseSpecies == species
            && scaledLevel >= row->minLevel && badges >= row->minBadges)
            return row->evolvedSpecies;
    }
    return species;
}

static bool32 CreateRematchParty(struct Pokemon *party, const struct Trainer *trainer, u16 trainerId, u8 highestLevel, u8 badges)
{
    u8 originalHighest = 1;
    struct TrainerGenerator generator = {0};
    // The curated registry contains ordinary fixed parties, not trainer pools.
    assertf(trainer->party && trainer->partySize && trainer->partySize <= PARTY_SIZE && !trainer->poolSize,
            "Invalid Three Horizons rematch party")
    {
        return FALSE;
    }
    for (u32 i = 0; i < trainer->partySize; i++)
        originalHighest = max(originalHighest, trainer->party[i].lvl);
    u8 target = TH13_GetRematchLevel(highestLevel, originalHighest, badges);
    ZeroPartyMons(party);
    MakeTrainerGenerator(&generator, trainer);
    for (u32 i = 0; i < trainer->partySize; i++)
    {
        struct TrainerMon mon = trainer->party[i];
        mon.lvl = max(1, (s32)target - (originalHighest - mon.lvl));
        for (u32 tier = 0; tier < ARRAY_COUNT(sRematchTiers); tier++)
            if (sRematchTiers[tier].base == trainer->party[i].species && mon.lvl >= sRematchTiers[tier].level)
                mon.species = sRematchTiers[tier].species;
        u16 evolved = TH14_GetAuthoredRematchEvolution(trainerId, i, trainer->party[i].species, mon.lvl, badges);
        if (evolved != trainer->party[i].species)
            mon.species = evolved;
        // Native generation chooses legal normal abilities and current moves.
        mon.ability = ABILITY_NONE;
        for (u32 move = 0; move < MAX_MON_MOVES; move++)
            mon.moves[move] = MOVE_NONE;
        GenerateMonFromTrainerMon(&party[i], &mon, &generator);
    }
    return TRUE;
}

bool32 TH13_CreateRematchPartyFromTrainer(struct Pokemon *party, const struct Trainer *trainer, u8 highestLevel, u8 badges)
{
    return CreateRematchParty(party, trainer, TRAINER_NONE, highestLevel, badges);
}

#if TESTING
bool32 Test_TH14_CreateRematchParty(struct Pokemon *party, const struct Trainer *trainer, u16 trainerId, u8 highestLevel, u8 badges)
{
    return CreateRematchParty(party, trainer, trainerId, highestLevel, badges);
}
#endif

bool32 TH13_TryCreateRematchParty(struct Pokemon *party, u16 trainerId)
{
    if (trainerId == TRAINER_NONE || sActiveTrainer != trainerId || !TH13_IsRematchReady(trainerId))
        return FALSE;
    u8 badges = 0;
    for (u32 i = 0; i < NUM_BADGES; i++)
        badges += FlagGet(FLAG_BADGE01_GET + i) != 0;
    return CreateRematchParty(party, GetTrainerStructFromId(trainerId), trainerId, TH13_HighestNonEggPartyLevel(), badges);
}
#endif
