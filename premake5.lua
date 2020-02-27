workspace "Transcendent-Engine"
	architecture "x86_64"
	startproject "Sandbox"

	configurations 
	{
		"Debug",
		"Release",
		"Distrib"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Transcendent-Engine/vendor/glfw/include"
IncludeDir["GLAD"] = "Transcendent-Engine/vendor/glad/include"
IncludeDir["ImGui"] = "Transcendent-Engine/vendor/imgui"
IncludeDir["glm"] = "Transcendent-Engine/vendor/glm"
IncludeDir["stb"] = "Transcendent-Engine/vendor/stb"

group "Dependencies"
	include "Transcendent-Engine/vendor/glfw"
	include "Transcendent-Engine/vendor/glad"
	include "Transcendent-Engine/vendor/imgui"

group ""

project "Transcendent-Engine"
	location "Transcendent-Engine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tepch.h"
	pchsource "Transcendent-Engine/src/tepch.cpp"

	files
	{
		"%{prj.name}/include/Transcendent-Engine.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src/Transcendent-Engine",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"TE_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "TE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distrib"
		defines "TE_DISTRIB"
		runtime "Release"
		optimize "on"

		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Transcendent-Engine/vendor/spdlog/include",
		"Transcendent-Engine/include",
		"Transcendent-Engine/src",
		"Transcendent-Engine/vendor",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Transcendent-Engine"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "TE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "TE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "TE_DISTRIB"
		runtime "Release"
		optimize "on"
