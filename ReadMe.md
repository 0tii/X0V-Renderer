# X0V OpenGL Voxel Engine

This repository documents my journey in low-level graphics programming with OpenGL and C++, focusing on the creation of a general-purpose rendering engine. While the engine is currently applied to render voxels as part of a Minecraft-inspired project, its design and functionality aim to be flexible and extendable for various use cases.

## Libaries

Libraries used currently:

- `glad` to receive OpenGL function pointers
- `glfw` to create and manage application windows with an opengl context on different platforms
- `glm` for vector and matrix calculations
- `stbi` to handle texture image loading

## Current Screenshot

![img](https://i.imgur.com/FaSGmWi.png "Current state")

## Features

* [X] Textures
* [X] Camera
* [X] Meshes
* [X] Materials
* [X] RenderEntities
* [X] Proper cube texturing
* [X] BlockRegistry (extend block palette easily)
* [ ] Face Culling
* [ ] Frustrum Culling
* [X] Lighting
* [ ] World Generation
* [ ] Block placing
* [ ] Block breaking
