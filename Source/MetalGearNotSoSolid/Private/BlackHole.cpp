// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"

#include "DrawDebugHelpers.h"
#include "Components/SphereComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Black Hole Mesh"));
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComponent;

	OuterSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Outer Sphere"));
	OuterSphereComponent->SetupAttachment(MeshComponent);
	OuterSphereComponent->SetSphereRadius(3000.0f);
	
	InnerSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Inner Sphere"));
	InnerSphereComponent->SetupAttachment(MeshComponent);
	InnerSphereComponent->SetSphereRadius(100.0f);
	InnerSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::InnerSphereOverlap);

	HoleStrength = 2500.0f;
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> Components;
	OuterSphereComponent->GetOverlappingComponents(Components);
	for(const auto Component : Components)
	{
		if(Component && Component->IsSimulatingPhysics())
		{
			Component->AddRadialForce(GetActorLocation(), OuterSphereComponent->GetScaledSphereRadius(), -HoleStrength,
				RIF_Linear, true);
		}
	}
}

void ABlackHole::InnerSphereOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		OtherActor->Destroy();
	}
}

