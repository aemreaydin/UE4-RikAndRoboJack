#include "RoboJackCharacter.h"

#include "DrawDebugHelpers.h"
#include "MGNSSGameMode.h"
#include "RikCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ARoboJackCharacter::ARoboJackCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn Sense"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &ARoboJackCharacter::OnPawnSeen);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &ARoboJackCharacter::OnPawnHeard);
}

// Called when the game starts or when spawned
void ARoboJackCharacter::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();
	SetAIState(EAIState::Idle);
}

void ARoboJackCharacter::ResetRotation()
{
	if(AIState == EAIState::Alert) return;
	
	SetActorRotation(OriginalRotation);
	SetAIState(EAIState::Idle);
}

void ARoboJackCharacter::SetAIState(const EAIState NewState)
{
	if(AIState == NewState) return;

	AIState = NewState;
	OnAIStateChanged(NewState);
}

// Called every frame
void ARoboJackCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARoboJackCharacter::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn) return;

	const auto GameMode = Cast<AMGNSSGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode && !GameMode->bIsMissionComplete)
	{
		GameMode->CompleteMission(SeenPawn, false);
		GameMode->bIsMissionComplete = true;
	}

	GetWorldTimerManager().ClearTimer(ResetRotationTimerHandle);
	SetAIState(EAIState::Alert);
}

void ARoboJackCharacter::OnPawnHeard(APawn* HeardPawn, const FVector& Location, float Volume)
{
	if(AIState == EAIState::Alert) return;
	
	auto NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);
	NewRotation.Pitch = 0.0f;
	NewRotation.Roll = 0.0f;
	SetActorRotation(NewRotation);

	GetWorldTimerManager().ClearTimer(ResetRotationTimerHandle);
	GetWorldTimerManager().SetTimer(ResetRotationTimerHandle, this, &ARoboJackCharacter::ResetRotation, 3.0f);

	SetAIState(EAIState::Suspicious);
}
