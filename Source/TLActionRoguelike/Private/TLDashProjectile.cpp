// Fill out your copyright notice in the Description page of Project Settings.


#include "TLDashProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "TimerManager.h"

ATLDashProjectile::ATLDashProjectile()
{
	ProjectileMovementComp->InitialSpeed = 200;
}

void ATLDashProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);
	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	ParticleSystemComp->DeactivateSystem();
	ProjectileMovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);
	
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ATLDashProjectile::TeleportInstigator, TeleportDelay);
}

void ATLDashProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);
	}
}

void ATLDashProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ATLDashProjectile::Explode, DetonateDelay);
}

