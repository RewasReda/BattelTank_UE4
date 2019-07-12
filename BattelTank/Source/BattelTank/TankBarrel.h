// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent) , hidecategories = ("Collision"))
class BATTELTANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void Elevate(float RelativeSpeed);


private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0;
};
