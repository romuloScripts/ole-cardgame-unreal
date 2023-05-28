using UnrealBuildTool;

public class MatchUI : ModuleRules
{
    public MatchUI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnforceIWYU = true;
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bUseUnity = true;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
        );
        
        //PublicDefinitions.Add("GAMEPLAYTAGGED_API=");

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate", "InputCore",
                "SlateCore","Data","GameplayTags","CardSystem","UMG","BoardSystem","Match","UI"
            }
        );
    }
}