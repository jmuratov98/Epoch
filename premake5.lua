workspace "Epoch"
	architecture "x64"
	startproject "Sandbox"

	configurations { "Debug", "Release", "Distribution" }

	flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}"

IncludeDirs = {}
IncludeDirs["spdlog"]	= "Epoch/lib/spdlog/include"
IncludeDirs["glm"]		= "Epoch/lib/glm"
IncludeDirs["GLFW"]		= "Epoch/lib/GLFW/include"
IncludeDirs["Glad"]		= "Epoch/lib/Glad/include"
IncludeDirs["ImGui"]	= "Epoch/lib/imgui"
IncludeDirs["stb"]		= "Epoch/lib/stb/include"

group "Libraries"
	include "Epoch/lib/GLFW"
	include "Epoch/lib/Glad"
	include "Epoch/lib/imgui"

group ""

project "Epoch"
	location "Epoch"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir	("bin/" .. outputdir .. "/%{prj.name}")
	objdir		("bin-obj/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Epoch/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/include/**.h",
		"%{prj.name}/lib/glm/glm/**.hpp",
		"%{prj.name}/lib/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"%{prj.name}/include",

		"%{IncludeDirs.spdlog}",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.GLFW}",
		"%{IncludeDirs.Glad}",
		"%{IncludeDirs.ImGui}",
		"%{IncludeDirs.stb}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EGE_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "EGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "EGE_DISTRIBUTION"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir	("bin/" .. outputdir .. "/%{prj.name}")
	objdir		("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/include/**.h",
	}

	includedirs
	{
		"%{prj.name}/include",

		"Epoch/include",
	
		"%{IncludeDirs.spdlog}",
		"%{IncludeDirs.glm}",
		"%{IncludeDirs.ImGui}"
	}

	links
	{
		"Epoch"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "EGE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EGE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Distribution"
		defines "EGE_DISTRIBUTION"
		runtime "Release"
		optimize "on"
