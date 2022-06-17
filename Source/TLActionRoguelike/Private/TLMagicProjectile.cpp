// Fill out your copyright notice in the Description page of Project Settings.


#include "TLMagicProjectile.h"

#include "AttributeComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

void ATLMagicProjectile::OnComponentBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
	UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
	if(Actor && (Actor != GetInstigator()))
	{
		UAttributeComponent* AttributeComp = Cast<UAttributeComponent>(Actor->GetComponentByClass(UAttributeComponent::StaticClass()));
		if(AttributeComp)
		{
			AttributeComp->ApplyHealthChange(GetInstigator(), -Damage);
			//Destroy();
		}
	}
}

// Sets default values
ATLMagicProjectile::ATLMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ATLMagicProjectile::OnComponentBeginOverlap);

	Damage = 20;
}