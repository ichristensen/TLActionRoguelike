// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeComponent.h"

#include "GameFramework/Actor.h"
#include "TLActionRoguelike/TLActionRoguelikeGameModeBase.h"
#include "Engine/World.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("tl.DamageMultiplier"), 1.0f, TEXT("GLobal Damage modifier for Attribute Component"), ECVF_Cheat);

UAttributeComponent::UAttributeComponent()
{
	Health = 100;
	HealthMax = 100;
}

bool UAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (GetOwner()->CanBeDamaged())
	{
		// return false; @todo fix
	}

	float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
	Delta *= DamageMultiplier;

	float PrevHealth = Health;
	Health += Delta;
	Health = FMath::Clamp(Health, 0, HealthMax);
	Delta = Health - PrevHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, Delta);

	UE_LOG(LogTemp, Log, TEXT("Delta: %f - Equality: %d"), Delta, FMath::IsNearlyEqual(Health, 0));
	if(Delta < 0.0f && FMath::IsNearlyEqual(Health, 0))
	{
		ATLActionRoguelikeGameModeBase* GM = GetWorld()->GetAuthGameMode<ATLActionRoguelikeGameModeBase>();
		if(GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}

	return FMath::IsNearlyZero(Delta);
}

bool UAttributeComponent::IsAlive() const
{
	return (Health > 0.0f);
}

float UAttributeComponent::GetHealth() const
{
	return Health;
}

float UAttributeComponent::GetHealthMax() const
{
	return HealthMax;
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

