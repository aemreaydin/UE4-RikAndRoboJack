#include "RikCharacter.h"
#include "WeaponProjectile.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ARikCharacter::ARikCharacter()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FPS Camera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
	CameraComponent->bUsePawnControlRotation = true;

	PlayerMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Player Mesh"));
	PlayerMeshComponent->SetupAttachment(CameraComponent);
	PlayerMeshComponent->CastShadow = false;
	PlayerMeshComponent->SetRelativeRotation(FRotator(2.0f, -15.0f, 5.0f));
	PlayerMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -160.0f));

	GunMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Mesh"));
	GunMeshComponent->CastShadow = false;
	GunMeshComponent->SetupAttachment(PlayerMeshComponent, "GripPoint");
}


void ARikCharacter::Fire()
{
	if (ProjectileClass)
	{
		const auto MuzzleLocation = GunMeshComponent->GetSocketLocation("Muzzle");
		const auto MuzzleRotation = GunMeshComponent->GetSocketRotation("Muzzle");

		// Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// Spawn the projectile at the muzzle
		GetWorld()->SpawnActor<AWeaponProjectile
		>(ProjectileClass, MuzzleLocation, MuzzleRotation, ActorSpawnParameters);
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	if (FireAnimation)
	{
		UAnimInstance* AnimInstance = PlayerMeshComponent->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->PlaySlotAnimationAsDynamicMontage(FireAnimation, "Arms", 0.0f);
		}
	}
}

void ARikCharacter::MoveForward(const float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void ARikCharacter::MoveRight(const float Val)
{
	if (Val != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Val);
	}
}

// Called to bind functionality to input
void ARikCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARikCharacter::Fire);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARikCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARikCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}
