// Fill out your copyright notice in the Description page of Project Settings.


#include "TLActionComponent.h"

void UTLActionComponent::AddActions(TSubclassOf<UTLAction> ActionClass)
{
	if(!ensure(ActionClass))
	{
		return;
	}

	UTLAction* NewAction = NewObject<UTLAction>(this, ActionClass);
	if(ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
}

bool UTLActionComponent::StartActionByName(AActor* Instigator, FName ActionName)
{
	for(UTLAction* Action : Actions)
	{
		if(Action && (Action->ActionName == ActionName))
		{
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
			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;
}
