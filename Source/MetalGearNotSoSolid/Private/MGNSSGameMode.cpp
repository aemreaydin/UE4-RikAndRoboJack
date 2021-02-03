// Fill out your copyright notice in the Description page of Project Settings.


#include "MGNSSGameMode.h"

#include "MGNSSGameState.h"
#include "RikHUD.h"
#include "Kismet/GameplayStatics.h"


AMGNSSGameMode::AMGNSSGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_RikCharacter"));
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHudClassFinder(TEXT("/Game/Blueprints/BP_Rik_HUD"));
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(
		TEXT("/Game/Blueprints/BP_RikController"));

	DefaultPawnClass = PlayerPawnClassFinder.Class;
	HUDClass = PlayerHudClassFinder.Class;
	GameStateClass = AMGNSSGameState::StaticClass();
	PlayerControllerClass = PlayerControllerClassFinder.Class;
}

void AMGNSSGameMode::CompleteMission(const bool bIsSuccess) const
{
	if (SpectateViewClass)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectateViewClass, Actors);
		if (Actors.Num() > 0)
		{
			for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
			{
				const auto PC = Iter->Get();
				if (PC)
				{
					const auto SpectateCamera = Actors[0];
					PC->SetViewTargetWithBlend(SpectateCamera, 0.5f, VTBlend_Cubic);
				}
			}
		}
	}

	const auto GS = Cast<AMGNSSGameState>(GetWorld()->GetGameState());
	if (GS)
	{
		GS->MulticastOnMissionComplete(bIsSuccess);
	}
}
