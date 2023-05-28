// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Ole : ModuleRules
{
	public Ole(ReadOnlyTargetRules Target) : base(Target)
	{
		bEnforceIWYU = true;
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		//PrivatePCHHeaderFile = "MaulProtoPrecompiled.h";
		MinFilesUsingPrecompiledHeaderOverride = 1;
		bUseUnity = true;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", "OnlineSubsystem","Engine", "InputCore", "SlateCore","GameplayTags", "SessionSubsystemPlugin",
			"Data", "MoviePlayer","UI","BoardSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[]{"CoreUObject"});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		//PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
