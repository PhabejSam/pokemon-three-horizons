"""Execute the production switching predicate, isolated from unrelated AI scoring."""
import re
import shutil
import subprocess
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]


def function(path, name):
    source = (ROOT / path).read_text(encoding="utf-8")
    match = re.search(r"(?:static )?(?:bool32|enum DamageCategory) " + name + r"\([^;{}]*\)\s*\{", source)
    if match is None:
        raise AssertionError(name)
    start = source.index("{", match.start())
    depth = 0
    for end in range(start, len(source)):
        depth += (source[end] == "{") - (source[end] == "}")
        if depth == 0:
            return source[match.start():end + 1]
    raise AssertionError("Unclosed production function: " + name)


HARNESS = r"""
#include <stdio.h>
typedef unsigned bool32;
#define TRUE 1
#define FALSE 0
#define AI_DEFENDING 0
enum BattlerId { SELF, OPPONENT };
enum Move { MOVE_NONE, MOVE_POUND, MOVE_HYPER_BEAM = 63, MOVE_UNAVAILABLE = 65535 };
enum DamageCategory { DAMAGE_CATEGORY_NONE, DAMAGE_CATEGORY_PHYSICAL, DAMAGE_CATEGORY_SPECIAL, DAMAGE_CATEGORY_STATUS };
static int alive = 1, damage = 0, bestPhysical = 0;
static enum Move incoming = MOVE_HYPER_BEAM;
static enum DamageCategory fallback = DAMAGE_CATEGORY_SPECIAL;
static enum DamageCategory categories[2] = {DAMAGE_CATEGORY_SPECIAL, DAMAGE_CATEGORY_PHYSICAL};
static void *gAiLogicData;
static bool32 IsBattlerAlive(enum BattlerId b) { return alive; }
static int GetBestDmgFromBattler(enum BattlerId a, enum BattlerId b, int ctx) { return damage; }
static bool32 HasPhysicalBestMove(enum BattlerId a, enum BattlerId b, int ctx) { return bestPhysical; }
static enum Move GetIncomingMove(enum BattlerId a, enum BattlerId b, void *data) { return incoming; }
static enum DamageCategory GetBattleMoveCategory(enum Move move) { return fallback; }
static enum DamageCategory GetCategoryBasedOnStats(enum BattlerId b) { return categories[b]; }
"""

MAIN = r"""
#define CHECK(wanted, label) do { \
    unsigned actual = IsOpponentPhysicalAttacker(SELF, OPPONENT); \
    if (actual != (wanted)) { fprintf(stderr, "%s: expected %u, got %u\n", label, (unsigned)(wanted), actual); return 1; } \
} while (0)
int main(void) {
    CHECK(THREE_HORIZONS ? TRUE : FALSE, "Physical incoming Hyper Beam with Special base category");
    categories[SELF] = DAMAGE_CATEGORY_PHYSICAL;
    categories[OPPONENT] = DAMAGE_CATEGORY_SPECIAL;
    CHECK(FALSE, "Special/tied opposing stats must not use self stats");
    fallback = DAMAGE_CATEGORY_PHYSICAL;
    CHECK(THREE_HORIZONS ? FALSE : TRUE, "Special Hyper Beam ignores stale Physical scratch only in TH");
    incoming = MOVE_POUND;
    CHECK(TRUE, "Ordinary Physical move preserves fallback");
    fallback = DAMAGE_CATEGORY_SPECIAL;
    CHECK(FALSE, "Ordinary Special fallback remains unchanged");
    incoming = MOVE_NONE;
    CHECK(FALSE, "No prediction");
    incoming = MOVE_UNAVAILABLE;
    CHECK(FALSE, "Unavailable prediction");
    damage = 1; bestPhysical = 1;
    CHECK(TRUE, "Existing best physical move path");
    alive = 0;
    CHECK(FALSE, "Fainted opponent");
    puts("PASS: nine production switching-predicate cases");
    return 0;
}
"""


class PredictedSwitchCategory(unittest.TestCase):
    def run_predicate(self, th):
        compiler = shutil.which("gcc") or shutil.which("cc")
        self.assertIsNotNone(compiler, "Host C compiler required; test must not be skipped")
        source = (HARNESS + function("src/battle_ai_util.c", "AI_ResolveMoveCategory")
                  + "\n" + function("src/battle_ai_switch.c", "IsOpponentPhysicalAttacker") + MAIN)
        with tempfile.TemporaryDirectory(prefix=".th-ai-switch-", dir=ROOT) as directory:
            folder = Path(directory)
            cfile = folder / "predicate.c"
            exe = folder / "predicate.exe"
            cfile.write_text(source, encoding="utf-8")
            built = subprocess.run([compiler, "-std=c11", "-O2", f"-DTHREE_HORIZONS={th}",
                                    str(cfile), "-o", str(exe)], capture_output=True, text=True)
            self.assertEqual(built.returncode, 0, built.stdout + built.stderr)
            result = subprocess.run([str(exe)], capture_output=True, text=True)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_predicted_hyper_beam_switch_category_uses_opposing_battler(self):
        self.run_predicate(1)

    def test_upstream_switch_predicate_keeps_original_fallback(self):
        self.run_predicate(0)
