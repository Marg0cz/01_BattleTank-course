// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UAimingComponent * AimCompRef);

public:
	void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	// Return current start of reach line

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float CrosshairLocationX = 0.5;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float CrosshairLocationY = 0.33333;

	bool GetLookDirection(FVector2D ScreenLocation, FVector &OutHitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	int32 LineTraceRange = 1000000;
};
