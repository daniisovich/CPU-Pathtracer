workspace "Pathtracer"
	architecture "x64"
	startproject "Pathtracer"

	configurations {
		"Debug",
		"Release",
	}


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Pathtracer"
	location "Pathtracer"
	
	kind "ConsoleApp"

	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir)

	pchheader "precompiled/pch.h"
	pchsource "Pathtracer/src/precompiled/pch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs {
		"%{prj.name}/src",
	}


	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
