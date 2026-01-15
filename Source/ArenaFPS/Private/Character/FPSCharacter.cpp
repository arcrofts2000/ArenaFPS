// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Weapon/FPSWeaponBase.h"


AFPSCharacter::AFPSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Listing socket names here - hardcoded and visible anywhere if designers need to see it without VS
	HeadSocketName = "HeadSocket";
	LeftHandSocketName = "LeftHandSocket";
	RightHandSocketName = "RightHandSocket";

	// Setting up First Person Mesh
	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);
	GetMesh()->SetCollisionProfileName("No Collision");

	// Setting up the camera, and attaching to First Person Mesh
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(GetMesh(), HeadSocketName);
	CameraComp->SetEnableFirstPersonFieldOfView(true);
	CameraComp->SetEnableFirstPersonScale(true);
	CameraComp->SetFirstPersonFieldOfView(60.f);
	CameraComp->SetFirstPersonScale(0.6f);
	CameraComp->bUsePawnControlRotation = true;

	// Setting Multiplayer Mesh, invisible to the player / owner
	MultiplayerMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MultiplayerMeshComp");
	MultiplayerMeshComp->SetupAttachment(GetRootComponent());
	MultiplayerMeshComp->SetOwnerNoSee(true);
	MultiplayerMeshComp->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::WorldSpaceRepresentation);
	MultiplayerMeshComp->SetCollisionProfileName("No Collision");
}


void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// ~Begin IFPSCharacterInterface Override

void AFPSCharacter::AttachWeaponToActor(AFPSWeaponBase* WeaponClass)
{	
	WeaponClass->SetActorOwner(this);
	WeaponClass->AttachToActor(this, FAttachmentTransformRules::SnapToTargetIncludingScale);

	WeaponClass->GetTPWeaponMesh()->AttachToComponent(MultiplayerMeshComp, FAttachmentTransformRules::SnapToTargetIncludingScale, RightHandSocketName);
	WeaponClass->GetFPWeaponMesh()->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, RightHandSocketName);
}

// ~End IFPSCharacterInterface Override




void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PC = GetController<APlayerController>();
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMappingContext, 0);

	if (UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		InputComp->BindAction(Input_MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);
		InputComp->BindAction(Input_LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);
		InputComp->BindAction(Input_JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	}
}


/* Movement Functions */
void AFPSCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), MoveValue.Y);
	AddMovementInput(GetActorRightVector(), MoveValue.X);
}


void AFPSCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookValue = Value.Get<FVector2D>();
	
	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(LookValue.Y);
}