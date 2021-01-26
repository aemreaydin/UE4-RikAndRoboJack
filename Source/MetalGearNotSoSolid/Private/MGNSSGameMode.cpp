// Fill out your copyright notice in the Description page of Project Settings.


#include "MGNSSGameMode.h"
#include "RikHUD.h"


AMGNSSGameMode::AMGNSSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_RikCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	HUDClass = ARikHUD::StaticClass();
}
