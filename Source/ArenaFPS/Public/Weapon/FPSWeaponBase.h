// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSWeaponBase.generated.h"

class USkeletalMeshComponent;
class USphereComponent;

UCLASS()
class ARENAFPS_API AFPSWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AFPSWeaponBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;




public:
	/* Getters / Setters */
	USkeletalMeshComponent* GetTPWeaponMesh() const { return this->TPWeaponMesh; }
	USkeletalMeshComponent* GetFPWeaponMesh() const { return this->FPWeaponMesh; }

	AActor* GetActorOwner() const { return ActorOwner; }
	void SetActorOwner(AActor* NewOwner) { ActorOwner = NewOwner; }

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
};
