workspace "BlockopolisNBTEditorProject"
    configurations { "Debug", "Release" }
    platforms { "Linux-x64", "Windows-x64" }

    filter "platforms:Linux-x64"
        system "linux"
        architecture "x86_64"

    filter "platforms:Windows-x64"
        system "windows"
        architecture "x86_64"

project "BlockopolisNBTEditor"
    kind "WindowedApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    files {
        "src/**.cpp", 
        "src/**.h", 
        "src/**.hpp", 
        "src/**.c", 
        "/usr/share/include/**.cpp", 
        "/usr/share/include/**.h", 
        "/usr/share/include/**.hpp" 
    }

    filter {"platforms:Linux-x64", "configurations:Debug"}
        cppdialect "C++17"
        optimize "Full"

        defines { 
            "LINUX"
        }

        includedirs { 
            "include",
            "src"
        }

        libdirs {}

        links {}

        buildoptions { 
            "`wx-config --cxxflags`"
        }

        linkoptions  { 
            '`wx-config --libs`' 
        } 

    filter {"platforms:Linux-x64", "configurations:Release"}
        cppdialect "C++17"
        optimize "Full"

        defines { 
            "LINUX"
        }

        includedirs { 
            "include",
            "src"
        }

        libdirs {}

        links {}

        buildoptions { 
            "`wx-config --cxxflags`"
        }

        linkoptions  { 
            '`wx-config --libs`' 
        }

    filter {"platforms:Windows-x64", "configurations:Debug"}
        cppdialect "C++17"
        optimize "Full"

        defines { 
            "WINDOWS"
        }

        includedirs { 
            "include",
            "src"
        }

        libdirs {}

        links {}

        buildoptions { 
            "/utf-8" 
        }
        
        linkoptions { 
            "/utf-8", 
            "/STACK:8388608" 
        }

    filter {"platforms:Windows-x64", "configurations:Release"}
        cppdialect "C++17"
        optimize "Full"

        defines { 
            "WINDOWS"
        }

        includedirs { 
            "include",
            "src"
        }

        libdirs {}

        links {}

        buildoptions { 
            "/utf-8" 
        }
        
        linkoptions { 
            "/utf-8", 
            "/STACK:8388608" 
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        symbols "Full"

    prebuildcommands {
        "{ECHO} Prebuilding Common"
    }
