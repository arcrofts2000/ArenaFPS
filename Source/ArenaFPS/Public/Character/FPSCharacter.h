// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/FPSCharacterInterface.h"
#include "FPSCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class ARENAFPS_API AFPSCharacter : public ACharacter, public IFPSCharacterInterface
{
	GENERATED_BODY()

public:
	AFPSCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



public:
	/* ~Begin IFPSCharacterInterface Override */
	virtual void AttachWeaponToActor(AFPSWeaponBase* WeaponClass) override;
	/* ~End IFPSCharacterInterface Override */


protected:
	/* Sockets */
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	FName HeadSocketName;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	FName LeftHandSocketName;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	FName RightHandSocketName;

	/* Components */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> MultiplayerMeshComp;


	/* Input Components */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_JumpAction;



	/* Functions */
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
};
