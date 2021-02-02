#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "RikCharacter.generated.h"

class AWeaponProjectile;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class METALGEARNOTSOSOLID_API ARikCharacter final : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARikCharacter();

	virtual void Tick(float DeltaTime) override;
	
	// Weapon Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TSubclassOf<AWeaponProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	UAnimSequence* FireAnimation;

	UPROPERTY(BlueprintReadOnly, Category="Gameplay")
	bool bIsObjectPickedUp;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* PlayerMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* GunMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UPawnNoiseEmitterComponent* NoiseEmitterComponent;	

public:
	USkeletalMeshComponent* GetPlayerMesh() const { return PlayerMeshComponent; }
	UCameraComponent* GetFPSCamera() const { return CameraComponent; }
	// TODO Make a 3rd Person Camera

protected:
	// Fire should be called from the server
	UFUNCTION(Server, WithValidation, Reliable)
	void Server_Fire();
	
	// Fire a projectile
	void Fire();

	// Handles moving forward, backward, left, right
	void MoveForward(float Val);
	void MoveRight(float Val);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
