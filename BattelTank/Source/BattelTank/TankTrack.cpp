// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	//auto Name = GetName();
	//UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *Name, Throttle);

	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

}

TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent* Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) { continue; }

		AActor* SpawnedChild = SpawnPointChild->GetSpawnedActor();
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		if (!SprungWheel) { continue; }
		ResultArray.Add(SprungWheel);

	}
	return ResultArray;
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();
	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

//void UTankTrack::BeginPlay()
//{
//	Super::BeginPlay();
//
//	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
//
//}

//void UTankTrack::ApplySidewaysForce()
//{
//	// Work-out the required acceleration this frame to correct
//	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
//	auto DeltaTime = GetWorld()->GetDeltaSeconds();
//	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();
//
//	// Calculate and apply sideways (F = m a)
//	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
//	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2;//TwoTracks
//	TankRoot->AddForce(CorrectionForce);
//}

//void UTankTrack::DriveTrack(float CurrentThrottle)
//{
//	// TODO clamp actual throttle value so player can't over-drive
//	//auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
//	//auto ForceLocation = GetComponentLocation();
//	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
//	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
//
//}


//void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//}

//void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
//{
//	//UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit!"))
//	DriveTrack();
//	ApplySidewaysForce();
//	CurrentThrottle = 0;
//}
