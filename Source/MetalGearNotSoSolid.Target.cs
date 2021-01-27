// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MetalGearNotSoSolidTarget : TargetRules
{
	public MetalGearNotSoSolidTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange(new[] {"MetalGearNotSoSolid"});
	}
}