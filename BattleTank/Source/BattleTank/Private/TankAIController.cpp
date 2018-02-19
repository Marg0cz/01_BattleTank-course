// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "AimingComponent.h"
#include "Engine/World.h"





void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto AimingComponent = (GetPawn())->FindComponentByClass<UAimingComponent>();

	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if(AimingComponent->GetFiringState() == EFiringState::Locked)
	AimingComponent->Fire();
}



