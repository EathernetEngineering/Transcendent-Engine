workspace "Slue"
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
IncludeDir["GLFW"] = "Slue/vendor/GLFW/include"
IncludeDir["GLEW"] = "Slue/vendor/GLEW/include"

group "Dependencies"
	include "Slue/vendor/GLFW"
	include "Slue/vendor/GLEW"

group ""

project "Slue"
	location "Slue"
	kind "StaticLib"
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

	defines
	{
		"_TEMP_DEFINE"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLEW}"
	}

	links
	{
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SL_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "SL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distrib"
		defines "SL_DISTRIB"
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
		"Slue/src",
		"Slue/vendor"
	}

	links
	{
		"Slue"
	}

	filter "system:windows"
		systemversion "latest"
		
	filter "configurations:Debug"
		defines "SL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SL_DISTRIB"
		runtime "Release"
		optimize "on"
