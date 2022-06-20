// Fill out your copyright notice in the Description page of Project Settings.


#include "TLAction.h"
#include "TLActionComponent.h"

void UTLAction::StartAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Running: %s"), *GetNameSafe(this));
	UTLActionComponent* ActionComp = GetOwningComponent();
	ActionComp->ActiveGameplayTags.AppendTags(GrantsTags);
	bIsRunning = true;
}

void UTLAction::StopAction_Implementation(AActor* Instigator)
{
	UE_LOG(LogTemp, Log, TEXT("Stopping: %s"), *GetNameSafe(this));
	ensureAlways(bIsRunning);
	UTLActionComponent* ActionComp = GetOwningComponent();
	ActionComp->ActiveGameplayTags.RemoveTags(GrantsTags);
	bIsRunning = false;
}

UTLActionComponent* UTLAction::GetOwningComponent() const
{
	return Cast<UTLActionComponent>(GetOuter());
}

bool UTLAction::CanStart_Implementation(AActor* Instigator)
{
	if(IsRunning())
	{
		return false;
	}

	UTLActionComponent* ActionComp = GetOwningComponent();
	if(ActionComp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}
	return true;
}

bool UTLAction::IsRunning() const
{
	return bIsRunning;
}

UWorld* UTLAction::GetWorld() const
{
	UActorComponent* Comp = Cast<UActorComponent>(GetOuter());
	if(Comp)
	{
		return Comp->GetWorld();
	}
	return nullptr;
}
