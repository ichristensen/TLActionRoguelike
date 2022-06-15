// Fill out your copyright notice in the Description page of Project Settings.


#include "TLTargetDummy.h"

#include "AttributeComponent.h"
#include "Components/StaticMeshComponent.h"

ATLTargetDummy::ATLTargetDummy()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	RootComponent = StaticMeshComp;

	AttributeComp = CreateDefaultSubobject<UAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &ATLTargetDummy::OnHealthChanged);
}

void ATLTargetDummy::OnHealthChanged(AActor* InstigatorActor, UAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if(Delta < 0.0f)
	{
		StaticMeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}
