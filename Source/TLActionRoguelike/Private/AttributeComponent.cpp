// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"

#include "GameFramework/Actor.h"

UAttributeComponent::UAttributeComponent()
{
	Health = 100;
	HealthMax = 100;
}

bool UAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (GetOwner()->CanBeDamaged())
	{
		return false;
	}

	float PrevHealth = Health;
	Health += Delta;
	Health = FMath::Clamp(Health, 0, HealthMax);
	Delta = Health - PrevHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);
	return FMath::IsNearlyZero(Delta);
}

bool UAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

UAttributeComponent* UAttributeComponent::GetAttributes(AActor* FromActor)
{
	if(FromActor)
	{
		return Cast<UAttributeComponent>(FromActor->GetComponentByClass(UAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool UAttributeComponent::IsActorAlive(AActor* Actor)
{
	UAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}
	return false; // dead if no AttributeComp
}

bool UAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -HealthMax);
}

