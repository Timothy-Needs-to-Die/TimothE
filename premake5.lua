workspace "TimothE" 
	architecture "x64"

	configurations {
		"Debug",
		"Release",
	}

project "TimothE"
	location "TimothE"
	kind "ConsoleApp"
	language "C++"


	files {
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp"
	}

	includedirs {
		"Dependancies/GLFW/include",
		"Dependancies/GLEW/include",
		"Dependancies/glm",
		"Dependancies/irrklang/include",
		"Dependancies/",
		"Dependancies/freetype",
		"Dependancies",
		"Dependancies/imgui",
		"Dependancies/imgui/backend",
		"Dependancies/Fmod/inc"
	}

	libdirs {
		"Dependancies/GLFW/lib-vc2019",
		"Dependancies/GLEW/lib",
		"Dependancies/freetype",
		"Dependancies/irrklang/lib", 
		"Dependancies/Fmod/lib"
	}

	links {
		"opengl32.lib",
		"glfw3.lib",
		"glew32s.lib",
		"glew32.lib",
		"soil2-debug.lib",
		"soil2-debug.dll",
		"freetype.lib",
		"fmod_vc.lib"
	}

	vpaths {
		["Headers"] = "**.h",
		["Source"] = "**.cpp",
	}