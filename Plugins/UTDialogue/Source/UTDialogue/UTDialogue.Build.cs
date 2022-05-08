using UnrealBuildTool;

public class UTDialogue : ModuleRules
{
	public UTDialogue(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });
		PublicDependencyModuleNames.AddRange(new string[]
			{"Core", "UMG", "Slate", "SlateCore", "UTLogger", "UTInputIndicator"});
		PrivateDependencyModuleNames.AddRange(new string[]
			{"CoreUObject", "Engine", "UMG", "Slate", "SlateCore", "UTLogger", "UTInputIndicator"});
		DynamicallyLoadedModuleNames.AddRange(new string[] { });
	}
}
