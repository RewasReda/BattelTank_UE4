// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	/*auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Can't Find Player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Found Player: %s"), *(PlayerTank->GetName()));
	}*/
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto ControlledTank = GetPawn();
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensureAlways(PlayerTank && ControlledTank)) { return; }
	
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadious);

	//// Aim towards the player
	//ControlledTank->AimAt(PlayerTank->GetActorLocation());

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
	
	
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensureAlways(PossessedTank)) { return; }
		// Subscribe our local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossedTankDeath);
	}
}

void ATankAIController::OnPossedTankDeath()
{
	//UE_LOG(LogTemp, Warning, TEXT("Received!"))
	if (!ensureAlways(GetPawn())) { return; } // TODO remove if ok
	GetPawn()->DetachFromControllerPendingDestroy();
}

//ATank* ATankAIController::GetControlledTank() const
//{
//	return Cast<ATank>(GetPawn());
//}
//
//
//ATank* ATankAIController::GetPlayerTank() const
//{
//	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
//	
//	if (!PlayerPawn)
//	{
//		return nullptr;
//	}
//	return Cast<ATank>(PlayerPawn);
//}