#include "RoboJackCharacter.h"


#include "AIController.h"
#include "MGNSSGameMode.h"
#include "RikCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/PawnSensingComponent.h"
#include "Net/UnrealNetwork.h"

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

	Patrol();
}

void ARoboJackCharacter::ResetRotation()
{
	if (AIState == EAIState::Alert) return;

	SetActorRotation(OriginalRotation);
	SetAIState(EAIState::Idle);
	Patrol();
}

void ARoboJackCharacter::OnRep_AIState()
{
	OnAIStateChanged(AIState);
}

void ARoboJackCharacter::SetAIState(const EAIState NewState)
{
	if (AIState == NewState) return;

	AIState = NewState;
	OnRep_AIState();
}

// Called every frame
void ARoboJackCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (TargetPoints.Num() == 0) return;

	const auto Distance = (GetActorLocation() - TargetPoints[CurrentTargetPointIndex]->GetActorLocation()).Size2D();
	UE_LOG(LogTemp, Warning, TEXT("%f"), Distance);
	if (Distance < 50)
	{
		CurrentTargetPointIndex++;
		CurrentTargetPointIndex %= TargetPoints.Num();
		Patrol();
	}
}

void ARoboJackCharacter::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn) return;
	StopPatrol();

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
	if (AIState == EAIState::Alert) return;
	StopPatrol();

	auto NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Location);
	NewRotation.Pitch = 0.0f;
	NewRotation.Roll = 0.0f;
	SetActorRotation(NewRotation);

	GetWorldTimerManager().ClearTimer(ResetRotationTimerHandle);
	GetWorldTimerManager().SetTimer(ResetRotationTimerHandle, this, &ARoboJackCharacter::ResetRotation, 3.0f);

	SetAIState(EAIState::Suspicious);
}

void ARoboJackCharacter::Patrol()
{
	if (AIState == EAIState::Alert) return;
	if (TargetPoints.Num() == 0) return;

	MoveToTarget(TargetPoints[CurrentTargetPointIndex]);
}

void ARoboJackCharacter::MoveToTarget(AActor* Target) const
{
	const auto AI = Cast<AAIController>(GetController());
	if (AI)
	{
		AI->MoveToActor(Target);
	}
}

void ARoboJackCharacter::StopPatrol() const
{
	GetController()->StopMovement();
}

void ARoboJackCharacter::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( ARoboJackCharacter, AIState ); 
}