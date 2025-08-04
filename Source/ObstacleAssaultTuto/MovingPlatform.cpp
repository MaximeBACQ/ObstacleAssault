// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	// MyVector.X = 2330.0f;
	// MyVector.Y = 2070.0f;
	// MyVector.Z = 96.0f;

	StartLocation = GetActorLocation();
	
	UE_LOG(LogTemp, Display, TEXT("Test"))
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime){

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation = CurrentLocation + (PlatformVelocity*DeltaTime);
	SetActorLocation(CurrentLocation);

	if(ShouldPlatformReturn()){
		FVector MoveDirection = PlatformVelocity.GetSafeNormal(); //normalized vector, gives a unit vector in the direction of the velocity, value of 1
		StartLocation += MoveDirection * MoveDistance; //calculus used because we used to do StartLocation = CurrrentLocation but if current location was calculated with a high PlatformVelocity, it would be too far away from the start location and we would overshoot
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity; // Reverse the direction of the platform, AFTER because we use it to set the actor location
		
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime){
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const{
	return FVector::Dist(StartLocation, GetActorLocation());
}
