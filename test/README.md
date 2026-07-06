# TenTrillion Game Engine Testing Utility

This utility is used to test the TenTrillion in various different ways. It is directly linked against the TenTrillion
itself, and it will test tons of needed attributes about the engine.

> This program must be executed under a machine that has an active X Session or Wayland session, as it will
> do graphics
> testing, along with sound testing and performance testing. This means it cannot be run in a GitHub Action.

## Building

This section of the TenTrillion's build, will be handled by the root `CMakeLists.txt` file itself. This section needs to
be linked against the TenTrillion Library/DLL file.
