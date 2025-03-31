// Alexander (AgitoReiKen) Moskalenko (C) 2022

using System.IO;
using UnrealBuildTool;

public class Restyle : ModuleRules
{
	public Restyle(ReadOnlyTargetRules Target) : base(Target)
	{
		PublicDependencyModuleNames.AddRange(new[] { "Core" });
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		var EngineDir = Path.GetFullPath(Target.RelativeEnginePath);
		PrivateIncludePaths.AddRange(
			new[]
			{
				"Restyle/Private",
				"Restyle/Classes",
				Path.Combine(EngineDir, @"Source/Editor/GraphEditor/Private"),
				Path.Combine(EngineDir, @"Source/Editor/UMGEditor/Private")
			}
		);
		PrivateDependencyModuleNames.AddRange(
			new[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"RenderCore",
				"Projects",
				"EngineSettings",
				"Kismet",
				"UnrealEd",
				"BlueprintGraph",
				"KismetWidgets",
				"EditorWidgets",
				"GraphEditor",
				"UMG",
				"InputCore",
				"AppFramework",
				"EditorWidgets",
				"ToolWidgets",
				"RHI",
				"UMGEditor",
				"MaterialEditor",
				"AnimGraph",
				"KismetCompiler",
				"RestyleShaders",
				"AnimationBlueprintEditor"
				// ... add private dependencies that you statically link with here ...	
			}
		);
		if (Target.Platform == UnrealTargetPlatform.Win64)
			PublicAdditionalLibraries.Add($"{PluginDirectory}/Binaries/ThirdParty/MinHook/Win64/minhook.x64.lib");
	}
}