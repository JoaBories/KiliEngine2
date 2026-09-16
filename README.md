# KiliEngine II

## Disclaimer 🚨
I decided to rebuild **[Kili Engine I](https://github.com/JoaBories/KiliEngine)** to restart on good basis so for now some important part of the engine are missing or incomplete.
Like the previous version this engine is a personal and school project so it is heavily subject to change. APIs or file structure may change drastically during development.

## Build instruction
I use premake5 for project generation.
You can generate a Visual Studio solution (`.sln` and `.vcxproj`) using `GenerateSolution.bat`.
But you can also use any build supported by premake5. Note that I didn't test them.

## Roadmap 🗺️
This is a roadmap representing the features I plan to implement in the engine.
I will update by adding, removing, or moving features during the project development.

- **1.0 base** - **WIP** - *Coming back to KiliEngine I in terms of features*
  - [x] Log
  - [x] Event System
  - [x] Config files
  - [ ] OpenGl rendering
  - [ ] Collisions
  - [x] Time and frame
  - [ ] Asset manager
- **1.1 voxels** - **Planned** - *A start for voxel rendering and world generation*
  - [ ] Voxel Rendering
  - [ ] Voxel Collisions
  - [ ] Procedural generation
- **More things** - **Planned** - *Features not planned at shorter or midterm*
  - [ ] Vulkan rendering
  - [ ] Multi threading
  - [ ] Support for HLSL shaders
  - [ ] Mesh blocks
  - [ ] Compute shaders for procedural generation
  - [ ] ImGui integration
