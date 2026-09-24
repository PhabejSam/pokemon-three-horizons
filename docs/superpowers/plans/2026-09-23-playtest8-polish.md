# Playtest 8 polish implementation plan

Use superpowers:executing-plans for inline implementation in the existing isolated feature/opening-demo worktree.

Goal: address the user's Playtest 7 report, preserve existing saves, and add battle-time evolution.

Spec: the user's latest playtest report and explicit reply authorizing evolution during battle. Title remains Pokémon: Three Horizons. Keep reusable Escape Rope and trainer-blocked balls unconsumed.

- [x] Field scenes: implemented and map/collision contracts passed. Visual scene timing remains in the beta checklist.
- [x] Training: reusable TMs and native Gen6 party EXP Share delivered as an eighth one-time PC item. Old-mask migration, duplicate prevention and item properties passed engine tests; party experience on/off is a manual beta check.
- [x] Evolution: native scene and battle rebuild implemented. Confirm/cancel, active/reserve party, Everstone, callback/music restoration and temporary effects passed engine tests. Complete battle-to-next-opponent visual playback remains a beta check.
- [ ] Presentation: illustrated grouped professors and mountain/starter title. Image generation was rejected by service safety review; do not retry or circumvent. Existing native portrait/layout improvements may proceed; record unavailable illustration honestly.
- [x] 23 host checks, 45 engine tests, four save tests, five negative controls, compiled inspections and compatibility builds passed. Independent review repairs verified. Separate Playtest 8 package created with a beta checklist; old ROMs/saves preserved and PR remains a draft.

Rulings: existing user requests authorize these changes without another design approval. No new map expansion in this polish pass. Artwork generation failure is an external blocker for the requested new illustration, not a reason to stop unrelated fixes.
