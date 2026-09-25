# Playtest 9 repair — focused beta pass

This repair keeps the existing story and save layout. It does not add a chapter.
The compiled source revision is `a2ebbd69160cc32fd55926bd33c141aa7cc38840`.

## Changes

- Blue enters the original introduction stage, with the same background,
  platform and dialogue frame as the player, before the rival naming screen.
- On the first lab visit, the player walks to `(5,5)` beside the rival before
  Oak welcomes them. The path is checked against the actual map and objects.
- The first rival loss no longer invokes FireRed's Oak tutorial overlay in
  the Emerald battle scene. The shipped ROM reproduced the dim-screen pause.
- Options page 2 uses one help line that fits inside the window.
- Leaving the naming screen now retires its interrupt callbacks, tasks,
  sprites and background tilemap references before freeing its working data.
  The main naming callback also stops processing that retired scene.

## Capture-crash status

The reported `INVALID ITEM: 4365` assertion was mapped to the caught-Pokemon
handoff. The exact assertion has **not** been reproduced in the local emulator.
Repeated long-name captures in the shipped ROM succeeded, including captures
after a rival loss and with increased experience. This is not evidence that
the reported crash was harmless or absent.

A separate, concrete defect was reproduced: after nickname entry returned to
battle, its VBlank callback still referenced the freed naming-screen data.
The repair removes that invalid lifetime. A native regression checks cleanup
with party space and with a full party, while also checking the battle's held
item state. A negative control deliberately restores the stale callback and
must make that regression fail. The invalid-item assertion remains enabled.

## What to test

1. Back up your in-game save. Use the new ROM with an in-game save or a fresh
   game, rather than loading an emulator save state made by another build.
2. For the opening checks, start a separate fresh game. Confirm Blue appears
   on the intro stage, can be named, and the player reaches his side in the lab.
3. Intentionally lose the first rival battle. Confirm the post-battle dialogue,
   healing and rival departure finish without the long dim-screen pause.
4. Open Options page 2, change a setting and exit. Check that the bottom help
   text is completely visible and the chosen setting stays selected.
5. **Save immediately before the first capture.** Catch Pidgey, enter exactly
   `AAAAAAAAAA`, confirm, inspect its name in the party, then save and reload.
   Also try another capture with no nickname. Your brother can prioritize this
   on the Anbernic while you check it in desktop mGBA.
6. If the capture fails again, preserve the save from immediately before it.
   Record the ROM filename, emulator/core, starter level, experience setting,
   whether anyone leveled or evolved during the catch, and the error screen.

No user save or emulator settings are replaced by this package. To continue an
existing save, keep a backup and use your emulator's normal save-import method,
or copy the save with the new ROM's matching base filename in its save folder.
The Anbernic's save folder depends on its firmware and selected emulator core.

## Verification record

- [Repair build and tests](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36087116832)
  succeeded: 33 host checks, 58 Three Horizons engine tests, four save-layout
  checks, deliberate-defect controls including the new nickname case, and
  trainer build-mode switching. No save structure changed.
- [Compatibility run](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/36087120521)
  passed Emerald, FireRed, LeafGreen, release and upstream engine tests. Its
  documentation check exposed the missing repair-plan index entry; the final
  documentation commit adds both new pages and passes the same check locally.
- The shipped ROM's rival loss reproduced `PrintOakText_HowDisappointing`.
  The presentation repair (`d4a9ab5`) completed an intentional loss and
  departure without ever entering that callback. The lab endpoint and complete
  Options footer were also inspected in that ROM.
- The final `a2ebbd6` ROM was booted from a fresh game: Blue's stage, player and
  rival naming, and arrival in the bedroom passed. A separate in-game Route 1
  save loaded successfully. Options used auto-run, 8x EXP, follower, 24x visual
  clock and 1/256 shiny odds, matching the reported settings.
- Actual captures of Rattata and Pidgey were each named `AAAAAAAAAA` through
  the keyboard. The starter leveled from 5 to 8 on the first catch and to 9,
  with move learning, on the Pidgey catch. Both returned to the field; the
  nickname-state pointer and its VBlank callback were both null at handoff.
  An in-game save was then loaded in a new emulator session; both names and
  party members remained present.
- These interactive checks used the mGBA Libretro Windows core, not the
  tester's exact mGBA 0.10.5 build or physical RG40XX H. They do not reproduce
  every condition of the original Pidgey-first crash or constitute a full
  story traversal. Hardware acceptance remains outstanding.
- The ROM is 33,554,432 bytes. SHA-256:
  `62a0ceef964454bf6274215802ddae8ae5f4657bfa5acd67875995fdc5a98e89`.
  Build warnings remain for PNG metadata and the unused original boy/girl
  introduction function. They did not prevent compilation.
