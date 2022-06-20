// Fill out your copyright notice in the Description page of Project Settings.


#include "TLActionComponent.h"

void UTLActionComponent::BeginPlay()
{
	Super::BeginPlay();
	for(TSubclassOf<UTLAction> ActionClass : DefaultActions)
	{
		AddActions(GetOwner(), ActionClass);
	}
}

void UTLActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTLActionComponent::AddActions(AActor* Instigator, TSubclassOf<UTLAction> ActionClass)
{
	if(!ensure(ActionClass))
	{
		return;
	}

	UTLAction* NewAction = NewObject<UTLAction>(this, ActionClass);
	if(ensure(NewAction))
	{
		Actions.Add(NewAction);
		if(NewAction->bAutoStart && ensure(NewAction->CanStart(Instigator)))
		{
			NewAction->StartAction(Instigator);
		}
	}
}

bool UTLActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for(UTLAction* Action : Actions)
	{
		if(Action && (Action->ActionName == ActionName))
		{
			if(!Action->CanStart(Instigator))
			{
				UE_LOG(LogTemp, Log, TEXT("Failed to run: %s"), *ActionName.ToString());
				continue;
			}

			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool UTLActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for(UTLAction* Action : Actions)
	{
		if(Action && (Action->ActionName == ActionName))
		{
			if(Action->IsRunning())
			{
				Action->StopAction(Instigator);
				return true;
			}
		}
	}
	return false;
}

void UTLActionComponent::RemoveAction(UTLAction* Action)
{
	if(!ensure(Action && !Action->IsRunning()))
	{
		return;
	}
	Actions.Remove(Action);
}
