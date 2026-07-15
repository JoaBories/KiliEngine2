workspace "KiliEngine2"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Build"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Names
local mathlib = "KiliMathematics"
local engine = "KiliEngine"
local runtime = "Runtime"

-- =========== Math lib
project (mathlib)
    location "%{prj.name}"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        (mathlib .. "/src")
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"

        defines "KL_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        defines "KL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "KL_REL"
        optimize "On"

    filter "configurations:Build"
        defines "KL_BUILD"
        optimize "On"

-- =========== Engine    
project (engine)
    location "%{prj.name}"
    kind "StaticLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        (mathlib .. "/src"),
        (engine .. "/src")
    }

    links
    {
        (mathlib)
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"

        defines "KL_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        defines "KL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "KL_REL"
        optimize "On"

    filter "configurations:Build"
        defines "KL_BUILD"
        optimize "On"
        
-- =========== Runtime
project (runtime)
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        (mathlib .. "/src"),
        (engine .. "/src")
    }

    links
    {
        (mathlib),
        (engine)
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"

        defines "KL_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        defines "KL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "KL_REL"
        optimize "On"

    filter "configurations:Build"
        defines "KL_BUILD"
        optimize "On"