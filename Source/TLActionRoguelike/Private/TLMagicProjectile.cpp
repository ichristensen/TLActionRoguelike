// Fill out your copyright notice in the Description page of Project Settings.


#include "TLMagicProjectile.h"

#include "AttributeComponent.h"
#include "TLFunctionLibrary.h"
#include "Particles/ParticleSystemComponent.h"

ATLMagicProjectile::ATLMagicProjectile()
{
	Damage = 20;
}

void ATLMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// UE_LOG(LogTemp, Log, TEXT("ATLMagicProjectile::OnActorHit"));
	if(OtherActor == GetInstigator())
	{
		// UE_LOG(LogTemp, Log, TEXT("Hit Self - exiting"));
		return;
	}

	UTLFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, Damage, Hit);

	// if(OtherActor && (OtherActor != GetInstigator()))
	// {
	// 	UAttributeComponent* AttributeComp = Cast<UAttributeComponent>(OtherActor->GetComponentByClass(UAttributeComponent::StaticClass()));
	// 	if(AttributeComp)
	// 	{
	// 		AttributeComp->ApplyHealthChange(GetInstigator(), -Damage);
	// 	}
	// }
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}