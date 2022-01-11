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
		"Dependancies/nlohmann",
		"Dependancies/freetype",
		"Dependancies/imgui",
		"Dependancies/imgui/backend"
	}

	libdirs {
		"Dependancies/GLFW/lib-vc2019",
		"Dependancies/GLEW/lib",
		"Dependancies/irrklang/lib"
	}

	links {
		"opengl32.lib",
		"glfw3.lib",
		"glew32s.lib"
	}