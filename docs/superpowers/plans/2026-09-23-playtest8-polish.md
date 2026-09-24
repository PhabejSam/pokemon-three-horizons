# Playtest 8 polish implementation plan

Use superpowers:executing-plans for inline implementation in the existing isolated feature/opening-demo worktree.

Goal: address the user's Playtest 7 report, preserve existing saves, and add battle-time evolution.

Spec: the user's latest playtest report and explicit reply authorizing evolution during battle. Title remains Pokémon: Three Horizons. Keep reusable Escape Rope and trainer-blocked balls unconsumed.

- [ ] Field scenes: preserve regional starter displays, refresh first follower after handoff, group professors without blocking Oak's paths, restore Center machine animation, suppress indoor map popup, individual NPC/object/trainer dialogue. Verify collision paths and map/script contracts.
- [ ] Training: enable reusable TMs and native Gen6 party EXP Share, delivered as an eighth one-time PC kit item; preserve old seven-bit masks and allocate unused persistent flag. Test old-save migration, no duplicate deliveries, item properties and experience eligibility.
- [ ] Evolution: pause after earned level-up and learned moves; use native evolution/cancel/move-learning flow and restore battle state, graphics, music and active battler data. Preserve status/volatile effects and PP. Test evolution, cancel, Everstone, inactive party members and continued battle.
- [ ] Presentation: illustrated grouped professors and mountain/starter title. Image generation was rejected by service safety review; do not retry or circumvent. Existing native portrait/layout improvements may proceed; record unavailable illustration honestly.
- [ ] Run host/engine/save/build checks, independent final review, package a separate Playtest 8 ROM and beta checklist, preserve previous ROMs and saves. Do not merge the draft PR.

Rulings: existing user requests authorize these changes without another design approval. No new map expansion in this polish pass. Artwork generation failure is an external blocker for the requested new illustration, not a reason to stop unrelated fixes.
