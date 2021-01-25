// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "RikCharacter.generated.h"

class AWeaponProjectile;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class METALGEARNOTSOSOLID_API ARikCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARikCharacter();

	// Weapon Projectile class to spawn
	UPROPERTY(EditDefaultsOnly, Category="Projectile")
	TSubclassOf<AWeaponProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay")
	UAnimSequence* FireAnimation;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* PlayerMeshComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Mesh")
	USkeletalMeshComponent* GunMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* CameraComponent;
	
public:	
	USkeletalMeshComponent* GetPlayerMesh() const { return PlayerMeshComponent; }
	UCameraComponent* GetFPSCamera() const { return CameraComponent; }
	// TODO Make a 3rd Person Camera

protected:
	// Fire a projectile
	void Fire();

	// Handles moving forward, backward, left, right
	void MoveForward(float Val);
	void MoveRight(float Val);

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;	
};
