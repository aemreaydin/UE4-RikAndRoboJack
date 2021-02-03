// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MGNSSGameState.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARNOTSOSOLID_API AMGNSSGameState : public AGameState
{
	GENERATED_BODY()

public:
	UFUNCTION(NetMulticast, Reliable)
	void MulticastOnMissionComplete(bool bIsSuccess);

	UFUNCTION(NetMulticast, Reliable)
    void MulticastOnMissingObjective();

	UFUNCTION(BlueprintCallable)
	bool IsObjectPickedUpByAPlayer();
};
