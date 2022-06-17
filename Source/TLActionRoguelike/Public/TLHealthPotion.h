// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "TLHealthPotion.generated.h"

UCLASS()
class TLACTIONROGUELIKE_API ATLHealthPotion : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;
	
	UPROPERTY(VisibleAnywhere)
	float HealAmount;
	
	UPROPERTY(VisibleAnywhere)
	float CooldownTime;

	FTimerHandle TimerHandle_Cooldown;

	void CooldownComplete();
	
public:	
	// Sets default values for this actor's properties
	ATLHealthPotion();

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

};
