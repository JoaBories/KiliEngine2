-- Premake file for KiliEngine2

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Names
local mathLib = "KiliMathematics"
local glad = "Glad"
local engine = "KiliEngine"
local runtime = "Runtime"

workspace "KiliEngine2"
    architecture "x64"

    configurations {
        "Debug",
        "Release",
        "Build"
    }

    debugdir "%{wks.location}"

-- =========== Math lib
project (mathLib)
    location "projects/%{prj.name}"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "projects/%{prj.name}/src/**.h",
        "projects/%{prj.name}/src/**.cpp"
    }

    includedirs {
        ("projects/" .. mathLib .. "/src")
    }

    cppdialect "c++17"
    staticruntime "On"
    systemversion "latest"

    filter "configurations:Debug"
        defines "KL_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "KL_REL"
        optimize "On"
        symbols "On"

    filter "configurations:Build"
        defines "KL_BUILD"
        optimize "On"

-- =========== Glad
project (glad)
    location "vendor/%{prj.name}"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "vendor/%{prj.name}/include/**.h",
        "vendor/%{prj.name}/src/**.c"
    }

    includedirs {
        ("vendor/" .. glad .. "/include")
    }

    cppdialect "c++17"
    staticruntime "On"
    systemversion "latest"
    
    filter "configurations:Debug"
        defines "KL_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "KL_REL"
        optimize "On"
        symbols "On"
    
    filter "configurations:Build"
        defines "KL_BUILD"
        optimize "On"


-- =========== Engine    
project (engine)
    location "projects/%{prj.name}"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "klpch.h"
    pchsource "projects/%{prj.name}/src/klpch.cpp"

    files {
        "projects/%{prj.name}/src/**.h",
        "projects/%{prj.name}/src/**.cpp",
        "premake5.lua",
        "README.md",
        "config/**",
        "resources/**"
    }

    includedirs {
        ("projects/" .. mathLib .. "/src"),
        ("projects/" .. engine .. "/src"),
        ("vendor/" .. glad .. "/include"),
        "vendor/Sdl3/include"
    }

    libdirs {
        "vendor/Sdl3"
    }

    links {
        (mathLib),
        (glad),
        "SDL3"
    }

    cppdialect "c++17"
    staticruntime "On"
    systemversion "latest"

    filter "configurations:Debug"
        defines "KL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "KL_REL"
        optimize "On"
        symbols "On"

    filter "configurations:Build"
        defines "KL_BUILD"
        optimize "On"
        
-- =========== Runtime
project (runtime)
    location "projects/%{prj.name}"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "projects/%{prj.name}/src/**.h",
        "projects/%{prj.name}/src/**.cpp"
    }

    includedirs {
        ("projects/" .. mathLib .. "/src"),
        ("projects/" .. engine .. "/src"),
        ("vendor/" .. glad .. "/include"),
        "vendor/Sdl3/include"
    }

    libdirs {
        "vendor/Sdl3"
    }

    links {
        (mathLib),
        (engine),
        (glad),
        "Sdl3"
    }

    -- Used for copying SDL3 dll onto the exe folder 
    postbuildcommands { 
        "{COPYFILE} %[vendor/Sdl3/SDL3.dll] %[%{!cfg.targetdir}]",
        "{COPYDIR} %[resources] %[%{!cfg.targetdir}/resources]",
        "{COPYDIR} %[config] %[%{!cfg.targetdir}/config]"
    }

    cppdialect "c++17"
    staticruntime "On"
    systemversion "latest"

    filter "configurations:Debug"
        defines "KL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "KL_REL"
        optimize "On"
        symbols "On"

    filter "configurations:Build"
        defines "KL_BUILD"
        optimize "On"