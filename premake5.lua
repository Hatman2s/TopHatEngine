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

files
{
    "%{prj.name}/src/TopHat**.h",
    "%{prj.name}/src/TopHat/**.cpp"

}
includedirs
{
    "%{prj.name}/src/externlibs/spdlog/include;"
}

filter "system:windows"
cppdialect "C++17"
staticruntime "On"
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
    symbols "On"

filter "configurations:RT"
    defines "TH_RT"
    optimize "On"

filter "configurations:Release"
    defines "TH_RELEASE"
    optimize "On"
