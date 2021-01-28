// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MGNSSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARNOTSOSOLID_API AMGNSSGameMode final : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMGNSSGameMode();

	void CompleteMission(APawn* PlayerPawn);

	UFUNCTION(BlueprintImplementableEvent, Category="GameMode")
	void OnMissionComplete(APawn* PlayerPawn);

	UFUNCTION(BlueprintImplementableEvent, Category="GameMode")
	void OnMissingObjective(APawn* PlayerPawn);
};
