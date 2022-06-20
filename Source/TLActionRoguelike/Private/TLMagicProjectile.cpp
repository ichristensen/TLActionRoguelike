// Fill out your copyright notice in the Description page of Project Settings.


#include "TLMagicProjectile.h"

#include "TLActionComponent.h"
#include "TLActionEffect.h"
#include "TLFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

ATLMagicProjectile::ATLMagicProjectile()
{
	SphereComp->SetSphereRadius(20.0f);
	Damage = 20;
}

void ATLMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATLMagicProjectile::OnActorOverlap);
	
}

void ATLMagicProjectile::OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
                                        UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if(Actor && Actor == GetInstigator())
	{
		return;
	}
	
	if(Actor)
	{
		UTLActionComponent* ActionComp = Cast<UTLActionComponent>(Actor->GetComponentByClass(UTLActionComponent::StaticClass()));
		if(ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			ProjectileMovementComp->Velocity = -ProjectileMovementComp->Velocity;
			SetInstigator(Cast<APawn>(Actor));
			return;
		}
		
		UTLFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), Actor, Damage, HitResult);
		ActionComp->AddActions(GetInstigator(), BurningActionClass);
	}
	Explode();
}
