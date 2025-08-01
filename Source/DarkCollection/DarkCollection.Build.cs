// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DarkCollection : ModuleRules
{
	public DarkCollection(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;


        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "MounteaDialogueSystem" });

        PrivateIncludePaths.AddRange(new string[] { Name });
        PublicIncludePaths.AddRange(new string[] { Name });


    }
}
