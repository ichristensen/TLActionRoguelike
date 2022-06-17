// Fill out your copyright notice in the Description page of Project Settings.


#include "TLHealthPotion.h"

#include "AttributeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

void ATLHealthPotion::CooldownComplete()
{
	RootComponent->SetVisibility(true);
	SetActorEnableCollision(true);
}

// Sets default values
ATLHealthPotion::ATLHealthPotion()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;
	
	HealAmount = 50;
	CooldownTime = 10;
}

void ATLHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);

	RootComponent->SetVisibility(false);
	SetActorEnableCollision(false);
	
	GetWorldTimerManager().ClearTimer(TimerHandle_Cooldown);
	GetWorldTimerManager().SetTimer(TimerHandle_Cooldown, this, &ATLHealthPotion::CooldownComplete, CooldownTime, false);
	
	if(UAttributeComponent* AttributeComponent = Cast<UAttributeComponent>(InstigatorPawn->GetComponentByClass(UAttributeComponent::StaticClass())))
	{
		AttributeComponent->ApplyHealthChange(this, HealAmount);
	}
}
