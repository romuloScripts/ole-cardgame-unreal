// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class OleEditorTarget : TargetRules
{
	public OleEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		//ExtraModuleNames.AddRange( new string[] { "Ole" } );
		RegisterModulesCreatedByRider();
	}

	private void RegisterModulesCreatedByRider(){
		ExtraModuleNames.AddRange(new string[]{ "Data","UI","CardSystem","BoardSystem", "Match","Ole", "MatchUI"});
	}
}
