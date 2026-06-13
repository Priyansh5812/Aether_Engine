workspace "Aether"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Aether"
	location "Aether"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	-- Don't compile third-party library sources (examples, benches, tests).
	-- Only use the headers from ThirdParty/spdlog/include.
	removefiles
	{
		"%{prj.name}/src/ThirdParty/**.cpp",
		"%{prj.name}/src/ThirdParty/**.c",
		"%{prj.name}/src/ThirdParty/**.cc",
		"%{prj.name}/src/ThirdParty/**_example*.h",
		"%{prj.name}/src/ThirdParty/**/bench*.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/src/ThirdParty/spdlog/include"
	}
	

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"AE_WINDOWS",
			"AE_BUILD_DLL",
			"SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE",
			"SPDLOG_HEADER_ONLY" -- use header-only spdlog to avoid compiled lib requirements
		}
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "AE_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "AE_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "AE_DIST"
		optimize "On"

	filter {"system:windows"}
		buildoptions "/utf-8"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{	
		"Aether/src",
		"Aether/src/ThirdParty/spdlog/include"
	}

	links
	{
		"Aether"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"AE_WINDOWS",
			"SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_TRACE",
			"SPDLOG_HEADER_ONLY"
		}
	
	filter "configurations:Debug"
		defines "AE_DEBUG"
		symbols "On"
	filter "configurations:Release"
		defines "AE_RELEASE"
		optimize "On"
	filter "configurations:Dist"
		defines "AE_DIST"
		optimize "On"

	filter {"system:windows"}
		buildoptions "/utf-8"