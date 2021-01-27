// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MetalGearNotSoSolidEditorTarget : TargetRules
{
	public MetalGearNotSoSolidEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] {"MetalGearNotSoSolid"});
	}
}