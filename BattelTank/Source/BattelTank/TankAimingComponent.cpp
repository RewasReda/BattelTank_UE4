// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


//// Called when the game starts
//void UTankAimingComponent::BeginPlay()
//{
//	Super::BeginPlay();
//
//	// ...
//	
//}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator =  AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

	// Move the barrel the right amount this frame
	// Given a max
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

}


//// Called every frame
//void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	// ...
//}

void UTankAimingComponent::AimAt(FVector HitLocation, float LuanchSpeed)
{
	/*auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s From %s Firing At %f"), *OurTankName, *HitLocation.ToString(), *BarrelLocation, LuanchSpeed);
*/

	if (!Barrel)
	{
		return;
	}
	FVector OutLuanchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	/*if (UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLuanchVelocity,
		StartLocation,
		HitLocation,
		LuanchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	)
		)*/
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLuanchVelocity,
		StartLocation,
		HitLocation,
		LuanchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLuanchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("Aiming At %s"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);

	//	auto time = GetWorld()->GetTimeSeconds();

	//	UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), time);
	//}
	//else
	//{
	//	auto time = GetWorld()->GetTimeSeconds();

	//	UE_LOG(LogTemp, Warning, TEXT("%f: No Aim solve found"), time);

	}

}

void UTankAimingComponent::SetBarrelRefrence(UTankBarrel * BarrelToSet)
{
	if (!BarrelToSet)
	{
		return;
	}
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretRefrence(UTankTurret * TurretToSet)
{
	if (!TurretToSet)
	{
		return;
	}
	Turret = TurretToSet;
}

