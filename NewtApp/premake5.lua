project "NewtApp"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"%{wks.location}/Newt/Newt/vendor/spdlog/include",
		"%{wks.location}/Newt/Newt/src",
		"%{wks.location}/Newt/Newt/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"Newt"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "NT_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NT_RELEASE"
		runtime "Release"
		optimize "On"
		symbols "On"

	filter "configurations:Dist"
		kind "WindowedApp"
		defines "NT_DIST"
		runtime "Release"
		optimize "On"
		symbols "Off"