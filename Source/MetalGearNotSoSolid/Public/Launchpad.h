// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Launchpad.generated.h"

class UBoxComponent;
UCLASS()
class METALGEARNOTSOSOLID_API ALaunchpad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALaunchpad();

	UPROPERTY(EditInstanceOnly, Category="Force")
	float LaunchForce;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	UBoxComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category="Particle")
	UParticleSystem* ParticleSystem;

	UPROPERTY(EditDefaultsOnly, Category="Sound")
	USoundBase* LaunchSound;


	void PlaySound();
	void PlayParticleFX();

	UFUNCTION()
	void LaunchActor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                 int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
