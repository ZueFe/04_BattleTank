// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTanks.h"
#include "Projectile.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	Projectile->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::LaunchProjectile(float Speed)
{
	Projectile->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	Projectile->Activate(true);
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

