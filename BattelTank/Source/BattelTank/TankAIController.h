// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Components/ActorComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTELTANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// How close can the AI tank get
	float  AcceptanceRadious = 3000;
	/*ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;*/
	virtual void SetPawn(APawn* InPawn) override;
	UFUNCTION()
	void OnPossedTankDeath();
protected:
	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 8000;


};
