// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Aiming component not found on %s"), *GetName());
	}
	
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(GetPawn() && AimingComponent)) { return; }

	FVector HitLocation;		//Out Location

	
	//if we hit the landscape while aiming
	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	//Find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation,
										ViewportSizeY * CrosshairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(HitLocation, LookDirection);
	}
	
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection);
	
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector & HitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	if (GetWorld()->LineTraceSingleByChannel(HitResult,
		StartLocation,
		StartLocation + LookDirection * LineTraceRange,
		ECollisionChannel::ECC_Visibility
	))
	{
		HitLocation = HitResult.Location;
		return true;
	}

	HitLocation = FVector(0.0f);
	return false;
}


