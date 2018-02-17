// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// forward declaration
class UAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankTrack;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	UAimingComponent * AimingComponent = nullptr;


public:
	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable)
		void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> BlueprintSpawnable;

	UTankBarrel * Barrel = nullptr; // TODO Remove

	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;





};
