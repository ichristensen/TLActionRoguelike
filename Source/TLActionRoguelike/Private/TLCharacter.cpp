// Fill out your copyright notice in the Description page of Project Settings.


#include "TLCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

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

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
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
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	const FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

// Called every frame
void ATLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
}

