#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "WeaponProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class METALGEARNOTSOSOLID_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()

public:
	AWeaponProjectile();

protected:
	// Used to check sphere collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	USphereComponent* CollisionComponent;

	// Projectile movement component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Static Mesh Component to render projectile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* ProjectileMesh;

public:
	// Called when projectile hits something
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
	           const FHitResult& Hit);

	USphereComponent* GetCollisionComponent() const { return CollisionComponent; }
	UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovementComponent; }
};
