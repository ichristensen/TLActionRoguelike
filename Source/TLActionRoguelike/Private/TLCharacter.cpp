// Fill out your copyright notice in the Description page of Project Settings.


#include "TLCharacter.h"

#include "SInteractionComponent.h"
#include "TLActionComponent.h"
#include "AttributeComponent.h"
#include "TimerManager.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
ATLCharacter::ATLCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);
	
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraArmComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<UAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<UTLActionComponent>("ActionComp");
	
	InteractionComp->RegisterComponent();

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	TimeToHitParamName = "TimeToHit";
}

// Called when the game starts or when spawned
void ATLCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATLCharacter::MoveForward(float value)
{
	FRotator ControlBot = GetControlRotation();
	ControlBot.Pitch = 0;
	ControlBot.Roll = 0;
	
	AddMovementInput(ControlBot.Vector(), value);
}

void ATLCharacter::MoveRight(float value)
{
	FRotator ControlBot = GetControlRotation();
	ControlBot.Pitch = 0;
	ControlBot.Roll = 0;

	const FVector RightVector = FRotationMatrix(ControlBot).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, value);
}

void ATLCharacter::PrimaryAttack()
{
	ActionComp->StartActionByName(this, "PrimaryAttack");
}

void ATLCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ATLCharacter::Dash()
{
	ActionComp->StartActionByName(this, "Dash");
}

void ATLCharacter::BlackHoleAttack()
{
	ActionComp->StartActionByName(this, "BlackHole");
}

void ATLCharacter::SprintStart()
{
	ActionComp->StartActionByName(this, "Sprint");
}

void ATLCharacter::SprintStop()
{
	ActionComp->StopActionByName(this, "Sprint");
}

void ATLCharacter::OnHealthChanged(AActor* InstigatorActor, UAttributeComponent* OwningComp, float NewHealth,
	float Delta)
{
	if(Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
	}
	
	if((NewHealth <= 0.0f) && (Delta < 0.0f))
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}

void ATLCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ATLCharacter::OnHealthChanged);
}

FVector ATLCharacter::GetPawnViewLocation() const
{
	return CameraComp->GetComponentLocation();
}

// Called to bind functionality to input
void ATLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATLCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATLCharacter::MoveRight);
	
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ATLCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("BlackHole", IE_Pressed, this, &ATLCharacter::BlackHoleAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ATLCharacter::PrimaryInteract);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &ATLCharacter::Dash);
	
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ATLCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ATLCharacter::SprintStop);
}

void ATLCharacter::HealSelf(float Amount)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}

