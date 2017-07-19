# 3DEngine

This is a 3D/2D game engine (currently only 3D supported) which uses SDL (maybe will add other frameworks) and OpenGL.

## Features

+ **Render 3D Models**
  - Materials with textures
+ **Loading 3D Models**
  - Fileformats: .obj, .dae, .fbx, .stl, .blend ...
+ **Render 2D textures**
+ **Render 2D text**
+ **3D Camera**
  - Translating
  - Rotating
+ **Skybox**
+ **Lighting** <br/>
  - Pointlights
  - Spotlights
  - Directionallights
+ **Shadows** <br/>
  - for Directionallights, Spotlights
+ **Gamepad input**
  - Complete simple to use gamepad implemantation

## Setup

### Dependencies

- SDL2 (http://www.libsdl.org)
- SDL2_ttf (https://www.libsdl.org/projects/SDL_ttf/)
- assimp (http://assimp.org/)
- OpenGL (https://www.opengl.org/)
- GLEW (http://glew.sourceforge.net/)

#### Windows - Visual Studio

1. Download dependencies from links above
2. Put the .h/.hpp and .lib files in seperate directories
3. In Visual Studio
  - link to the .h/.hpp files
  - link to the .lib files
4. Add the files of the engine to the project
5. It should compile and link

