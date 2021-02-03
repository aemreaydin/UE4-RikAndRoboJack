// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RikController.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARNOTSOSOLID_API ARikController : public APlayerController
{
	GENERATED_BODY()

	ARikController();
protected:
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category="GameHUD")
	void OnMissionComplete(APawn* PlayerPawn, bool bIsSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category="GameHUD")
	void OnMissingObjective();
};
