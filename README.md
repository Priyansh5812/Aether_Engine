# Aether
Aether is a Windows-only C++20 engine/framework skeleton built as a shared library, with a separate Sandbox console app for local experiments and benchmarks.

## What Is In This Repo

- `Aether` shared library target
- `Sandbox` console app target
- Logging wrappers around `spdlog`
- Delegate/event helpers: `Delegate`, `Action`, and `Func`
- Premake-based project generation for Visual Studio 2022

## Features

- Windows-only shared library export/import via `AE_API`
- Colorized logging with `Debug` and `EDebug`
- Simple callback binding for free functions and member functions
- Header-only `spdlog` integration
- Sandbox entrypoint pattern through `Aether.h`

## Repository Layout

```text
Aether/
├─ Aether/                  # Engine source
├─ Sandbox/                 # Client sandbox app
├─ ThirdParty/              # Tools and dependencies
├─ premake5.lua             # Workspace definition
├─ ProjectGen.bat           # Premake launcher
├─ Aether.sln               # Generated solution
└─ LICENSE
```

## Requirements

- Windows 10/11
- Visual Studio 2022 with the Desktop development with C++ workload
- Premake 5 executable at `ThirdParty/bin/premake/premake5.exe`
- Git submodules initialized

## Setup

1. Clone the repository.
2. Initialize dependencies:
   ```bat
   git submodule update --init --recursive
   ```
3. Generate the solution:
   ```bat
   ProjectGen.bat
   ```
   or run Premake directly:
   ```bat
   ThirdParty\bin\premake\premake5.exe vs2022
   ```
4. Open `Aether.sln` in Visual Studio 2022.
5. Build one of the available configurations:
   - Debug
   - Release
   - Dist

## Running The Sandbox

`Sandbox` is the client application that links against `Aether`. The current `main.cpp` shows the expected pattern:

```cpp
#include <Aether.h>

class Sandbox : public Aether::Application
{
};

Aether::Application* Aether::CreateApplication()
{
    return new Sandbox();
}
```

The sandbox currently runs a benchmark comparing `std::function` with the custom `Action` delegate system before entering the application loop.

## Logging

`Aether::EDebug` is used for engine-side logs and `Aether::Debug` is used for client-side logs.

Available helpers:

- `Log(...)`
- `LogWarning(...)`
- `LogError(...)`

## Event System

The event system lives under `Aether::EventSystems` and includes:

- `Delegate` for binding free functions and member functions
- `Action` for `void` callbacks
- `Func` for non-void callbacks

## Notes

- The project is Windows-only.
- `Application::Run()` is currently a placeholder loop; replace it with your real game or app loop.
- `bin/` and `bin-int/` are generated output folders.
- `spdlog` is vendored under `Aether/src/ThirdParty/spdlog` and used header-only by the build scripts.

## License

MIT License. See [LICENSE](LICENSE).
