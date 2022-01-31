// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class UI_Lessons : ModuleRules
{
	public UI_Lessons(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
		 "Core",
		 "CoreUObject",
		 "Engine",
		 "InputCore",
		 "Slate",
		 "SlateCore", 
		 "UMG", 
		 "MediaAssets", 
		 "DesktopPlatform"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {"QuestSystem", "InventorySystem", "SaveSystem"});
		PublicIncludePaths.AddRange(new string[] {"UI_Lessons/SaveSystem"});
		

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
