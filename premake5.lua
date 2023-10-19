workspace "TopHatEngine"
architecture "x64"
configurations
{
    "Debug",
    "RT",
    "Release"
}

outputdir = "%{cfg.builder}-%{cfg.system}-%{cfg.architecture}"

project "TopHatEngine"
location "TopHatEngine"
kind "Sharedlib"
language "C++"
targetdir ("bin/" .. outputdir .. "/%{prj.name}")
objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
pchheader "THPrecomp.h"
pchsource "TopHatEngine/src/THPrecomp.cpp"


files
{
    "%{prj.name}/src/**.h",
    "%{prj.name}/src/**.cpp"

}
includedirs
{
    "%{prj.name}/externlibs/spdlog/include;",
    "%{prj.name}/src;"
}

filter "system:windows"
cppdialect "C++17"
staticruntime "off"
systemversion "latest"

defines
{
    "TH_PLATFORM_WINDOWS",
    "TH_BUILD_DLL"
}

postbuildcommands
{
    ("{COPY} %{cfg.buildtarget.relpath} ../bin/Debug/Scp-GF")
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
