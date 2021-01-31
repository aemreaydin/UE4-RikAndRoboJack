#include "WeaponProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AWeaponProjectile::AWeaponProjectile()
{
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision Component"));
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionProfileName("Projectile");
	CollisionComponent->OnComponentHit.AddDynamic(this, &AWeaponProjectile::OnHit);
	CollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
	CollisionComponent->CanCharacterStepUpOn = ECB_No;
	// Make collision component root
	RootComponent = CollisionComponent;

	// Find and add the sphere mesh as the static mesh component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshFinder(TEXT("/Game/Weapon/WeaponProjectile"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh Component"));
	if (SphereMeshFinder.Object)
	{
		ProjectileMesh->SetStaticMesh(SphereMeshFinder.Object);
	}
	ProjectileMesh->SetupAttachment(CollisionComponent);
	ProjectileMesh->SetRelativeScale3D(FVector(0.03f));

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->UpdatedComponent = CollisionComponent;
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;

	// Lifespan of the projectile
	InitialLifeSpan = 3.0f;
}

void AWeaponProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                              FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse then destroy if the other actor is a physics body
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 10.0f, GetActorLocation());
	}

	MakeNoise(1.0f, GetInstigator());
	Destroy();
}
