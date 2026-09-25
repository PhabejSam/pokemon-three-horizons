#include "global.h"
#include "three_horizons.h"
#if THREE_HORIZONS
// Diagnostic checkpoint: the regression must expose the missing migration.
void TH_MigrateSaveState(void) {}
#endif
