#include "RoboJackCharacter.h"

#include "DrawDebugHelpers.h"
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
}

// Called every frame
void ARoboJackCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARoboJackCharacter::OnPawnSeen(APawn* SeenPawn)
{
	if (!SeenPawn) return;

	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 16, FColor::Blue, true, 10.0f);
}

void ARoboJackCharacter::OnPawnHeard(APawn* HeardPawn, const FVector& Location, float Volume)
{
	DrawDebugSphere(GetWorld(), Location, 32.0f, 16, FColor::Red, true, 10.0f);
}
