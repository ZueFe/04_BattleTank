// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//Calculate the OutLaunchVelocity
	if (UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		RotateTurretTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//Get barrel rotation
	auto BarrelRotation = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	//Move the barrel the right amount this frame, given a max speed and elevation and the frame time
	Barrel->Elevate(DeltaRotator.Pitch);		
}

void UTankAimingComponent::RotateTurretTowards(FVector AimDirection)
{
	//Get barrel rotation
	auto BarrelRotation = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotation;

	//Move the barrel the right amount this frame, given a max speed and elevation and the frame time
	Turret->Rotate(DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	bool isReloaded = (FPlatformTime::Seconds() - LastTimeFired) > ReloadTimeInSeconds;
	if (!isReloaded) { return; }

	//Spawn a projectile on socket location
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile")));

	Projectile->LaunchProjectile(LaunchSpeed);

	LastTimeFired = FPlatformTime::Seconds();
}


