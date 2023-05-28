// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class OleTarget : TargetRules
{
	public OleTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		//ExtraModuleNames.AddRange( new string[] { "Ole" } );
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider(){
		ExtraModuleNames.AddRange(new string[]{ "Data","UI","CardSystem","BoardSystem", "Match","Ole", "MatchUI"});
	}
}
