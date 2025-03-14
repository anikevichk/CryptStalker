// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CryptStalker : ModuleRules
{
	public CryptStalker(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
