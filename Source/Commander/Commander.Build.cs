// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Commander : ModuleRules
{
	public Commander(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(new string[] { "Commander" });

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

    }
}
