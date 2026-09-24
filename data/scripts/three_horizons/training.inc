TH_TrainingClerk::
    lockall
    faceplayer
    msgbox TH_Text_TrainingWelcome
    dynmultichoice 0, 0, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, TH_Text_BuyTraining, TH_Text_ImproveIVs, TH_Text_TrainingAdvice, TH_Text_TrainingExit
    goto_if_eq VAR_RESULT, 0, TH_TrainingBuy
    goto_if_eq VAR_RESULT, 1, TH_TrainingCaps
    goto_if_eq VAR_RESULT, 2, TH_TrainingAdvice
    goto TH_TrainingEnd
TH_TrainingBuy:
    pokemart TH_TrainingStock
    goto TH_TrainingEnd
TH_TrainingAdvice:
    msgbox TH_Text_TrainingHelp
    goto TH_TrainingEnd
TH_TrainingCaps:
    getpartysize
    goto_if_eq VAR_RESULT, 0, TH_TrainingEnd
    msgbox TH_Text_ChooseTrainee
    special ChoosePartyMon
    goto_if_ge VAR_0x8004, PARTY_SIZE, TH_TrainingEnd
    copyvar VAR_0x8007, VAR_0x8004
    dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, TH_Text_SilverCap, TH_Text_GoldCap, TH_Text_TrainingExit
    goto_if_eq VAR_RESULT, 0, TH_TrainingOneStat
    goto_if_eq VAR_RESULT, 1, TH_TrainingAllStats
    goto TH_TrainingEnd
TH_TrainingAllStats:
    setvar VAR_0x8005, ITEM_GOLD_BOTTLE_CAP
    setvar VAR_0x8006, 0
    bufferstring STR_VAR_3, TH_Text_AllStats
    goto TH_TrainingConfirm
TH_TrainingOneStat:
    setvar VAR_0x8005, ITEM_BOTTLE_CAP
    dynmultichoice 0, 0, FALSE, 7, 0, DYN_MULTICHOICE_CB_NONE, TH_Text_StatHP, TH_Text_StatAtk, TH_Text_StatDef, TH_Text_StatSpAtk, TH_Text_StatSpDef, TH_Text_StatSpeed, TH_Text_TrainingExit
    goto_if_ge VAR_RESULT, 6, TH_TrainingEnd
    goto_if_eq VAR_RESULT, 0, TH_TrainingHP
    goto_if_eq VAR_RESULT, 1, TH_TrainingAtk
    goto_if_eq VAR_RESULT, 2, TH_TrainingDef
    goto_if_eq VAR_RESULT, 3, TH_TrainingSpAtk
    goto_if_eq VAR_RESULT, 4, TH_TrainingSpDef
    setvar VAR_0x8006, STAT_SPEED
    bufferstring STR_VAR_3, TH_Text_StatSpeed
    goto TH_TrainingConfirm
TH_TrainingHP:
    setvar VAR_0x8006, STAT_HP
    bufferstring STR_VAR_3, TH_Text_StatHP
    goto TH_TrainingConfirm
TH_TrainingAtk:
    setvar VAR_0x8006, STAT_ATK
    bufferstring STR_VAR_3, TH_Text_StatAtk
    goto TH_TrainingConfirm
TH_TrainingDef:
    setvar VAR_0x8006, STAT_DEF
    bufferstring STR_VAR_3, TH_Text_StatDef
    goto TH_TrainingConfirm
TH_TrainingSpAtk:
    setvar VAR_0x8006, STAT_SPATK
    bufferstring STR_VAR_3, TH_Text_StatSpAtk
    goto TH_TrainingConfirm
TH_TrainingSpDef:
    setvar VAR_0x8006, STAT_SPDEF
    bufferstring STR_VAR_3, TH_Text_StatSpDef
