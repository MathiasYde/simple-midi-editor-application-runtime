NEWT_DIR = "%{wks.location}/Newt"
include "Newt/Dependencies.lua"

workspace "SMEAR"
	architecture "x86_64"
	startproject "SMEAR"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Newt/NewtExternal.lua"
include "SMEAR"
