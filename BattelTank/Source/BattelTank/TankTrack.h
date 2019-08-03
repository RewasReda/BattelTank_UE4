// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTELTANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; // Assume 40 tonne tank, and 1g accelleration

private:
	UTankTrack();
	//virtual void BeginPlay() override;

	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//void ApplySidewaysForce();
	//void DriveTrack();
	//float CurrentThrottle = 0;
	//UFUNCTION()
	//void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	TArray<class ASprungWheel*> GetWheels() const;
	void DriveTrack(float CurrentThrottle);

};
