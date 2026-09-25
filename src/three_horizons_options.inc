// Second page of the native Options menu; task fields are temporary until exit.
#if THREE_HORIZONS
static void TH_DrawOptions(u8 taskId)
{
    static const u8 *const labels[] = {
        COMPOUND_STRING("AUTO-RUN"), COMPOUND_STRING("EXPERIENCE"),
        COMPOUND_STRING("FOLLOWER"), COMPOUND_STRING("DAY / NIGHT"),
        COMPOUND_STRING("SHINY ODDS"), COMPOUND_STRING("SAVE AND EXIT")};
    static const u8 *const rates[] = {
        COMPOUND_STRING("1x"), COMPOUND_STRING("2x"),
        COMPOUND_STRING("4x"), COMPOUND_STRING("8x")};
    const u8 *values[5];
    u32 i;
    values[0] = gTasks[taskId].tTHAutoRun ? COMPOUND_STRING("ON") : COMPOUND_STRING("OFF");
    values[1] = rates[gTasks[taskId].tTHExpRate];
    values[2] = gTasks[taskId].tTHFollowerOff ? COMPOUND_STRING("OFF") : COMPOUND_STRING("ON");
    static const u8 *const odds[]={COMPOUND_STRING("Normal"),COMPOUND_STRING("1/1024"),COMPOUND_STRING("1/512"),COMPOUND_STRING("1/256")};
    values[3]=gTasks[taskId].tTHClock ? COMPOUND_STRING("Fast 24x") : COMPOUND_STRING("Real time");
    values[4]=odds[gTasks[taskId].tTHShiny];
    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, COMPOUND_STRING("OPTIONS  2/2     L/R: PAGE"), 8, 1, TEXT_SKIP_DRAW, NULL);
    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < ARRAY_COUNT(labels); i++)
    {
        AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, labels[i], 8, i * 16 + 1, TEXT_SKIP_DRAW, NULL);
        if (i < ARRAY_COUNT(values))
            AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, values[i], 136, i * 16 + 1, TEXT_SKIP_DRAW, NULL);
    }
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_SMALL, COMPOUND_STRING("LEFT/RIGHT: CHANGE  B: EXIT"), 8, 97, TEXT_SKIP_DRAW, NULL);
    HighlightOptionMenuItem(gTasks[taskId].tMenuSelection);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static bool32 TH_ProcessOptions(u8 taskId)
{
    if (JOY_NEW(L_BUTTON | R_BUTTON))
    {
        gTasks[taskId].tTHPage ^= 1;
        gTasks[taskId].tMenuSelection = 0;
        if (gTasks[taskId].tTHPage)
            TH_DrawOptions(taskId);
        else
        {
            DrawHeaderText();
            DrawOptionMenuTexts();
            TextSpeed_DrawChoices(gTasks[taskId].tTextSpeed);
            BattleScene_DrawChoices(gTasks[taskId].tBattleSceneOff);
            BattleStyle_DrawChoices(gTasks[taskId].tBattleStyle);
            Sound_DrawChoices(gTasks[taskId].tSound);
            ButtonMode_DrawChoices(gTasks[taskId].tButtonMode);
            FrameType_DrawChoices(gTasks[taskId].tWindowFrameType);
            HighlightOptionMenuItem(0);
            CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        }
        return TRUE;
    }
    if (!gTasks[taskId].tTHPage)
        return FALSE;
    if (JOY_NEW(B_BUTTON) || (JOY_NEW(A_BUTTON) && gTasks[taskId].tMenuSelection == 5))
        gTasks[taskId].func = Task_OptionMenuSave;
    else if (JOY_NEW(DPAD_UP))
        gTasks[taskId].tMenuSelection = (gTasks[taskId].tMenuSelection + 5) % 6;
    else if (JOY_NEW(DPAD_DOWN))
        gTasks[taskId].tMenuSelection = (gTasks[taskId].tMenuSelection + 1) % 6;
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        switch (gTasks[taskId].tMenuSelection)
        {
        case 0: gTasks[taskId].tTHAutoRun ^= 1; break;
        case 1: gTasks[taskId].tTHExpRate = (gTasks[taskId].tTHExpRate + (JOY_NEW(DPAD_RIGHT) ? 1 : 3)) % 4; break;
        case 2: gTasks[taskId].tTHFollowerOff ^= 1; break;
        case 3: gTasks[taskId].tTHClock ^= 1; break;
        case 4: gTasks[taskId].tTHShiny = (gTasks[taskId].tTHShiny+(JOY_NEW(DPAD_RIGHT) ? 1 : 3))%4; break;
        }
    }
    else
        return TRUE;
    TH_DrawOptions(taskId);
    return TRUE;
}
#endif
