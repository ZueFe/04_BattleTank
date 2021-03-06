// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	float AcceptanceRadius = 3000;
	UTankAimingComponent* AimingComponent = nullptr;
};
