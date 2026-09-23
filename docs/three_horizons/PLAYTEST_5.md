# Playtest 5: running and rival scenes

This repair preserves the save layout, outfit choices, starter configuration,
rival teams, experience options, and follower settings from playtest 4.

## Changes

- Gold, Kris and Silver now address their actual running image frames. Two
  relative-frame descriptors incorrectly made running read beyond the walking
  asset; the second descriptor was never used by the sprite engine.
- Red and Leaf use the FireRed running sequence rather than Emerald's differently
  ordered frames. Brendan and May retain their original animation tables.
- Pallet checks for the home greeting and lab challenge after the door transition
  completes. Each map entry is checked once; story stages prevent repeat scenes.
- The rival approaches the player at home. In the lab he walks to the regional
  Poké Ball, collects it with a fanfare and his partner's cry, then walks out.
  The player steps out of his path and the follower returns to its ball during
  the movement. The used regional display stays empty on subsequent visits.

## Focused playtest

1. Start a separate new game to see the greeting: leave home and wait without
   moving or pressing A. The rival should approach and speak, then go to the lab.
2. Choose a starter from each region on separate runs. Confirm/cancel still works;
   after confirming, the rival must collect from that same regional display and
   name the species he actually uses in battle. Test with followers enabled.
3. Leave the lab and wait without moving or pressing A. The rival should face you
   and start the first battle. Win or lose; revisiting must not repeat it.
4. Run north, south, east and west in all seven outfits, both holding B and with
   auto-run enabled. Silver still uses his walking poses at running speed: the
   available classic Silver sheet has no separate running pose set.
5. View Chikorita from the front, rear and side, including shiny. Its source sheet
   and reference classic sheet have the same compact rear silhouette. The report's
   screenshot matches that rear view; no clipped image or missing frame was found.
   No speculative sprite replacement is included. Bayleef evolution and follower
   appearance were reported working by the user on playtest 4.
6. Repeat in-game save, close emulator, reopen and Continue. Copy a previous save
   before trying it with a new ROM; preserve the original file.

## Automated evidence

The new ELF checker follows the same relative/explicit image addressing rules as
the runtime, checks four directions for every outfit, and validates all 112 running
frame reads against the intended asset bounds and frame order. It rejects the
previous playtest-4 ELF. Host checks cover scene wiring, map collisions, player
positions around each regional display, and existing departure paths.

These checks do not substitute for viewing the scenes in an emulator. This host
does not expose native emulator controls; manual playthrough results remain open.
