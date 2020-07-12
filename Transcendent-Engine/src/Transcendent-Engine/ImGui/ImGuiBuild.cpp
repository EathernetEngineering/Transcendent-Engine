#include "tepch.h"

#ifdef TE_PLATFORM_WINDOWS
#include <examples/imgui_impl_win32.cpp>
#include <examples/imgui_impl_dx12.cpp>
#else
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <examples/imgui_impl_opengl3.cpp>
#include <examples/imgui_impl_glfw.cpp>
#endif
