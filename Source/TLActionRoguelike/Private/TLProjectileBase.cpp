#include "TLProjectileBase.h"

#include "TLBTTask_HealSelf.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ATLProjectileBase::ATLProjectileBase()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ATLProjectileBase::OnActorHit);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	RootComponent = SphereComp;

	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComp");
	ParticleSystemComp->SetupAttachment(RootComponent);
	
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComp->ProjectileGravityScale = 0.0f;
	ProjectileMovementComp->InitialSpeed = 800;
	
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);
}

void ATLProjectileBase::Explode_Implementation()
{
	if (ensure(IsValid(this)))
	{
		const FVector Location = GetActorLocation();
		const FRotator Rotation = GetActorRotation();
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, Location, Rotation);
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundBase, Location, Rotation);
		
		//UGameplayStatics::PlayWorldCameraShake(this, ImpactShake, GetActorLocation(), ImpactShakeInnerRadius, ImpactShakeOuterRadius);

		Destroy();
	}
}

void ATLProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Log, TEXT("ATLProjectileBase::OnActorHit"));
	Explode();
}

void ATLProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SetLifeSpan(4.0f);
}


