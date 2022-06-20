// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "TLAction.generated.h"

class UTLActionComponent;
class UWorld;

/**
 * 
 */
UCLASS(Blueprintable)
class TLACTIONROGUELIKE_API UTLAction : public UObject
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category="Tags")
	FGameplayTagContainer BlockedTags;

	UFUNCTION(BlueprintCallable, Category="Action")
	UTLActionComponent* GetOwningComponent() const;

	bool bIsRunning;

public:
	UPROPERTY(EditDefaultsOnly, Category="Action")
	FName ActionName;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	bool CanStart(AActor* Instigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	void StartAction(AActor* Instigator);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Action")
	void StopAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool IsRunning() const;

	UPROPERTY(EditDefaultsOnly, Category="Action")
	bool bAutoStart;

	virtual UWorld* GetWorld() const override;
};
