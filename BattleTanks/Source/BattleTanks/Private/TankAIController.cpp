// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find player tank"));
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetPlayerTank())
	{
		FVector PlayerLocation = GetPlayerTank()->GetActorLocation();
		GetControlledTank()->AimAt(PlayerLocation);
	}
		
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!Player) { return nullptr; }

	return Cast<ATank>(Player);
}
