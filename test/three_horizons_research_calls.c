#include "global.h"
#include "test/test.h"
#include "event_data.h"
#include "overworld.h"
#include "palette.h"
#include "script.h"
#include "item_menu.h"
#include "party_menu.h"
#include "three_horizons_research.h"
#include "constants/maps.h"
#include "constants/three_horizons.h"

#if THREE_HORIZONS
static void BattleCallback(void) {}
static void NamingCallback(void) {}
static void SafeField(void)
{
    TH_ResearchResetCallPacing();
    ScriptContext_Init(); UnlockPlayerFieldControls();
    gMain.callback2 = CB2_Overworld;
    gMain.newKeys = gMain.heldKeys = 0;
    gMain.inBattle = FALSE;
    gPaletteFade.active = FALSE;
    gPlayerAvatar.preventStep = FALSE;
    gPlayerAvatar.tileTransitionState = T_NOT_MOVING;
    gPlayerAvatar.runningState = NOT_MOVING;
    gPlayerAvatar.transitionFlags = 0;
    gSaveBlock1Ptr->location.mapGroup = MAP_GROUP(MAP_TH12_ROUTE25_SEA_COTTAGE);
}

TEST("Three Horizons playtest13 professor call waits for safe field")
{
    MainCallback old = gMain.callback2;
    const MainCallback busy[] = {BattleCallback, NamingCallback, CB2_BagMenuFromStartMenu,
        CB2_PartyMenuFromStartMenu, CB2_LoadMap, CB2_ContinueSavedGame};
    InitEventData(); SafeField();
    TH_ResearchQueueCall(TH_CALL_ACTIVATION);
    EXPECT(!TH_ResearchTryStartPendingCall()); // Gear locked
    FlagSet(FLAG_TH13_GEAR);
    for (u32 i = 0; i < ARRAY_COUNT(busy); i++)
    {
        gMain.callback2 = busy[i];
        EXPECT(!TH_ResearchTryStartPendingCall());
        EXPECT(!ScriptContext_IsEnabled());
    }
    SafeField(); LockPlayerFieldControls();
    EXPECT(!TH_ResearchTryStartPendingCall()); // field move/cutscene lock
    SafeField(); gPlayerAvatar.preventStep = TRUE;
    EXPECT(!TH_ResearchTryStartPendingCall());
    SafeField(); gMain.inBattle = TRUE;
    EXPECT(!TH_ResearchTryStartPendingCall());
    SafeField(); gPlayerAvatar.runningState = MOVING;
    EXPECT(!TH_ResearchTryStartPendingCall());
    SafeField(); gPlayerAvatar.transitionFlags = 1;
    EXPECT(!TH_ResearchTryStartPendingCall());
    SafeField(); gPaletteFade.active = TRUE;
    EXPECT(!TH_ResearchTryStartPendingCall());
    for (u32 movement = T_TILE_TRANSITION; movement <= T_TILE_CENTER; movement++)
    {
        SafeField(); gPlayerAvatar.tileTransitionState = movement;
        EXPECT(!TH_ResearchTryStartPendingCall());
    }
    SafeField(); gMain.newKeys = A_BUTTON;
    EXPECT(!TH_ResearchTryStartPendingCall());
    SafeField(); gMain.heldKeys = DPAD_UP;
    EXPECT(!TH_ResearchTryStartPendingCall());
    SafeField(); gSaveBlock1Ptr->location.mapGroup = 0;
    EXPECT(!TH_ResearchTryStartPendingCall());
    // Even a running script without a control lock must not be overwritten.
    SafeField(); ScriptContext_Enable(); UnlockPlayerFieldControls();
    EXPECT(!TH_ResearchTryStartPendingCall());
    SafeField(); EXPECT(TH_ResearchTryStartPendingCall());
    EXPECT(ArePlayerFieldControlsLocked()); EXPECT(ScriptContext_IsEnabled());
    EXPECT(!TH_ResearchCallDelivered(TH_CALL_ACTIVATION));
    EXPECT(!TH_ResearchTryStartPendingCall()); // rapid second dispatch
    SafeField(); gMain.callback2 = old;
}

TEST("Three Horizons playtest13 professor call stays pending until delivered")
{
    MainCallback old = gMain.callback2;
    u8 saved[NUM_FLAG_BYTES];
    InitEventData(); FlagSet(FLAG_TH13_GEAR);
    for (s32 call = TH_RESEARCH_CALL_COUNT - 1; call >= TH_CALL_ACTIVATION; call--)
        EXPECT(TH_ResearchQueueCall(call));
    memcpy(saved, gSaveBlock1Ptr->flags, sizeof(saved));
    InitEventData(); memcpy(gSaveBlock1Ptr->flags, saved, sizeof(saved));
    const u16 order[] = {TH_CALL_ACTIVATION, TH_CALL_ELM, TH_CALL_BIRCH, TH_CALL_ROUTE10, TH_CALL_LAVENDER};
    for (u32 i = 0; i < ARRAY_COUNT(order); i++)
    {
        u32 call = order[i];
        SafeField(); EXPECT(TH_ResearchTryStartPendingCall());
        EXPECT_EQ(TH_ResearchNextPendingCall(), call);
        EXPECT(!TH_ResearchCallDelivered(call));
        // Interrupted field session: no receipt was written; it remains pending.
        SafeField(); EXPECT(TH_ResearchTryStartPendingCall());
        gSpecialVar_0x8004 = call; TH_ScriptResearchCompleteCall();
        EXPECT(TH_ResearchCallDelivered(call));
        EXPECT(!TH_ResearchQueueCall(call));
    }
    SafeField(); EXPECT(!TH_ResearchTryStartPendingCall());
    EXPECT(!ScriptContext_IsEnabled());
    gMain.callback2 = old;
}

TEST("Three Horizons RC2 queued calls wait for resumed travel and survive cold pacing reset")
{
    MainCallback old = gMain.callback2;
    InitEventData(); SafeField(); FlagSet(FLAG_TH13_GEAR);
    TH_ResearchQueueCall(TH_CALL_ELM); TH_ResearchQueueCall(TH_CALL_BIRCH);
    EXPECT(TH_ResearchTryStartPendingCall());
    gSpecialVar_0x8004 = TH_CALL_ELM; TH_ScriptResearchCompleteCall();
    ScriptContext_Init(); UnlockPlayerFieldControls();
    for (u32 frame = 0; frame < 180; frame++) EXPECT(!TH_ResearchTryStartPendingCall());
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_CALL_BIRCH);
    gSaveBlock1Ptr->pos.x += 8;
    EXPECT(TH_ResearchTryStartPendingCall());
    // Cold Continue resets RAM pacing, never the receipt or pending report.
    ScriptContext_Init(); UnlockPlayerFieldControls(); TH_ResearchResetCallPacing();
    EXPECT(TH_ResearchCallDelivered(TH_CALL_ELM));
    EXPECT_EQ(TH_ResearchNextPendingCall(), TH_CALL_BIRCH);
    EXPECT(TH_ResearchTryStartPendingCall());
    SafeField(); gMain.callback2 = old;
}
#endif
