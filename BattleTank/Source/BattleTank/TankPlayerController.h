// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	ATank* GetControlledTank() const;
public:
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
private:
	// Return current start of reach line

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5;
	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.33333;

	bool GetLookDirection(FVector2D ScreenLocation, FVector &OutHitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	int32 LineTraceRange = 1000000;
	
};
