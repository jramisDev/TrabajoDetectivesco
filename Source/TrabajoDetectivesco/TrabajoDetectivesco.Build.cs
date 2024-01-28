// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TrabajoDetectivesco : ModuleRules
{
	public TrabajoDetectivesco(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
		
		PublicIncludePaths.AddRange(new string[]
		{
			"TrabajoDetectivesco/Public"
		});
	}
}
