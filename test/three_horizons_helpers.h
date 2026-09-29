#ifndef GUARD_THREE_HORIZONS_TEST_HELPERS_H
#define GUARD_THREE_HORIZONS_TEST_HELPERS_H

struct Trainer;
// The battle test runner replaces gTrainers. Use the generated release data
// for assertions about authored Three Horizons trainer records.
const struct Trainer *TH_TestGetActualTrainer(u16 trainerId);

#endif
