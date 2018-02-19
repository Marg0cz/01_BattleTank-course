// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};


//Forward Declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and Elevate method
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPROPERTY(EditDefaultsOnly)
		float LaunchSpeed = 5000;

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTankBarrel * TankBarrelToSet, UTankTurret * TankTurretToSet);


	//TODO add tank turret reference
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringState FiringState = EFiringState::Reloading;

public:

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable)
		void Fire();

	EFiringState GetFiringState() const;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
		int Ammunition = 3;
	UFUNCTION(BlueprintCallable)
		int GetAmmunition() const;

private:
	UAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrelTowards();

	void MoveTurretYaw();

	FVector AimDirection;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> BlueprintSpawnable;

	UTankBarrel * Barrel = nullptr;
	UTankTurret * Turret = nullptr;

	bool IsBarrelMoving();

	float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	
};
