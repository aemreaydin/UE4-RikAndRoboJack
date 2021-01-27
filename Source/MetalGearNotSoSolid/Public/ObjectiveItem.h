#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "ObjectiveItem.generated.h"

class USphereComponent;

UCLASS()
class METALGEARNOTSOSOLID_API AObjectiveItem : public AActor
{
	GENERATED_BODY()

public:
	AObjectiveItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category="Particle")
	UParticleSystem* ParticleFX;

	UPROPERTY(EditDefaultsOnly, Category="Particle")
	USoundBase* ParticlePickupSound;
public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
protected:
	void PlayParticleFX();
};
