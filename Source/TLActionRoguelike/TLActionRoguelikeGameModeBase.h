// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "GameFramework/GameModeBase.h"
#include "TLActionRoguelikeGameModeBase.generated.h"

class UCurveFloat;
class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;

/**
 * 
 */
UCLASS()
class TLACTIONROGUELIKE_API ATLActionRoguelikeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="AI")
	float SpawnTimerInterval;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UEnvQuery* SpawnBotQuery;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TSubclassOf<AActor> MinionClass;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	UCurveFloat* DifficultyCurve;
	
	UPROPERTY(EditDefaultsOnly, Category="Credits")
	int CreditsPerKill;
	
	FTimerHandle TimerHandle_SpawnBots;
	

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void SpawnBotTimerElapsed();
	
	UFUNCTION()
	void RespawnPlayerElapsed(AController* Controller);
	
public:
	ATLActionRoguelikeGameModeBase();
	
	UFUNCTION()
	virtual void OnActorKilled(AActor* VictimActor, AActor* KillerActor);
	
	virtual void StartPlay() override;

	UFUNCTION(Exec)
	void KillAll();

};
