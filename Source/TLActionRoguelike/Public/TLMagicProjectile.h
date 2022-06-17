// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLProjectileBase.h"
#include "TLMagicProjectile.generated.h"

class UAudioComponent;

UCLASS()
class TLACTIONROGUELIKE_API ATLMagicProjectile : public ATLProjectileBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void OnComponentBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor, UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg,
	                             const FHitResult& HitResult);
	// Sets default values for this actor's properties
	ATLMagicProjectile();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
};
