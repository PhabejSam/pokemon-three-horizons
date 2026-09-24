#ifndef GUARD_CONSTANTS_THREE_HORIZONS_H
#define GUARD_CONSTANTS_THREE_HORIZONS_H

// TH-only replacements for unreachable Hoenn trainers; save flag capacity is unchanged.

// Audited unused Emerald event slots; no save-block layout changes.
#define VAR_TH_STAGE           0x40F7
#define VAR_TH_FIRST_PARTNER   0x40F8
#define VAR_TH_RIVAL_PARTNER   0x40F9
#define VAR_TH_SUPPLY_MASK     0x40FA
#define VAR_TH_SIGHTING_SEEN   0x40FB
#define VAR_TH_OUTFIT          0x40FC
#define VAR_TH_EXP_RATE        0x40FD
#define VAR_TH_AUTO_RUN        0x40FE
#define VAR_TH_FOLLOWER_OFF    0x40FF
#define VAR_TH_RIVAL_NAME_0    0x404E
#define VAR_TH_RIVAL_NAME_1    0x4083
#define VAR_TH_RIVAL_NAME_2    0x408B
#define VAR_TH_RIVAL_NAME_3    0x4091
#define VAR_TH_TRAINING_KIT_MASK 0x409B
#define TH_OUTFIT_RED          0
#define TH_OUTFIT_LEAF         1
#define TH_OUTFIT_BRENDAN      2
#define TH_OUTFIT_MAY          3
#define TH_OUTFIT_GOLD         4
#define TH_OUTFIT_KRIS         5
#define TH_OUTFIT_SILVER       6
#define TH_OUTFIT_COUNT        7
#define TH_STAGE_HOME          0
#define TH_STAGE_INVITED       1
#define TH_STAGE_PARTNER       2
#define TH_STAGE_BATTLE_DONE   3
#define TH_STAGE_COMPLETE      4
#define TH_SUPPLY_BALLS        1
#define TH_SUPPLY_POTIONS      2
#define TH_SUPPLY_DEX          4
#define TH_SUPPLIES_COMPLETE   7
#define FLAG_TH_BROCK_TM FLAG_UNUSED_0x020
#define FLAG_TH_HIDE_ROBIN_TOWN FLAG_TEMP_1
#define FLAG_TH_HIDE_ROBIN_LAB  FLAG_TEMP_2
#endif
