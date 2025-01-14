# X0V OpenGL Renderer

This repository documents my journey in low-level graphics programming with OpenGL and C++, focusing on the creation of a general-purpose rendering engine. While the engine is currently applied to render voxels as part of a Minecraft-inspired project, its design and functionality aim to be flexible and extendable for various use cases. This means there are no gameplay elements planned, voxel-engine related features are currently postponed indefinitely, as the scope of this project has shifted to a general purpose renderer, using minecraft blocks as the visual representation of choice (for now).

## Libaries

Libraries used currently:

- `glad` to receive OpenGL function pointers
- `glfw` to create and manage application windows with an opengl context on different platforms
- `glm` for vector and matrix calculations
- `stbi` to handle texture image loading

## Current Screenshot

![img](https://i.imgur.com/HOazaBC.png)

## Features

* [X] Textures
* [X] Camera
* [X] Meshes
* [X] Materials
* [X] RenderEntities
* [X] Proper cube texturing
* [X] BlockRegistry
* [ ] Frustrum Culling
* [X] Diffuse / Specular Lighting
* [X] Emissive Textures
* [X] Colored LightScene
* [X] Lighting Abstraction
* [X] Light culling
* [X] Arbitrary light numbers
* [X] Arbitrary light optimization (single UBO)
* [ ] Scene Graph
* [ ] 3D Object loading (.obj, .fbx)
* [ ] PBR
* [ ] Batch Rendering
