// Fill out your copyright notice in the Description page of Project Settings.


#include "MGNSSGameMode.h"
#include "RikHUD.h"
#include "Kismet/GameplayStatics.h"


AMGNSSGameMode::AMGNSSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_RikCharacter"));
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHudClassFinder(TEXT("/Game/Blueprints/BP_Rik_HUD"));

	DefaultPawnClass = PlayerPawnClassFinder.Class;
	HUDClass = PlayerHudClassFinder.Class;
}

void AMGNSSGameMode::CompleteMission(APawn* PlayerPawn, const bool bIsSuccess)
{
	if (!PlayerPawn) return;
	
	PlayerPawn->DisableInput(nullptr);

	if (SpectateViewClass)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectateViewClass, Actors);
		if (Actors.Num() > 0)
		{
			const auto Controller = PlayerPawn->GetController();
			const auto PC = Cast<APlayerController>(Controller);
			if (PC)
			{
				const auto SpectateCamera = Actors[0];
				PC->SetViewTargetWithBlend(SpectateCamera, 0.5f, VTBlend_Cubic);
			}
		}
	}

	OnMissionComplete(PlayerPawn, bIsSuccess);
}
