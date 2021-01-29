// Fill out your copyright notice in the Description page of Project Settings.


#include "Launchpad.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALaunchpad::ALaunchpad()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 0.125f));
	RootComponent = StaticMesh;

	SphereComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SphereComponent->SetBoxExtent(FVector(25.0f, 25.0f, 150.0f));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ALaunchpad::LaunchActor);
	SphereComponent->SetupAttachment(StaticMesh);

	LaunchForce = 1000.0f;
}

void ALaunchpad::PlaySound()
{
	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void ALaunchpad::PlayParticleFX()
{
	if(ParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ParticleSystem, GetActorLocation());
	}
}

void ALaunchpad::LaunchActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp,
                             int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto LaunchDirection = GetActorForwardVector();
	LaunchDirection.Z = 1.0f;
	const auto OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter)
	{
		OtherCharacter->LaunchCharacter(LaunchDirection *
		                                LaunchForce, true, false);

		PlaySound();
		PlayParticleFX();
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(LaunchDirection * LaunchForce, NAME_None, true);

		PlaySound();
		PlayParticleFX();
	}
}
