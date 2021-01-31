// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "RoboJackCharacter.generated.h"

class UPawnSensingComponent;


UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alert
};

UCLASS()
class METALGEARNOTSOSOLID_API ARoboJackCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARoboJackCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
	UPawnSensingComponent* PawnSensingComponent;

	FRotator OriginalRotation;
	FTimerHandle ResetRotationTimerHandle;

	UPROPERTY(VisibleAnywhere)
	EAIState AIState;
	
	void SetAIState(EAIState NewState);
	
	UFUNCTION(BlueprintImplementableEvent, Category="AI")
	void OnAIStateChanged(EAIState NewState);
public:	
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ResetRotation();
	
	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);
	UFUNCTION()
	void OnPawnHeard(APawn* HeardPawn, const FVector& Location, float Volume);
};
