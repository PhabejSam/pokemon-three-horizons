#include "global.h"
#include "test/test.h"
#include "battle_setup.h"
#include "event_data.h"
#include "item.h"
#include "overworld.h"
#include "constants/maps.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
bool8 TH_TestTowerGhostCheck(u16 mapGroup, u16 mapNum);

TEST("Three Horizons PT14 mother: upper floor uses Scope classification and adjacent maps do not")
{
    ClearBag();
    EXPECT(TH_TestTowerGhostCheck(MAP_GROUP(MAP_TH14_POKEMON_TOWER_7F), MAP_NUM(MAP_TH14_POKEMON_TOWER_7F)));
    EXPECT(TH_TestTowerGhostCheck(MAP_GROUP(MAP_TH13_POKEMON_TOWER_6F), MAP_NUM(MAP_TH13_POKEMON_TOWER_6F)));
    EXPECT(!TH_TestTowerGhostCheck(MAP_GROUP(MAP_TH14_ROCKET_HIDEOUT_ELEVATOR), MAP_NUM(MAP_TH14_ROCKET_HIDEOUT_ELEVATOR)));
    EXPECT(AddBagItem(ITEM_SILPH_SCOPE, 1));
    EXPECT(!TH_TestTowerGhostCheck(MAP_GROUP(MAP_TH14_POKEMON_TOWER_7F), MAP_NUM(MAP_TH14_POKEMON_TOWER_7F)));
    EXPECT(!TH_TestTowerGhostCheck(MAP_GROUP(MAP_TH13_POKEMON_TOWER_6F), MAP_NUM(MAP_TH13_POKEMON_TOWER_6F)));
}

TEST("Three Horizons PT14 mother: appended scene actor preserves the five existing locals")
{
    const struct MapHeader *map = Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH13_POKEMON_TOWER_6F), MAP_NUM(MAP_TH13_POKEMON_TOWER_6F));
    EXPECT_EQ(map->events->objectEventCount, 6);
    if (map->events->objectEventCount == 6)
    {
        for (u32 i = 0; i < 6; i++) EXPECT_EQ(map->events->objectEvents[i].localId, i+1);
        EXPECT_EQ(map->events->objectEvents[5].x, 11);
        EXPECT_EQ(map->events->objectEvents[5].y, 16);
        // Removal during the fade cannot set the final receipt prematurely.
        EXPECT_EQ(map->events->objectEvents[5].flagId, 0);
    }
}
#endif
#include "battle.h"
#include "fieldmap.h"
#include "pokemon.h"
#include "pokedex.h"
#include "script.h"
#include "task.h"
#include "palette.h"
#include "field_weather.h"
#include "constants/field_weather.h"
#include "gpu_regs.h"
#include "text.h"
#include "string_util.h"
#include "three_horizons_chapter14.h"
#include "three_horizons_research.h"

