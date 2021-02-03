// Fill out your copyright notice in the Description page of Project Settings.


#include "MGNSSGameState.h"
#include "EngineUtils.h"
#include "RikCharacter.h"
#include "RikController.h"

void AMGNSSGameState::MulticastOnMissionComplete_Implementation(bool bIsSuccess)
{
	for(auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		const auto PC = Cast<ARikController>(Iter->Get());
		if(PC && PC->IsLocalController())
		{
			const auto Pawn = PC->GetPawn();
			Pawn->DisableInput(PC);
			PC->OnMissionComplete(Pawn, bIsSuccess);
		}
	}
}

void AMGNSSGameState::MulticastOnMissingObjective_Implementation()
{
	for(auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
	{
		const auto PC = Cast<ARikController>(Iter->Get());
		if(PC && PC->IsLocalController())
		{
			PC->OnMissingObjective();
		}
	}
}

bool AMGNSSGameState::IsObjectPickedUpByAPlayer()
{
	for(auto Iter = TActorIterator<AActor>(GetWorld()); Iter; ++Iter)
	{
		const auto Rik = Cast<ARikCharacter>(*Iter);
		if(Rik && Rik->bIsObjectPickedUp)
		{
			return true;
		}
	}
	return false;
}
