// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//auto TankName = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ Construct"), *TankName)
	//TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	//TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

//void ATank::AimAt(FVector HitLocation)
//{
//	if (!ensureAlways(TankAimingComponent)) { return; }
//	/*auto OurTankName = GetName();
//
//	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *OurTankName, *HitLocation.ToString());
//*/
//	TankAimingComponent->AimAt(HitLocation, LuanchSpeed);
//}

// Called when the game starts or when spawned
//void ATank::BeginPlay()
//{
//	Super::BeginPlay();
//	//TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
//	// Needed for BP Begin Play to run!
//	//auto TankName = GetName();
//	//UE_LOG(LogTemp, Warning, TEXT("%s DONKEY: Tank C++ Begin Play"), *TankName)
//}
//
////// Called every frame
////void ATank::Tick(float DeltaTime)
////{
////	Super::Tick(DeltaTime);
////
////}
//
//// Called to bind functionality to input
//void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}
//
//void ATank::SetBarrelRefrence(UTankBarrel * BarrelToSet)
//{
//	TankAimingComponent->SetBarrelRefrence(BarrelToSet);
//	Barrel = BarrelToSet;
//}
//
//void ATank::SetTurretRefrence(UTankTurret * TurretToSet)
//{
//	TankAimingComponent->SetTurretRefrence(TurretToSet);
//}

//void ATank::Fire()
//{
//	//auto Time = GetWorld()->GetTimeSeconds();
//	//UE_LOG(LogTemp, Warning, TEXT("%f: Tank fires"), Time);
//	if (!ensureAlways(Barrel)) { return; }
//	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
//	if (isReloaded)
//	{
//		auto Projectile = GetWorld()->SpawnActor<AProjectile>
//			(
//				ProjectileBlueprint,
//				Barrel->GetSocketLocation(FName("Projectile")),
//				//Barrel->GetSocketRotation(FName("Projectile"))
//				);
//		Projectile->LaunchProjectile(LuanchSpeed);
//		LastFireTime = FPlatformTime::Seconds();
//	}
//
//
//}
//
