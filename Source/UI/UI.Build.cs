using UnrealBuildTool;

public class UI : ModuleRules
{
    public UI(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnforceIWYU = true;
        MinFilesUsingPrecompiledHeaderOverride = 1;
        bUseUnity = true;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate","UMG",
                "SlateCore","InputCore","GameplayTags",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Data"
            }
        );
    }
}