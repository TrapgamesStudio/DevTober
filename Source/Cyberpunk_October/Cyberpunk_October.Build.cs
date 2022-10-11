// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Cyberpunk_October : ModuleRules
{
	public Cyberpunk_October(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
