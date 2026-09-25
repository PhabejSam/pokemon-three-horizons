#include "global.h"
#include "three_horizons.h"
#include "pokemon.h"
#include "battle.h"
#include "battle_util.h"
#include "battle_util2.h"
#include "battle_gfx_sfx_util.h"
#include "evolution_scene.h"
#include "reshow_battle_screen.h"
#include "main.h"
#include "palette.h"
#include "sound.h"
#include "m4a.h"
#include "constants/rgb.h"

#if THREE_HORIZONS
// Scene-owned scratch, never saved. The battle script stays at getexp case 5.
static EWRAM_DATA u8 sState = 0;
static EWRAM_DATA u8 sPartyId = 0;
static EWRAM_DATA u8 sEnvironment = 0;
static EWRAM_DATA struct SongHeader *sMusic = NULL;
static EWRAM_DATA u16 sTarget = 0;
static EWRAM_DATA bool32 sCanStop = FALSE;
static EWRAM_DATA u8 sCommunication[8] = {0};
static EWRAM_DATA struct Pokemon sBefore = {0};
static EWRAM_DATA MainCallback sBattleCallback1 = NULL;

static void TH_WaitForBattleRebuild(void)
{
    if (gMain.callback2 == BattleMainCB2 && !gPaletteFade.active)
        gMain.callback1 = sBattleCallback1;
}

u16 TH_GetBattleEvolution(struct Pokemon *mon, bool32 *canStop)
{
    if (!GetMonData(mon, MON_DATA_HP) || GetMonData(mon, MON_DATA_IS_EGG))
        return SPECIES_NONE;
    return GetEvolutionTargetSpecies(mon, EVO_MODE_BATTLE_ONLY, ITEM_NONE, NULL, canStop, CHECK_EVO);
}

void TH_SyncEvolvedBattleMon(u32 partyId, struct Pokemon *before)
{
    struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][partyId];
    u16 species = GetMonData(mon, MON_DATA_SPECIES);
    u16 oldItem = GetMonData(before, MON_DATA_HELD_ITEM);
    u16 item = GetMonData(mon, MON_DATA_HELD_ITEM);
    if (item != oldItem)
    {
        if (gBattleStruct->itemLost[B_TRAINER_PLAYER][partyId].originalItem == oldItem)
            gBattleStruct->itemLost[B_TRAINER_PLAYER][partyId].originalItem = item;
        for (u32 battler = 0; battler < gBattlersCount; battler++)
            if (GetBattlerSide(battler) == B_SIDE_PLAYER && gBattlerPartyIndexes[battler] == partyId)
                gBattleMons[battler].item = item;
    }
    if (species != GetMonData(before, MON_DATA_SPECIES))
    {
        for (u32 battler = 0; battler < gBattlersCount; battler++)
        {
            if (GetBattlerSide(battler) != B_SIDE_PLAYER || gBattlerPartyIndexes[battler] != partyId)
                continue;
            struct BattlePokemon *battleMon = &gBattleMons[battler];
            if (battleMon->volatiles.transformed)
            {
                battleMon->hp = GetMonData(mon, MON_DATA_HP);
                battleMon->maxHP = GetMonData(mon, MON_DATA_MAX_HP);
                continue;
            }
            u16 oldSpecies = battleMon->species;
            battleMon->species = species;
            CopyMonLevelAndBaseStatsToBattleMon(battler, mon, TRUE);
            if (battleMon->volatiles.powerTrick)
            {
                u16 temp = battleMon->attack;
                battleMon->attack = battleMon->defense;
                battleMon->defense = temp;
            }
            // Retain temporary type/ability changes such as Soak and Skill Swap.
            if (!battleMon->volatiles.overwrittenAbility && battleMon->ability == GetMonAbility(before))
                battleMon->ability = GetMonAbility(mon);
            if (battleMon->types[0] == GetSpeciesType(oldSpecies, 0)
                && battleMon->types[1] == GetSpeciesType(oldSpecies, 1))
                for (u32 i = 0; i < 2; i++)
                    battleMon->types[i] = GetSpeciesType(species, i);
            for (u32 i = 0; i < MAX_MON_MOVES; i++)
                if (MOVE_IS_PERMANENT(battler, i)
                    && GetMonData(mon, MON_DATA_MOVE1 + i) != GetMonData(before, MON_DATA_MOVE1 + i))
                {
                    battleMon->moves[i] = GetMonData(mon, MON_DATA_MOVE1 + i);
                    battleMon->pp[i] = GetMonData(mon, MON_DATA_PP1 + i);
                    battleMon->ppBonuses = (battleMon->ppBonuses & ~(3 << (i * 2)))
                        | (GetMonData(mon, MON_DATA_PP_BONUSES) & (3 << (i * 2)));
                }
        }
    }
}

static void TH_ReturnFromBattleEvolution(void)
{
    TH_SyncEvolvedBattleMon(sPartyId, &sBefore);
    gBattleEnvironment = sEnvironment;
    memcpy(gBattleCommunication, sCommunication, sizeof(sCommunication));
    // Evolution owns and frees its sprite buffers. Rebuild the battle's buffers.
    AllocateMonSpritesGfx();
    ResetMapMusic();
    if (sMusic != NULL && !gDisableMusic)
        MPlayStart(&gMPlayInfo_BGM, sMusic);
    sState = 2;
    gMain.callback1 = TH_WaitForBattleRebuild;
    ReshowBattleScreenAfterMenu();
}

bool32 TH_TryBattleEvolution(u32 partyId)
{
    if (sState == 2)
    {
        if (gPaletteFade.active || gMain.callback2 != BattleMainCB2)
            return TRUE;
        sState = 0;
        return FALSE;
    }
    if (sState == 1)
    {
        if (gPaletteFade.active)
            return TRUE;
        sBefore = gParties[B_TRAINER_PLAYER][sPartyId];
        memcpy(sCommunication, gBattleCommunication, sizeof(sCommunication));
        sEnvironment = gBattleEnvironment;
        // Keep victory music when the final wild opponent has already fainted.
        sMusic = gMPlayInfo_BGM.songHeader;
        // BattleMainCB1 runs independently of callback2. Suspend it throughout
        // the evolution scene so getexp and battle controllers cannot re-enter.
        sBattleCallback1 = gMain.callback1;
        gMain.callback1 = NULL;
        CloseMainBattleScreen();
        FreeMonSpritesGfx();
        gCB2_AfterEvolution = TH_ReturnFromBattleEvolution;
        GetEvolutionTargetSpecies(&gParties[B_TRAINER_PLAYER][sPartyId], EVO_MODE_BATTLE_ONLY,
            ITEM_NONE, NULL, &sCanStop, DO_EVO);
        EvolutionScene(&gParties[B_TRAINER_PLAYER][sPartyId], sTarget, sCanStop, sPartyId);
        return TRUE;
    }
    if (partyId >= PARTY_SIZE || !(gLeveledUpInBattle & (1u << partyId))
        || gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED | BATTLE_TYPE_FRONTIER
            | BATTLE_TYPE_SAFARI | BATTLE_TYPE_CATCH_TUTORIAL | BATTLE_TYPE_INGAME_PARTNER))
        return FALSE;
    sCanStop = TRUE;
    sTarget = TH_GetBattleEvolution(&gParties[B_TRAINER_PLAYER][partyId], &sCanStop);
    if (sTarget == SPECIES_NONE)
        return FALSE;
    sPartyId = partyId;
    // Cancellation must not prompt again when this same battle ends.
    gLeveledUpInBattle &= ~(1u << partyId);
    sState = 1;
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    return TRUE;
}
#endif
