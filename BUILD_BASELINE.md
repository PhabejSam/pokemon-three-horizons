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
sudo apt-get install -y --no-install-recommends build-essential binutils-arm-none-eabi gcc-arm-none-eabi libnewlib-arm-none-eabi libpng-dev pkg-config python3
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

The Windows attempt stopped before compilation because `make` is not installed.
WSL is also not installed on that machine. GitHub workflows have now been enabled;
the Linux baseline build is pending. Update this section only from the completed
run's evidence.

A linker warning about a LOAD segment with RWX permissions is shown as normal
in upstream INSTALL.md; report any actual warnings from the completed build.
A successful build establishes compilation, not emulator or gameplay validation.
Package versions may change in Ubuntu repositories, so retain the environment
record with each build.

## Next milestone

Once the build passes, perform an emulator smoke test of the untouched ROM:
boot, start a game, enter the overworld, and save/reload. Then agree on the first
small Three Horizons gameplay milestone before implementing it.
