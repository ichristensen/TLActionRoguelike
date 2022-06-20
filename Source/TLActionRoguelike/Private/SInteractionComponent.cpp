// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"

#include "Engine/Public/CollisionQueryParams.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "DrawDebugHelpers.h"

USInteractionComponent::USInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	TraceDistance = 1000.0f;
	TraceRadius = 30.0f;
	CollisionChannel = ECC_WorldDynamic;
}

void USInteractionComponent::FindBestInteractable()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	AActor* MyOwner = GetOwner();
	
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	const FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance);

	TArray<FHitResult> Hits;
	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);
	const bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);
	const FColor Color = (bBlockingHit ? FColor::Green : FColor::Red);

	FocusedActor = nullptr;

	for(const FHitResult& Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if(HitActor->Implements<USGameplayInterface>())
			{
				FocusedActor = HitActor;
				break;
			}
		}
	}

	if (FocusedActor)
	{
		if(!DefaultWidgetClass && ensure(DefaultWidgetClass))
		{
			DefaultWidgetInstance = CreateWidget<UTLWorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}

		if(DefaultWidgetInstance)
		{
			DefaultWidgetInstance->AttachedActor = FocusedActor;
			if(!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}
	}
	else if(DefaultWidgetInstance)
	{
		DefaultWidgetInstance->RemoveFromParent();
	}
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FindBestInteractable();
}

void USInteractionComponent::PrimaryInteract()
{
	if (FocusedActor == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("No Focus Actor to interact."));
		return;
	}
	
	APawn* MyPawn = Cast<APawn>(GetOwner());
	ISGameplayInterface::Execute_Interact(FocusedActor, MyPawn);
}

