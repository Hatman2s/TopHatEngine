workspace "TopHatEngine"
architecture "x64"
startproject "Game"
configurations
{
    "Debug",
    "RT",
    "Release"
}

outputdir = "%{cfg.builder}-%{cfg.system}-%{cfg.architecture}"


project "TopHatEngine"
location "TopHatEngine"
kind "Staticlib"
language "C++"
targetdir ("bin/" .. outputdir .. "/%{prj.name}/%{cfg.buildcfg}")
objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
pchheader "THPrecomp.h"
pchsource "TopHatEngine/src/THPrecomp.cpp"

IncludeDir = {}
IncludeDir["GLFW"] = "TopHatEngine/externlibs/glfw/include"
IncludeDir["glad"] = "TopHatEngine/externlibs/glad/include"
IncludeDir["glm"] = "TopHatEngine/externlibs/glm/glm"
IncludeDir["STBI"] = "TopHatEngine/externlibs/STBI"

files
{
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp",
    "%{prj.name}/externlibs/glm/glm/**.hpp",
    "%{prj.name}/externlibs/glm/glm/**.inl",
    "%{prj.name}/externlibs/STBI/**.h",
	"%{prj.name}/externlibs/STBI/**.cpp",
}
includedirs
{
    "%{prj.name}/externlibs/spdlog/include;",
    "%{prj.name}/src;",
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.glad}",
    "%{IncludeDir.glm}",
    "%{IncludeDir.STBI}"
}
links
{
    "GLFW",
    "glad",
    "opengl32.lib"
}

filter "system:windows"
cppdialect "C++17"
staticruntime "on"
systemversion "latest"

defines
{
    --"TH_PLATFORM_WINDOWS",
    "TH_PLATFORM_MULTI",
    "GLFW_INCLUDE_NONE"
}

postbuildcommands
{
    ("{COPY} %{cfg.buildtarget.relpath} \"../Game/src/\"")
}

    filter "configurations:Debug"
        defines "TH_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:RT"
        defines "TH_RT"
        runtime "Release"
        optimize "On"

    filter "configurations:Release"
        defines "TH_RELEASE"
        runtime "Release"
        optimize "On"

include "TopHatEngine/externlibs/glfw"
include "TopHatEngine/externlibs/glad"
    project "Game"
        location "Game"
        kind "ConsoleApp"
        language "C++"
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
            "TopHatEngine/externlibs/spdlog/include",
            "TopHatEngine/src",
            "%{IncludeDir.glm}",
            "%{IncludeDir.GLFW}"
        }
        links
        {
            "TopHatEngine",
            "GLFW",
            "opengl32.lib"
        }
    
        filter "system:windows"
            cppdialect "C++17"
            systemversion "latest"
    
            defines
            {
                --"TH_PLATFORM_WINDOWS"
                "TH_PLATFORM_MULTI"
            }
    
        filter "configurations:Debug"
            defines "TH_DEBUG"
          
            runtime "Debug"
            symbols "On"
    
        filter "configurations:Release"
            defines "TH_RELEASE"
          
            runtime "Release"
            optimize "On"
    
        filter "configurations:Dist"
            defines "TH_DIST"
            
            runtime "Release"
            optimize "On"