TH_TrainingConfirm:
    bufferpartymonnick STR_VAR_1, VAR_0x8007
    bufferitemname STR_VAR_2, VAR_0x8005
    msgbox TH_Text_CapConfirm, MSGBOX_YESNO
    goto_if_ne VAR_RESULT, YES, TH_TrainingEnd
    copyvar VAR_0x8004, VAR_0x8007
    special TH_ScriptImproveIVs
    goto_if_ne VAR_RESULT, TRUE, TH_TrainingNoChange
    playfanfare MUS_OBTAIN_ITEM
    msgbox TH_Text_CapDone
    waitfanfare
    goto TH_TrainingEnd
TH_TrainingNoChange:
    msgbox TH_Text_CapNoChange
TH_TrainingEnd:
    releaseall
    end

    .align 2
TH_TrainingStock:
    .2byte ITEM_POMEG_BERRY, ITEM_KELPSY_BERRY, ITEM_QUALOT_BERRY
    .2byte ITEM_HONDEW_BERRY, ITEM_GREPA_BERRY, ITEM_TAMATO_BERRY
    .2byte ITEM_LONELY_MINT, ITEM_ADAMANT_MINT, ITEM_NAUGHTY_MINT, ITEM_BRAVE_MINT
    .2byte ITEM_BOLD_MINT, ITEM_IMPISH_MINT, ITEM_LAX_MINT, ITEM_RELAXED_MINT
    .2byte ITEM_MODEST_MINT, ITEM_MILD_MINT, ITEM_RASH_MINT, ITEM_QUIET_MINT
    .2byte ITEM_CALM_MINT, ITEM_GENTLE_MINT, ITEM_CAREFUL_MINT, ITEM_SASSY_MINT
    .2byte ITEM_TIMID_MINT, ITEM_HASTY_MINT, ITEM_JOLLY_MINT, ITEM_NAIVE_MINT
    .2byte ITEM_SERIOUS_MINT, ITEM_BOTTLE_CAP, ITEM_GOLD_BOTTLE_CAP, ITEM_NONE
TH_Text_TrainingWelcome:
    .string "Welcome! I help trainers shape\nany partner's potential.$"
TH_Text_BuyTraining:
    .string "Buy supplies$"
TH_Text_ImproveIVs:
    .string "Improve IVs$"
TH_Text_TrainingAdvice:
    .string "Training advice$"
TH_Text_TrainingExit:
    .string "Cancel$"
TH_Text_ChooseTrainee:
    .string "Which partner shall we work with?$"
TH_Text_SilverCap:
    .string "One IV: Bottle Cap$"
TH_Text_GoldCap:
    .string "All IVs: Gold Cap$"
TH_Text_AllStats:
    .string "All stats$"
TH_Text_StatHP:
    .string "HP$"
TH_Text_StatAtk:
    .string "Attack$"
TH_Text_StatDef:
    .string "Defense$"
TH_Text_StatSpAtk:
    .string "Sp. Attack$"
TH_Text_StatSpDef:
    .string "Sp. Defense$"
TH_Text_StatSpeed:
    .string "Speed$"
TH_Text_CapConfirm:
    .string "Partner: {STR_VAR_1}\nIV choice: {STR_VAR_3}\pRaise to 31 using one\n{STR_VAR_2}?$"
TH_Text_CapDone:
    .string "All set! Check your partner's IVs\non the summary screen.$"
TH_Text_CapNoChange:
    .string "No changes were made. Check your caps.\nThe IVs may already be at 31.\pEggs cannot take part in training.\nYou haven't spent any items.$"
TH_Text_TrainingHelp:
    .string "Wild partners start with zero EVs.\nTheir IVs and nature usually vary.\pYour home PC holds a training kit.\nGive those items to a partner to hold.\pPower items add EVs for one stat.\nThe opponent's usual EVs still count.\pThese berries reduce unwanted EVs.\nMints change the nature used for stats.\pThe summary shows that stat nature.\nYour partner's birth nature is kept.\pBring caps to me to raise IVs to 31.\nOne silver cap improves one stat.\pOne gold cap improves all six stats.\nThere is no minimum level!$"
