// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGameplayInterface.h"
#include "GameFramework/Actor.h"
#include "TLItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class TLACTIONROGUELIKE_API ATLItemChest : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ATLItemChest();

	UPROPERTY(EditAnywhere)
	float TargetPitch;
	
	void Interact_Implementation(APawn* InstigatorPawn) override;
	

protected:
	
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMeshComp;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
