// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "Tank.h"



// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAimingComponent::Initialise(UTankBarrel * TankBarrelToSet, UTankTurret * TankTurretToSet)
{
	Barrel = TankBarrelToSet;
	Turret = TankTurretToSet;
}

// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();

}


// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Ammunition <= 0)
	{
		FiringState = EFiringState::NoAmmo;
	}

	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}

	else
	{
		FiringState = EFiringState::Locked;
	}
}

int UAimingComponent::GetAmmunition() const
{
	return Ammunition;
}

void UAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
		MoveTurretYaw();
	}
}

void UAimingComponent::MoveBarrelTowards()
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;


	Barrel->Elevate(DeltaRotator.Pitch);
}
void UAimingComponent::MoveTurretYaw()
{
	if (!ensure(Barrel) || !ensure(Turret)) { return; }
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	if (FMath::Abs(DeltaRotator.Yaw) > 180)
		Turret->RotateTurret(-DeltaRotator.Yaw);
	else
		Turret->RotateTurret(DeltaRotator.Yaw);

}

bool UAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	return !(Barrel->GetForwardVector().Equals(AimDirection, 0.01f));
}

void UAimingComponent::Fire()
{
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{

		if (!ensure(Barrel)) { return; }
		if (!ensure(BlueprintSpawnable)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(BlueprintSpawnable,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		if (!ensure(Projectile)) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		Ammunition--;
	}
}

EFiringState UAimingComponent::GetFiringState() const
{
	return FiringState;
}
