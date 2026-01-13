// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FPSWeaponBase.h"

// Sets default values
AFPSWeaponBase::AFPSWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

