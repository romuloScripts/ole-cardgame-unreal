// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SessionSubsystemPlugin : ModuleRules
{
	public SessionSubsystemPlugin(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(new string[] {
				// ... add other private include paths required here ...
			}
			);

		PublicDependencyModuleNames.AddRange(new string[]{ "Core","OnlineSubsystem", "OnlineSubsystemUtils"});
		PrivateDependencyModuleNames.AddRange(new string[]{ "CoreUObject", "Engine", "Slate", "SlateCore"});
		DynamicallyLoadedModuleNames.AddRange(new string[]{"OnlineSubsystemSteam"});
	}
}
