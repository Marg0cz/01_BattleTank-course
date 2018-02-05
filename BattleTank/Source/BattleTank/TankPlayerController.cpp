// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/PrimitiveComponent.h"
#include "TankPlayerController.h"
#include "Engine/World.h"



void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController is possessing: %s"), *GetControlledTank()->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("Tick function is working."));
	AimTowardsCrosshair();

}

FVector ATankPlayerController::GetReachLineStart() const
{
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			 PlayerViewPointLocation,
			 PlayerViewPointRotation);

		return PlayerViewPointLocation;
}

FVector ATankPlayerController::GetReachLineEnd() const
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewPointLocation,
		PlayerViewPointRotation);

	return PlayerViewPointLocation * 1000.f;
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()){ return; }
	else
	{
		FVector HitLocation; // Out parameter
		if (GetSightRayHitLocation(HitLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("Location is: %s"), *HitLocation.ToString());
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{

	//FHitResult HitResult;
	///// Setup query parameters ignoring their's owner
	//FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//GetWorld()->LineTraceSingleByObjectType(HitResult,
	//	GetReachLineStart(), GetReachLineEnd(),
	//	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
	//	TraceParameters);
	OutHitLocation = FVector(0.f,0.f,0.f);
	return true;
}

ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}