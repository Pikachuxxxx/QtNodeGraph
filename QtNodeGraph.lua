include "scripts/qt/qt.lua"

local qt = premake.extensions.qt

project "QtNodeGraph"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"
        -- Debugging directory = where the main premake5.lua is located
    debugdir "%{wks.location}../"

    -- be carefull, this function enables Qt only for the current configuration.
    -- So if you want to enable it on all configuration, be sure that no filter
    -- is active when calling this (or reset the filter using `filter {}`
    qt.enable()

   -- TODO: use environment variables to set this
   -- Setup the Qt path. This apply to the current configuration, so
   -- if you handle x32 and x64, you can specify a different path
   -- for both configurations.
   --
   -- Note that if this is ommited, the addon will try to look for the
   -- QTDIR environment variable. If it's not found, then the script
   -- will return an error since it won't be able to find the path
   -- to your Qt installation.
   --
   qtpath "C:/Qt/Qt_msvc_dir/msvc2017_64"

   --
   -- Setup which Qt modules will be used. This also apply to the
   -- current configuration, so can you choose to deactivate a module
   -- for a specific configuration.
   --
   qtmodules { "core", "gui", "widgets", "opengl" }

   --
   -- Setup the prefix of the Qt libraries. Usually it's Qt4 for Qt 4.x
   -- versions and Qt5 for Qt 5.x ones. Again, this apply to the current
   -- configuration. So if you want to have a configuration which uses
   -- Qt4 and one that uses Qt5, you can do it.
   --
   qtprefix "Qt5"

   qtbinpath "C:/Qt/Qt_msvc_dir/msvc2017_64/bin"

   qtgenerateddir "%{prj.location}/../src/generated"

    files
    {
        "src/**.h",
        "src/**.hpp",
        "src/**.c",
        "src/**.cpp",
    }

    includedirs
    {
        "./",
        "./src/"
    }

    filter "system:windows"
        systemversion "latest"
        characterset ("MBCS")
        editandcontinue "Off"

    filter "configurations:Debug"
        defines { "_DEBUG" }
        qtsuffix "d"
        symbols "On"
        runtime "Debug"
        optimize "Off"

    filter "configurations:Release"
        defines { "NDEBUG" }
        symbols "On"
        optimize "Full"
        runtime "Release"
