# mGBA

## Windows runtime setup

The x86-64 Windows runner also needs `libwinpthread-1.dll` and
`libepoxy-0.dll`. A shell with MSYS2's `mingw64/bin` on PATH may find them,
but direct launches otherwise fail before any test executes.

Use the project's installed MSYS2 toolchain to install verified local copies
beside the runner (replace the root below with the actual installation):

```powershell
python tools/three_horizons/setup_windows_test_runtime.py --msys2-root C:/msys64 --check
python tools/three_horizons/setup_windows_test_runtime.py --msys2-root C:/msys64
```

This validates each DLL against the installed package's checksum manifest and
signature-validation record, checks matching architecture, and refuses to
overwrite a different existing DLL. It does not download libraries or modify
ROMs, saves, the runner executable, or the machine's PATH. DLL copies are local
build dependencies and are not committed. Never use third-party DLL sites.

A Windows loader error means the test process did not run; it is not a test
pass. Verify the runner's exit code and native PASS/FAIL records after setup.

The binaries in this folder are built from `mGBA`, an emulator for running Game Boy Advance games. The source code is available here: <https://github.com/mgba-emu/mgba>.
The source code for these specific builds is available from:

 - Windows: <https://github.com/mgba-emu/mgba/tree/7ee2be6c96222dca12a9a579b747fe5ff1829def>
 - Linux: <https://github.com/mgba-emu/mgba/tree/dbffb46c4e7d2e7a2cbed7c3488cece4c2176d4c>
 - Mac: <https://github.com/mgba-emu/mgba/tree/daf01b03d5316dac966acd4b05318a225cab12f5>
