using UnrealBuildTool;

public class CardSystem : ModuleRules
{
    public CardSystem(ReadOnlyTargetRules Target) : base(Target)
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
                "SlateCore","Data","GameplayTags","UMG"
            }
        );
    }
}