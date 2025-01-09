// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KRPG : ModuleRules
{
	public KRPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags", "UMG", "Niagara","NavigationSystem", "AIModule" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PrivateIncludePaths.AddRange(new string[] {
			"KRPG/",
            "KRPG/Actor/",
            "KRPG/Actor/Player/",
            "KRPG/Actor/Monster/",
            "KRPG/ControllerEx/",
            "KRPG/ControllerEx/Player/",
            "KRPG/ControllerEx/Monster/",
            "KRPG/GameMode/",
            "KRPG/Stat/",
			"KRPG/Animation/",
			"KRPG/Define/",
			"KRPG/State/",
            "KRPG/State/Player/",
            "KRPG/State/Monster/",
			"KRPG/State/Skill/",
            "KRPG/StateMachine/",
            "KRPG/Notify/",
            "KRPG/NotifyState/",
			"KRPG/Weapon/",
			"KRPG/GameInstance/",
			"KRPG/Data/",
			"KRPG/UI/",
			"KRPG/UI/Widget/",
            "KRPG/UI/Hud/",
            "KRPG/Interface/",
			"KRPG/Input/",
            "KRPG/Inventory/",
			"KRPG/Item/",
            "KRPG/Util/",
            "KRPG/Equipment/"
        });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
