// Fill out your copyright notice in the Description page of Project Settings.


#include "MGNSSGameMode.h"
#include "RikHUD.h"


AMGNSSGameMode::AMGNSSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_RikCharacter"));
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHudClassFinder(TEXT("/Game/Blueprints/BP_Rik_HUD"));

	DefaultPawnClass = PlayerPawnClassFinder.Class;
	HUDClass = PlayerHudClassFinder.Class;
}

void AMGNSSGameMode::CompleteMission(APawn* PlayerPawn)
{
	if(PlayerPawn)
	{
		PlayerPawn->DisableInput(nullptr);
	}

	OnMissionComplete(PlayerPawn);
}
