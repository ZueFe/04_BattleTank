// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto AITank = Cast<ATank>(GetPawn());
	auto Player = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (AITank || Player)
	{
		//Move towards player
		MoveToActor(Player, AcceptanceRadius);		//TODO check radius is in cm

		FVector PlayerLocation = Player->GetActorLocation();
		AITank->AimAt(PlayerLocation);

		//Fire if ready
		AITank->Fire();
	}
		
}

