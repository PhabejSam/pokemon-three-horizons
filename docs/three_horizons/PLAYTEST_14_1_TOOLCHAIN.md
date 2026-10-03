# PT14.1 Windows host-tool recovery — 2026-10-02

The interrupted baseline attempt invoked Windows x86-64 MinGW host tools without the matching runtime directory on the child process PATH. Windows returned `0xC0000135` (missing dependency). The initial host run therefore had 15 failures and one error; it is not a passing baseline. The next attempt was interrupted and is also not counted as complete.

## Exact tools and installed dependencies

Worktree: `C:/Users/phabe/Documents/Codex/2026-09-22/referenced-chatgpt-conversation-this-is-an/work/playtest14-1-stabilization`.

- `tools/mapjson/mapjson.exe`: imports `libstdc++-6.dll` and `libgcc_s_seh-1.dll`.
- `tools/gbagfx/gbagfx.exe`: imports `libpng16-16.dll`.
- All three DLLs already exist in `C:/Users/phabe/Documents/Codex/pt13-review-tools-20261001/msys64/mingw64/bin`.
- Transitive dependencies `libwinpthread-1.dll` and `zlib1.dll` also exist there.

PE architecture is x86-64 throughout. The dependency hashes match the local MSYS2 package manifests, which record SHA-256 and PGP validation. Packages: libgcc/libstdc++ 16.2.0-4, libpng 1.6.59-1, zlib 1.3.2-2, libwinpthread 14.0.0.r426.g4564ee4b5-1.

This uses the established Three Horizons portable MSYS2/MinGW64 plus ARM GNU13.2 workflow documented in the PT14 development notes. The inherited generic upstream MSYS2 installation page does not describe this project-specific workflow. No Linux/WSL switch was made.

## Fix and launch verification

1. Stopped the active host-test run and preserved its logs and temporary state.
2. Inspected PE imports and verified installed dependencies without executing the broken programs again.
3. Preserved copies/hashes of both prebuilt tools, then rebuilt each from this worktree's current source using its existing Makefile and installed MinGW64 GCC/G++ 16.2.0.
4. Added a private command wrapper that prepends normalized Windows paths for `msys64/mingw64/bin` and `msys64/usr/bin` to the child process PATH. Bash build scripts retain `/mingw64/bin:/usr/bin` first. Each invocation supplies the environment explicitly; it does not depend on a previous shell call retaining PATH.
5. Set `PYTHONUTF8=1` for child test processes. Five Celadon tests initially encountered Windows CP1252 decoding errors reading UTF-8 dialogue; the affected 11-test module passed after this setting.
6. Verified **mapjson exit 0** generating nonempty native layout assembly/header files.
7. Verified **gbagfx exit 0** twice: the Mother's Watch PNG rebuilt to byte-identical existing 4bpp tiles and GBA palette.

The affected focused run executed 48 tests: 43 passed and five failed only on the separate encoding issue. The subsequent 11-test Celadon module passed, covering all five encoding errors. Thus all 48 distinct affected checks have passing results across the two runs; this is not a claim of one all-green 48-test run or of full-suite acceptance.

No dependency downloads, package installation, arbitrary DLL copying, global PATH modification, assertion weakening, or game-source changes were required for this repair. Only generated host executables, private environment/evidence helpers, this note, and the existing uncommitted PT14.1 plan are involved. Original ROMs, battery saves, PT14 outputs, source changes and unrelated temporary state are preserved. The initial failed and interrupted runs remain recorded as such.

Private evidence: `.superpowers/sdd/2026-10-02-playtest14-1-stabilization/host-runtime/{audit.json,rebuild.log,smoke.json,focused.log,utf8-focused.log}`. The private wrapper is `.superpowers/with-host-runtime.py`; all remaining host-test commands must use it (or an explicitly equivalent environment).

After these launch/focused gates, execution resumed at Task 1's unchanged-source production reproduction gate. Later PT14.1 feature, full integration and hardware results must be recorded separately; this runtime repair alone does not establish them.

Fresh unchanged production build completed with exit0; ROM SHA-256: 7e9e18bcb30026a47c9e46e187f8a1ba906e431682eb704b48c2ed8fd67a77a7, exactly matching the preserved PT14 candidate. Build log: private baseline-production.log. This verifies the baseline independently of cached Windows host binaries.
