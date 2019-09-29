# Epoch Graphics Engnie (EGE)  Version 0.0.0.1 #

![Epoch](/lib/logos/BlackOnWhiteLogo.png?raw=true "Epoch")

## Getting Started ##
_Epoch Graphics Engine_ is in the earliest stages of development so please note that EGE is untested for other platforms. In order to get started with EGE, Microsoft Visual Studio 17 or 19 is recommended.

You can clone the repository localy by using the following git command:

`git clone --recursive https://https://github.com/jmuratov98/Epoch.git`

Note: use `--recursive` command in order to clone all of EGE's dependenices

After cloning the repository go to the folders and click `GenEpcohProj.bat` in order to generate visual studio project files

For more information [click here](https://jmuratov98.github.io/epochengine)

## The Plan ##
The plan for EGE is simple using the tutorials from [TheCherno](https://thecherno.com/engine), and [Javidx9](https://www.youtube.com/channel/UC-yuWVUplUJZvieEligKBkA) create a simple and fast graphics engine.

### Main Features to Come ###
- Fast 2D and 3D rendering
	- 2D (UI, particles, sprites, etc)
- Support other platforms such as Mac OS, Linux, Android, iOS (hopefully down the line PS, Xbox, and the web browser)
	- using their native graphics API such as Metal, Vulkan, DirectX
- Scripting Language (maybe Lua, JavaScript, My Own?)
- Fully featured application editor
- Terain and World Gen
- AI
- Audio Systems

## Dependencies ##
- [premake](https://premake.github.io)
- [spdlog](https://github.com/gabime/spdlog): Logging library
- glm [web](https://glm.g-truc.net/0.9.9/index.html) [code](https://github.com/g-truc/glm): Fast math library
- GLFW [web](https://www.glfw.org) [code](https://github.com/glfw/glfw): For getting OpenGL 1.0 functions
- Glad [web](https://glad.dav1d.de) [code](https://github.com/Dav1dde/glad): For getting later OpenGL functions
- [Dear ImGui](https://github.com/ocornut/imgui): Immediate mode GUI for C++
- [stb_image](https://gitbub.com/nothings/stb): Image Loader

## Changelog ##
The latest changes:

- Full Screen

Complete list of changes here -> [Changelog](docs/Changelog.md)
