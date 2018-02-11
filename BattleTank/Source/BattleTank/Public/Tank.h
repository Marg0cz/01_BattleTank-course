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

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:
	UAimingComponent * AimingComponent = nullptr;
	

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelRefrence(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret * TurretToSet);
	UFUNCTION(BlueprintCallable)
		void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000; // TODO Find sensible default

	UPROPERTY(EditAnywhere, Category = Setup)
		TSubclassOf<AProjectile> BlueprintSpawnable;

	UTankBarrel * Barrel = nullptr;

	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;





};
