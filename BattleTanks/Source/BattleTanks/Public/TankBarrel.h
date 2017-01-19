// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	//-1 is max downward speed, +1 is max up movement
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 5.0f;

	UPROPERTY(EditAnywhere)
	float MaxDegreesElevation = 35.0f;

	UPROPERTY(EditAnywhere)
	float MinDegreesElevation = 0.0f;
	
};
