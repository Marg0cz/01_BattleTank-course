// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAIController.h"


ATank * ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	else
		return Cast<ATank>(PlayerPawn);
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possessing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController is possessing: %s"), *GetControlledTank()->GetName());
	}
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Couldn't find player controller."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI aims at: %s"), *PlayerTank->GetName());
	}

}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
