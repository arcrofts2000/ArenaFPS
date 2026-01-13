// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/FPSCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(GetRootComponent());
	CameraComp->SetEnableFirstPersonFieldOfView(true);
	CameraComp->SetEnableFirstPersonScale(true);
	CameraComp->SetFirstPersonFieldOfView(60.f);
	CameraComp->SetFirstPersonScale(0.6f);
	CameraComp->bUsePawnControlRotation = true;

	MultiplayerMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MultiplayerMeshComp");
	MultiplayerMeshComp->SetupAttachment(GetRootComponent());
	MultiplayerMeshComp->SetOwnerNoSee(true);
	MultiplayerMeshComp->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::WorldSpaceRepresentation);
	MultiplayerMeshComp->SetCollisionProfileName("No Collision");

	GetMesh()->SetOnlyOwnerSee(true);
	GetMesh()->SetFirstPersonPrimitiveType(EFirstPersonPrimitiveType::FirstPerson);
	GetMesh()->SetCollisionProfileName("No Collision");
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
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