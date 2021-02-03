// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtractionZone.h"


#include "MGNSSGameMode.h"
#include "MGNSSGameState.h"
#include "RikCharacter.h"
#include "RikController.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"

// Sets default values
AExtractionZone::AExtractionZone()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	BoxComponent->SetBoxExtent(FVector(200.0f));
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AExtractionZone::OnExtractionOverlap);

	RootComponent = BoxComponent;

	DecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Comp"));
	DecalComponent->DecalSize = FVector(200.0f);
	DecalComponent->SetupAttachment(BoxComponent);
}

void AExtractionZone::OnExtractionOverlap(
	UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	const auto GameMode = Cast<AMGNSSGameMode>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		const auto GS = GameMode->GetGameState<AMGNSSGameState>();
		if(GS)
		{
			if(GS->IsObjectPickedUpByAPlayer())
			{
				GameMode->CompleteMission(true);				
			} else
			{
				GS->MulticastOnMissingObjective();
			}
		}
	}
}
