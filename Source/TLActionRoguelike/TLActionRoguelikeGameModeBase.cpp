// Copyright Epic Games, Inc. All Rights Reserved.


#include "TLActionRoguelikeGameModeBase.h"

#include "AttributeComponent.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "TimerManager.h"
#include "AI/TLAICharacter.h"

ATLActionRoguelikeGameModeBase::ATLActionRoguelikeGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void ATLActionRoguelikeGameModeBase::StartPlay()
{
	Super::StartPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ATLActionRoguelikeGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ATLActionRoguelikeGameModeBase::KillAll()
{
	for(TActorIterator<ATLAICharacter> It(GetWorld()); It; ++It)
	{
		ATLAICharacter* Bot = *It;
		UAttributeComponent* AttributeComp = UAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && (AttributeComp->IsAlive()))
		{
			AttributeComp->Kill(this);
		}
	}

}

void ATLActionRoguelikeGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance,
                                                      EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Failed"));
		return;
	}
	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0) || Locations.IsEmpty())
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
	}
}

void ATLActionRoguelikeGameModeBase::SpawnBotTimerElapsed()
{
	int32 NrOfAliveBots = 0;
	for(TActorIterator<ATLAICharacter> It(GetWorld()); It; ++It)
	{
		ATLAICharacter* Bot = *It;
		UAttributeComponent* AttributeComp = UAttributeComponent::GetAttributes(Bot);
		if (ensure(AttributeComp) && (AttributeComp->IsAlive()))
		{
			++NrOfAliveBots;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots."), NrOfAliveBots);
	
	const float MaxBotCount = [&]()
	{
		if (DifficultyCurve)
		{
			return DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
		}
		return 10.0f;
	}();
	
	if(NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At maximum bot capacity. Skipping bot spawn."));
		return;
	}
	
	auto QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ATLActionRoguelikeGameModeBase::OnQueryCompleted);
	}
}