#if THREE_HORIZONS
extern const u8 TH14_Mother_RecordWin[];
extern const u8 TH14_Mother_Reveal[], TH14_Mother_Record[], TH14_Mother_Recorded[];
extern const u8 TH14_Mother_MissingGear[], TH14_Mother_RetryPhoto[], TH14_Mother_StillWatching[], TH14_Mother_Calm[];
void StartMarowakBattle(void);
static void LoadMotherTower(void)
{
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH13_POKEMON_TOWER_6F);
    gSaveBlock1Ptr->location.mapNum = MAP_NUM(MAP_TH13_POKEMON_TOWER_6F);
    gMapHeader = *Overworld_GetMapHeaderByGroupAndId(MAP_GROUP(MAP_TH13_POKEMON_TOWER_6F), MAP_NUM(MAP_TH13_POKEMON_TOWER_6F));
    LoadObjEventTemplatesFromHeader(); InitMap();
}
TEST("Three Horizons PT14 mother: native stair reload opens only resolved and actor receipt stays separate")
{
    const struct MapHeader header = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    for (u32 state = 0; state < 8; state++)
    {
        InitEventData();
        if (state & 1) FlagSet(FLAG_TH14_OBS_MOTHER);
        if (state & 2) FlagSet(FLAG_TH14_MOTHER_WON);
        if (state & 4) FlagSet(FLAG_TH14_MOTHER_RESOLVED);
        for (u32 reload = 0; reload < 2; reload++)
        {
            ClearTempFieldEventData(); LoadMotherTower();
            EXPECT_EQ(MapGridGetMetatileIdAt(11+MAP_OFFSET,16+MAP_OFFSET), 709);
            EXPECT_EQ(MapGridGetCollisionAt(11+MAP_OFFSET,16+MAP_OFFSET) == 0, !!(state&4));
            EXPECT_EQ(VarGet(VAR_TEMP_1), !!(state&4));
            EXPECT_EQ(VarGet(VAR_TEMP_2), 0);
            EXPECT_EQ(TH14_ShouldSpawnObject(MAP_GROUP(MAP_TH13_POKEMON_TOWER_6F), MAP_NUM(MAP_TH13_POKEMON_TOWER_6F), 6), (state&3) && !(state&4));
            EXPECT(!FlagGet(FLAG_TH14_PHOTO_MOTHER));
        }
    }
    gMapHeader=header;gBackupMapLayout=layout;
}
TEST("Three Horizons PT14 mother: real encounter is female thirty Serious and only winning callback records won")
{
    const struct MapHeader header = gMapHeader;
    const struct BackupMapLayout layout = gBackupMapLayout;
    MainCallback original = gMain.callback2, originalSaved = gMain.savedCallback;
    InitEventData(); ClearBag(); ResetPokedex(); ResetTasks(); LoadMotherTower();
    EXPECT(AddBagItem(ITEM_SILPH_SCOPE, 1));
    CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][0], SPECIES_WOBBUFFET, 40, 123, OTID_STRUCT_PLAYER_ID, 20);
    CalculatePlayerPartyCount();
    StartMarowakBattle();
    MainCallback endMother = gMain.savedCallback;
    EXPECT(endMother != NULL);
    EXPECT_EQ(gBattleTypeFlags, BATTLE_TYPE_GHOST);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_SPECIES), SPECIES_MAROWAK);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_OPPONENT_A][0], MON_DATA_LEVEL), 30);
    EXPECT_EQ(GetMonGender(&gParties[B_TRAINER_OPPONENT_A][0]), MON_FEMALE);
    EXPECT_EQ(GetNature(&gParties[B_TRAINER_OPPONENT_A][0]), NATURE_SERIOUS);
    ResetTasks(); // Do not run the transition inside a synchronous callback test.
    for (u32 outcome = 0; outcome <= B_OUTCOME_MON_TELEPORTED; outcome++)
    {
        InitEventData(); FlagSet(FLAG_TH13_GEAR); FlagSet(FLAG_TH14_OBS_MOTHER); FlagSet(FLAG_TH14_PHOTO_MOTHER);
        FlagSet(FLAG_TH13_ENDPOINT);
        gBattleOutcome=outcome;gSpecialVar_Result=TRUE;
        endMother(); MainCallback selected=gMain.callback2;SetMainCallback2(original);
        bool32 blackout=outcome==B_OUTCOME_LOST || outcome==B_OUTCOME_DREW || outcome==B_OUTCOME_FORFEITED;
        EXPECT_EQ(selected,blackout ? CB2_WhiteOut : CB2_ReturnToFieldContinueScriptPlayMapMusic);
        EXPECT_EQ(gSpecialVar_Result,outcome!=B_OUTCOME_WON);
        if (!blackout) RunScriptImmediately(TH14_Mother_RecordWin);
        EXPECT_EQ(FlagGet(FLAG_TH14_MOTHER_WON),outcome==B_OUTCOME_WON);
        EXPECT(!FlagGet(FLAG_TH14_MOTHER_RESOLVED));EXPECT(FlagGet(FLAG_TH14_PHOTO_MOTHER));EXPECT(FlagGet(FLAG_TH13_ENDPOINT));
        EXPECT(!GetSetPokedexFlag(NATIONAL_DEX_MAROWAK, FLAG_GET_CAUGHT));
        ClearTempFieldEventData();EXPECT(FlagGet(FLAG_TH14_PHOTO_MOTHER));
        ScriptContext_Init();UnlockPlayerFieldControls();
    }
    gMain.savedCallback=originalSaved;gMapHeader=header;gBackupMapLayout=layout;
}
TEST("Three Horizons PT14 mother: photo prerequisite failure and interrupted flash cannot report completion")
{
    InitEventData(); ResetPaletteFade();
    gSpecialVar_0x8004=TH_PHOTO_MOTHERS_WATCH;
    TH_ScriptResearchPhotoStatus();EXPECT_EQ(gSpecialVar_Result,0);
    FlagSet(FLAG_TH13_GEAR);TH_ScriptResearchPhotoStatus();EXPECT_EQ(gSpecialVar_Result,0);
    FlagSet(FLAG_TH14_OBS_MOTHER);TH_ScriptResearchPhotoStatus();EXPECT_EQ(gSpecialVar_Result,1);
    TH_ScriptEndPhotoFlash();EXPECT_EQ(gSpecialVar_Result,FALSE);
    TH_ScriptBeginPhotoFlash();EXPECT_EQ(gSpecialVar_Result,TRUE);
    TH_ScriptBeginPhotoFlash();EXPECT_EQ(gSpecialVar_Result,FALSE);
    FadeScreenHardware(FADE_TO_WHITE,0);
    TH_ScriptEndPhotoFlash();EXPECT_EQ(gSpecialVar_Result,FALSE);
    EXPECT(!FlagGet(FLAG_TH14_PHOTO_MOTHER));ResetPaletteFade();
    u16 bldcnt=GetGpuReg(REG_OFFSET_BLDCNT);
    TH_ScriptBeginPhotoFlash();EXPECT_EQ(gSpecialVar_Result,TRUE);
    for (u32 direction=0;direction<2;direction++)
    {
        FadeScreenHardware(direction ? FADE_FROM_WHITE : FADE_TO_WHITE,0);
        u32 frame;
        for(frame=0;frame<120 && gPaletteFade.active;frame++) { UpdatePaletteFade();TransferPlttBuffer(); }
        EXPECT_LT(frame,120);EXPECT(!FlagGet(FLAG_TH14_PHOTO_MOTHER));
    }
    TH_ScriptEndPhotoFlash();EXPECT_EQ(gSpecialVar_Result,TRUE);EXPECT_EQ(GetGpuReg(REG_OFFSET_BLDCNT),bldcnt);
    TH_ScriptTakeResearchPhoto();EXPECT_EQ(gSpecialVar_Result,TRUE);EXPECT(FlagGet(FLAG_TH14_PHOTO_MOTHER));
    TH_ScriptResearchPhotoStatus();EXPECT_EQ(gSpecialVar_Result,2);
    TH_ScriptTakeResearchPhoto();EXPECT_EQ(gSpecialVar_Result,FALSE);
    EXPECT(!FlagGet(FLAG_TH14_MOTHER_WON));EXPECT(!FlagGet(FLAG_TH14_MOTHER_RESOLVED));
}
TEST("Three Horizons PT14 mother: scene dialogue fits the native text box")
{
    const u8 *texts[]={TH14_Mother_Reveal,TH14_Mother_Record,TH14_Mother_Recorded,TH14_Mother_MissingGear,TH14_Mother_RetryPhoto,TH14_Mother_StillWatching,TH14_Mother_Calm};
    SetDefaultFontsPointer();
    for(u32 t=0;t<ARRAY_COUNT(texts);t++)
    {
        u8 text[256];EXPECT_LT(StringLength(texts[t]),sizeof(text));StringCopy(text,texts[t]);
        for(u32 i=0;text[i]!=EOS;i++) if(text[i]==CHAR_PROMPT_CLEAR||text[i]==CHAR_PROMPT_SCROLL)text[i]=CHAR_NEWLINE;
        EXPECT_LE(GetStringWidth(FONT_NORMAL,text,0),208);
    }
}
#endif
