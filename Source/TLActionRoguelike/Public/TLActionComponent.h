// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TLAction.h"
#include "TLActionEffect.h"
#include "Components/ActorComponent.h"
#include "TLActionComponent.generated.h"

class UTLAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TLACTIONROGUELIKE_API UTLActionComponent : public UActorComponent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TArray<UTLAction*> Actions;

	UPROPERTY(EditAnywhere, Category="Actions")
	TArray<TSubclassOf<UTLAction>> DefaultActions;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category="Actions")
	void AddActions(AActor* Instigator, TSubclassOf<UTLAction> ActionClass);
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StartActionByName(AActor* Instigator, FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	bool StopActionByName(AActor* Instigator, FName ActionName);
	
	UFUNCTION(BlueprintCallable, Category="Actions")
	void RemoveAction(UTLAction* Action);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Tags")
	FGameplayTagContainer ActiveGameplayTags;
};
