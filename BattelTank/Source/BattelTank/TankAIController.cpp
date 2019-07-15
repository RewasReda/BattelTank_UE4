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
	auto ControlledTank = Cast<ATank>(GetPawn());
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank)
	{
		// TODO Move towards the player

		// Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		ControlledTank->Fire();
	}
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