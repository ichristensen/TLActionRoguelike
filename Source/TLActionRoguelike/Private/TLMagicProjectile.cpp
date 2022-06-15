// Fill out your copyright notice in the Description page of Project Settings.


#include "TLMagicProjectile.h"

#include "AttributeComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

void ATLMagicProjectile::OnComponentBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if(Actor && (Actor != GetInstigator()))
	{
		UAttributeComponent* AttributeComp = Cast<UAttributeComponent>(Actor->GetComponentByClass(UAttributeComponent::StaticClass()));
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);
			Destroy();
		}
	}
}

// Sets default values
ATLMagicProjectile::ATLMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATLMagicProjectile::OnComponentBeginOverlap);
	RootComponent = SphereComp;

	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>("ParticleSystemComp");
	ParticleSystemComp->SetupAttachment(SphereComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComp");
	ProjectileMovementComp->InitialSpeed = 1000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void ATLMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATLMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

