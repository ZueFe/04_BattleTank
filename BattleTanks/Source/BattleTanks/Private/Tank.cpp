// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Projectile.h"
#include "TankBarrel.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	AimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	AimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastTimeFired) > ReloadTimeInSeconds;
	if (!Barrel || !isReloaded) { return; }

	//Spawn a projectile on socket location
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, 
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile")));

	Projectile->LaunchProjectile(LaunchSpeed);

	LastTimeFired = FPlatformTime::Seconds();

}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	AimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	AimingComponent->SetTurretReference(TurretToSet);
}

