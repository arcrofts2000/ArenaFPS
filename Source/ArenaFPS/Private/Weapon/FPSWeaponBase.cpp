// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/FPSWeaponBase.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Interface/FPSCharacterInterface.h"


AFPSWeaponBase::AFPSWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollisionComp = CreateDefaultSubobject<USphereComponent>("SphereCollisionComp");
	SphereCollisionComp->SetupAttachment(GetRootComponent());
	SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSWeaponBase::OnOverlap);

	FPWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("FPWeaponMesh");
	FPWeaponMesh->SetupAttachment(GetRootComponent());

	TPWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("TPWeaponMesh");
	TPWeaponMesh->SetupAttachment(GetRootComponent());
}

void AFPSWeaponBase::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetActorOwner())
		Cast<IFPSCharacterInterface>(OtherActor)->AttachWeaponToActor(this);
}


void AFPSWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AFPSWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

