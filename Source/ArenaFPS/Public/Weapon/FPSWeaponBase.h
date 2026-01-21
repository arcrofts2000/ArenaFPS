// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWeaponBase.generated.h"

class USkeletalMeshComponent;
class USphereComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class ARENAFPS_API AFPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFPSWeaponBase();

protected:
	virtual void BeginPlay() override;


public:
	/* Getters / Setters */
	USkeletalMeshComponent* GetTPWeaponMesh() const { return this->TPWeaponMesh; }
	USkeletalMeshComponent* GetFPWeaponMesh() const { return this->FPWeaponMesh; }

	AActor* GetActorOwner() const { return ActorOwner; }
	void SetActorOwner(AActor* NewOwner) { ActorOwner = NewOwner; }


	/* Input */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> IMC_Weapon;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Fire;


protected:
	/* Variables */
	AActor* ActorOwner;


	/* Components */
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> TPWeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> FPWeaponMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TObjectPtr<USphereComponent> SphereCollisionComp;


	


	/* Functions */
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION(BlueprintNativeEvent)
	void OnFire();
};
