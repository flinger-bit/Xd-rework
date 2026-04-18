# Xd-rework

## Overview

A rework of [xdBot](https://github.com/Zilko/xdBot) (by Zilko) — a Geometry Dash macro bot — updated for **Geode 5.6.1** and **GD 2.2081**.

The Replit project hosts the source code and a landing page. The actual `.geode` mod file is compiled via GitHub Actions on push to `main`.

## Project Structure

```
.github/workflows/build.yml   GitHub Actions CI — builds .geode file
src/
  main.cpp                    Entry point & PlayLayer/PauseLayer hooks
  includes.hpp                Shared includes and Global class declaration
  macro.hpp / macro.cpp       Macro data structure and logic
  global.cpp                  Global singleton implementation
  keybinds.cpp                Keyboard bindings (Windows)
  gdr/                        GDR replay format library
  hacks/                      Individual hack implementations
  ui/                         UI layers and popups
  practice_fixes/             Practice mode fix hooks
  renderer/                   Frame renderer (FFmpeg-based, Windows)
  utils/                      Utility helpers
resources/                    Sprites and audio files for the mod
CMakeLists.txt                CMake build configuration
mod.json                      Geode mod manifest
server.js                     Replit preview landing page (Node.js)
```

## Tech Stack

- **Language:** C++20
- **Framework:** [Geode SDK](https://geode-sdk.org/) v5.6.1
- **Game:** Geometry Dash 2.2081
- **Build:** CMake + GitHub Actions
- **Replit preview:** Node.js HTTP server on port 5000

## Building

The mod is built via GitHub Actions on every push to `main`. The workflow uses `geode-sdk/build-geode-mod@main` with SDK version `v5.6.1`.

Artifacts (`.geode` + `.pdb`) are uploaded for Windows, Linux, and macOS builds.

## Based On

- **xdBot v2.4.1** by Zilko — https://github.com/Zilko/xdBot
