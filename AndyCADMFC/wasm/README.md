WASM Build

This folder holds scripts and stubs for the WASM build.

Steps:
1) Install and activate Emscripten (emsdk).
2) Run:
   ./wasm/build_wasm.sh

Notes:
- CDC_WASM is a stub backend that should be wired to Canvas/WebGL.
- Use -DANDYCAD_WASM=ON to switch platform behavior in CMake.
- Output: wasm/build/andycad_wasm.html (plus .js/.wasm files).
