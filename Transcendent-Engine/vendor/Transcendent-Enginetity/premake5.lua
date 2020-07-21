workspace "Transcendent-Entity"
	architecture "x86_64"
	startproject "Transcendent-Entity"

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

group ""

project "Transcendent-Entity"
	location "Transcendent-Entity"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "tepch.h"
	pchsource "Transcendent-Entity/src/tepch.cpp"

	files
	{
		"%{prj.name}/include/Transcendent-Entity.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines
	{
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src/Transcendent-Entity"
	}

	links
	{
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
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
