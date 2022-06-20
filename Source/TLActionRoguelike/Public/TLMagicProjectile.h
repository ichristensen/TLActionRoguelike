// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TLActionEffect.h"
#include "TLProjectileBase.h"
#include "TLMagicProjectile.generated.h"

class UAudioComponent;
class UTLActionEffect;

UCLASS()
class TLACTIONROGUELIKE_API ATLMagicProjectile : public ATLProjectileBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult);

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FGameplayTag ParryTag;

	ATLMagicProjectile();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	TSubclassOf<UTLActionEffect>  BurningActionClass;

	virtual void PostInitializeComponents() override;
};
