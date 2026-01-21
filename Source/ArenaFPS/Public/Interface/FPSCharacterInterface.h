// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FPSCharacterInterface.generated.h"

class AFPSWeaponBase;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFPSCharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ARENAFPS_API IFPSCharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AttachWeaponToActor(AFPSWeaponBase* WeaponClass) = 0;
	virtual FHitResult GetLookLocation(FVector StartLocation, float ShotDistance) = 0;
};
