# Road to OpenGL

This repository documents my journey of learning low-level graphics programming with OpenGL and C++.

It started out by following the excellent book "Learn OpenGL" ([learnopengl.com](https://learnopengl.com/ "learnopengl.com")) and then starting to deviate from it with own abstractions of common concepts while also moving from Visual Studio 2019 to a VSCode setup to unify with the DX i am used to from my day job and other personal projects.

## Libaries

Libraries used currently:

- `glad` to receive OpenGL function pointers
- `glfw` to create and manage application windows with an opengl context on different platforms
- `glm` for vector and matrix calculations
- `stbi` to handle texture image loading
