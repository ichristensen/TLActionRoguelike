// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLProjectileBase.h"
#include "TLDashProjectile.generated.h"

/**
 * 
 */
UCLASS()
class TLACTIONROGUELIKE_API ATLDashProjectile : public ATLProjectileBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay;

	FTimerHandle TimerHandle_DelayedDetonate;

	virtual void Explode_Implementation() override;
	void TeleportInstigator();
	virtual void BeginPlay() override;
public:
	ATLDashProjectile();
	
};
