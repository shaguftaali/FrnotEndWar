// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FrontEndWar : ModuleRules
{
    public FrontEndWar(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "OnlineSubsystem", "OnlineSubsystemUtils" });
        DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
    }

    //public FrontEndWar(TargetInfo Target) : base(Target)
    //{
    //    PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

    //    PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "OnlineSubsystem", "OnlineSubsystemUtils" });
    //    DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
    //}
}
