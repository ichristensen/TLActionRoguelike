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
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	ATLMagicProjectile();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;
};
