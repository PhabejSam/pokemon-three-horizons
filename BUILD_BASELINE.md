# Three Horizons: clean build baseline

## Source and scope

Repository: https://github.com/PhabejSam/pokemon-three-horizons  
Upstream: https://github.com/rh-hideout/pokeemerald-expansion  
Baseline commit: `c93efe865f20eafd6b48751d13b14c087c330880`  
README version: pokeemerald-expansion 1.17.0.

This setup task changes no gameplay, maps, Pokemon data, trainers, scripts,
graphics, story, or balance. The baseline workflow checks out the exact original
commit; this note and the workflow are not part of the source being compiled.

## Reproduce on Ubuntu 24.04 / Ubuntu in WSL

Windows requires WSL for this version: the repository's MSYS2 and Cygwin guides
explicitly mark those environments as nonworking. Follow
[the upstream WSL instructions](docs/install/windows/WSL.md) if needed.
WSL installation can require administrator access and a Windows restart.
For WSL2, keep the checkout in the Linux filesystem.

In Ubuntu, run:

```bash
sudo apt-get update
sudo apt-get install -y --no-install-recommends build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi libpng-dev pkg-config python3 git
git clone https://github.com/PhabejSam/pokemon-three-horizons.git
cd pokemon-three-horizons
git switch --detach c93efe865f20eafd6b48751d13b14c087c330880
set -o pipefail
make -j2 -O all 2>&1 | tee build-baseline.log
test -s pokeemerald.gba
sha256sum pokeemerald.gba
git diff --exit-code
```

Use a fresh clone for the untouched baseline. On a previously built disposable
checkout, `make clean` removes build products before rebuilding.
The default output is `pokeemerald.gba` in the repository root.
Do not use `make compare` to validate Expansion against the original retail ROM.
No retail ROM download is part of this setup.

## GitHub build

The separate `.github/workflows/baseline-build.yml` uses Ubuntu 24.04, no build
cache, the dependencies above, and the default Emerald target. It records package
versions, the build log, ROM size, and SHA-256, then retains the ROM, ELF, map,
and evidence in the `untouched-emerald-c93efe8` artifact for 14 days.

The workflow runs when its file is pushed to `setup/clean-build-baseline`.
After it is merged into the default branch, it can also be run manually from
Actions. Its source commit is intentionally fixed: use the existing upstream
CI for later gameplay changes. No upstream build files need replacement.

## Verification status

**Succeeded on 2026-09-23 UTC** in
[baseline run 35801436937](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35801436937).
The default `make -j2 -O all` completed successfully, and both tracked-file diff
checks passed. No existing repository files were changed.

- Output: `pokeemerald.gba`, 33,554,432 bytes (32 MiB, padded).
- ROM SHA-256: `014b52eb7b85f8d0ae18623a5d1da55e3a1608e2c9ed653908b83b1128b5a291`.
- Linked memory use: EWRAM 226,416 bytes (86.37%), IWRAM 28,376 bytes
  (86.60%), ROM 26,749,476 bytes (79.72%).
- Environment: Ubuntu 24.04.5, GNU Make 4.3, host GCC 13.3.0,
  ARM GCC 13.2.1 (package `15:13.2.rel1-2`), ARM binutils 2.42,
  newlib `4.4.0.20231231-2`, libpng `1.6.43-5ubuntu0.6`, Python 3.12.3.
- [Artifact: untouched-emerald-c93efe8](https://github.com/PhabejSam/pokemon-three-horizons/actions/runs/35801436937/artifacts/10726845320).
  The downloaded archive and extracted ROM checksums were independently verified.

Warnings: 209 `libpng warning: bKGD: invalid index` messages and 3
`libpng warning: iCCP: known incorrect sRGB profile` messages. These did not
prevent compilation; the source graphics were left unchanged. GitHub also warned
that the v4 checkout/upload actions target deprecated Node 20 and were run under
Node 24. Both actions succeeded. No compiler/linker warnings were found in this
build log.

The first new workflow run failed before compilation because its clean-source
assertion followed creation of the environment report. Moving the assertion
ahead of that report fixed this setup-only issue; no upstream source fix was
needed.

The local Windows attempt stopped before compilation because `make` is absent;
WSL is also not installed. Local compilation remains unavailable until WSL/Ubuntu
and the listed dependencies are installed. The verified baseline was built on
GitHub's Linux runner. A successful build establishes compilation, not emulator
or gameplay validation. Package versions may change in Ubuntu repositories, so
retain the environment record with each build.

## Next milestone

Perform an emulator smoke test of the untouched ROM:
boot, start a game, enter the overworld, and save/reload. Then agree on the first
small Three Horizons gameplay milestone before implementing it.
