// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	LastFireTime = FPlatformTime::Seconds();	
}

bool UTankAimingComponent::IsMoving()
{
	if (!ensureAlways(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.1);
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensureAlways(Barrel) || !ensureAlways(Turret)) { return; }
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator =  AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *DeltaRotator.ToString());

	// Move the barrel the right amount this frame
	// Given a max
	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if(IsMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
	// TODO Handle aiming and locked states

}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	/*auto OurTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s From %s Firing At %f"), *OurTankName, *HitLocation.ToString(), *BarrelLocation, LuanchSpeed);
*/

	if (!ensureAlways(Barrel))
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
		AimDirection = OutLuanchVelocity.GetSafeNormal();
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

void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;

}

void UTankAimingComponent::Fire()
{
	//auto Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%f: Tank fires"), Time);
	//if (!ensureAlways(Barrel)) { return; }
	//bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	//if (isReloaded)
	if(FiringState != EFiringState::Reloading)
	{
		if (!ensureAlways(Barrel)) { return; }
		if (!ensureAlways(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>
			(
				ProjectileBlueprint,
				Barrel->GetSocketLocation(FName("Projectile")),
				Barrel->GetSocketRotation(FName("Projectile"))
				);
		Projectile->LaunchProjectile(LuanchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}


}





