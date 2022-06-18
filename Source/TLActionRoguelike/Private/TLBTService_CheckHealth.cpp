// Fill out your copyright notice in the Description page of Project Settings.


#include "TLBTService_CheckHealth.h"

#include "AIController.h"
#include "AttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

void UTLBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* AIPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ensure(AIPawn))
	{
		UAttributeComponent* AttributeComp = UAttributeComponent::GetAttributes(AIPawn);
		if(ensure(AttributeComp ))
		{
			bool bLowHealth = (AttributeComp->GetHealth() / AttributeComp->GetHealthMax()) < LowHealthFraction;
			UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
			BlackboardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, bLowHealth);
		}
	}
}

UTLBTService_CheckHealth::UTLBTService_CheckHealth()
{
	LowHealthFraction = 0.3f;
}
