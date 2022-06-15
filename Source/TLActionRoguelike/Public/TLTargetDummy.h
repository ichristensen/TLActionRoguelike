// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TLTargetDummy.generated.h"

class UAttributeComponent;
class UStaticMeshComponent;

UCLASS()
class TLACTIONROGUELIKE_API ATLTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	ATLTargetDummy();

protected:
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* AttributeComp;
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UAttributeComponent* OwningComp, float NewHealth, float Delta);
};
