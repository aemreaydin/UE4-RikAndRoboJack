// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameMode.h"
#include "MGNSSGameMode.generated.h"

/**
 * 
 */
UCLASS()
class METALGEARNOTSOSOLID_API AMGNSSGameMode final : public AGameMode
{
	GENERATED_BODY()

public:
	AMGNSSGameMode();

	void CompleteMission(bool bIsSuccess) const;

	bool bIsMissionComplete = false;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Spectate")
	TSubclassOf<AActor> SpectateViewClass;
};
