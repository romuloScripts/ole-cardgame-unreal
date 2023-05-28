using UnrealBuildTool;

public class Data : ModuleRules
{
    public Data(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnforceIWYU = true;
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bUseUnity = true;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core","GameplayTags"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "GameplayTags"
            }
        );
    }
}