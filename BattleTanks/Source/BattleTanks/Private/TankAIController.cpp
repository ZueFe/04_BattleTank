// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	auto Player = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(AimingComponent && Player))
	{
		//Move towards player
		MoveToActor(Player, AcceptanceRadius);		

		FVector PlayerLocation = Player->GetActorLocation();
		AimingComponent->AimAt(PlayerLocation);

		//Fire if ready
		AimingComponent->Fire();
	}
		
}

