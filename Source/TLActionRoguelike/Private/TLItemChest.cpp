// Fill out your copyright notice in the Description page of Project Settings.


#include "TLItemChest.h"
#include "Components/StaticMeshComponent.h"

void ATLItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	ISGameplayInterface::Interact_Implementation(InstigatorPawn);

	LidMeshComp->SetRelativeRotation(FRotator(TargetPitch,0,0));
}

// Sets default values
ATLItemChest::ATLItemChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMeshComp"));
	RootComponent = BaseMeshComp;

	LidMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMeshComp"));
	LidMeshComp->SetupAttachment(BaseMeshComp);

	TargetPitch = 110;
}