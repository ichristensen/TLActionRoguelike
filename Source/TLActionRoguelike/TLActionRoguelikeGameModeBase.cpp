// Copyright Epic Games, Inc. All Rights Reserved.


#include "TLActionRoguelikeGameModeBase.h"

#include "AttributeComponent.h"
#include "DrawDebugHelpers.h"
#include "EngineUtils.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "TimerManager.h"
#include "TLPlayerState.h"
#include "AI/TLAICharacter.h"

static TAutoConsoleVariable<bool> CVarSpawnBots(TEXT("tl.SpawnBots"), true, TEXT("Enable Spawning of bots via timer."), ECVF_Cheat);

ATLActionRoguelikeGameModeBase::ATLActionRoguelikeGameModeBase()
{
	SpawnTimerInterval = 2.0f;

	CreditsPerKill = 20;
	PlayerStateClass = ATLPlayerState::StaticClass();
}

void ATLActionRoguelikeGameModeBase::OnActorKilled(AActor* VictimActor, AActor* KillerActor)
{
	UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Victim: %s, Killer: %s"), *GetNameSafe(VictimActor), *GetNameSafe(KillerActor));

	if(ACharacter* Player = Cast<ACharacter>(VictimActor))
	{
		FTimerHandle TimerHandle_RespawnDelay;
		FTimerDelegate Delegate;
		Delegate.BindUFunction(this, "RespawnPlayerElapsed", Player->GetController());
		float RespawnDelay = 2.0f;
		GetWorldTimerManager().SetTimer(TimerHandle_RespawnDelay, Delegate, RespawnDelay, false);
		UE_LOG(LogTemp, Log, TEXT("OnActorKilled: Starting Respawn"));
	}

	if(APawn* KillerPawn = Cast<APawn>(KillerActor))
	{
		if(ATLPlayerState* PS = KillerPawn->GetPlayerState<ATLPlayerState>())
		{
			PS->AddCredits(CreditsPerKill);
		}
	}
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
	if(!CVarSpawnBots.GetValueOnGameThread())
	{
		UE_LOG(LogTemp, Warning, TEXT("Bot spawning disabled via cvar 'CVarSpawnBots'."));
		return;
	}
	
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

void ATLActionRoguelikeGameModeBase::RespawnPlayerElapsed(AController* Controller)
{
	if(ensure(Controller))
	{
		Controller->UnPossess();
		RestartPlayer(Controller);
	}
}

