// Fill out your copyright notice in the Description page of Project Settings.


#include "TLRedBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ATLRedBarrel::ATLRedBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	//StaticMeshComp->SetCollisionProfileName("Projectile");
	RootComponent = StaticMeshComp;
	
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp ->SetupAttachment(StaticMeshComp);

	StaticMeshComp->OnComponentHit.AddDynamic(this, &ATLRedBarrel::OnHit);
}

// Called when the game starts or when spawned
void ATLRedBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATLRedBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATLRedBarrel::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForceComp->FireImpulse();

	const FVector Pos = GetActorLocation();
	DrawDebugSphere(GetWorld(), Pos, 200.0f, 12, FColor::Yellow, 1.0f, 0.0f);
	Destroy();
}

