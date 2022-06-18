// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TLAction.h"
#include "Components/ActorComponent.h"
#include "TLActionComponent.generated.h"

class UTLAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TLACTIONROGUELIKE_API UTLActionComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	TArray<UTLAction*> Actions; 

public:
	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddActions(TSubclassOf<UTLAction> ActionClass);
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);
};
